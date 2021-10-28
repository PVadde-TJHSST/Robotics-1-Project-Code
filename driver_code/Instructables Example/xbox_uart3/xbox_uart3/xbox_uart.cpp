#include "stdafx.h"
#include "xbox_uart.h"

XBoxUart::XBoxUart()
{
	port = NULL;
	controllerID = -1;		// Set controller ID to invalid value

	for(int i=0;i<4;i++) // Check which controller is on
	{
		DWORD res = XInputGetState(i,&currentState);	// Get current state
		if(res==ERROR_SUCCESS)							// If on, set the controller ID to current value
		{
			controllerID = i;
		}
	}
}


bool XBoxUart::isOn()
{
		DWORD res = XInputGetState(controllerID,&currentState);	// Get current state
		if(res==ERROR_SUCCESS)							// If on, set the controller ID to current value
			return TRUE;
		else 
			return FALSE;
}

bool XBoxUart::connect(LPCWSTR portName, DWORD baudRate)
{
	DCB				portDCB;					// _DCB struct for serial configuration
	bool			result = FALSE;				// Return value
	COMMTIMEOUTS	comTOUT;					// Communication timeout
	try{
		port = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, NULL);
		// Try opening port communication
		if(&port==INVALID_HANDLE_VALUE)
		{
			CloseHandle(&port);
			port = NULL;
			return FALSE;
		}
		// NEW SETTINGS
		portDCB.DCBlength = sizeof(DCB);			// Setup config length
		GetCommState(&port, &portDCB);				// Get default port state
		portDCB.BaudRate = baudRate;				// Set baud rate
		portDCB.fBinary = TRUE;						// Enable Binary mode
		portDCB.fParity = FALSE;					// Disable parity 
		portDCB.fOutxCtsFlow = FALSE;				// No CTS 
		portDCB.fOutxDsrFlow = FALSE;				// No DSR
		portDCB.fDtrControl = DTR_CONTROL_DISABLE;	// No DTR
		portDCB.fDsrSensitivity = FALSE;			// No DSR sensitivity 
		portDCB.fTXContinueOnXoff = TRUE;			// TX on XOFF
		portDCB.fOutX = FALSE;						// No XON/XOFF
		portDCB.fInX = FALSE;						//
		portDCB.fErrorChar = FALSE;					// No error correction
		portDCB.fNull = FALSE;						// Keep NULL values
		portDCB.fRtsControl = RTS_CONTROL_DISABLE;	// Disable RTS
		portDCB.fAbortOnError = FALSE;				// Disable abort-on-error
		portDCB.ByteSize = 8;						// 8-bit frames
		portDCB.Parity = NOPARITY;					// Parity: none
		portDCB.StopBits = ONESTOPBIT;				// StopBits: 1

		// Try reconfiguring COM port
		if (!SetCommState (port, &portDCB))
		{
			CloseHandle(port);
			port=NULL;
			return FALSE;
		}
 
		/// Communication timeout values
		GetCommTimeouts(port, &comTOUT);
		comTOUT.ReadIntervalTimeout = 1;
		comTOUT.ReadTotalTimeoutMultiplier = 1;
		comTOUT.ReadTotalTimeoutConstant = 1;
		/// Set communication time out values
		SetCommTimeouts(port, &comTOUT);
	}
	catch (int e)
	{
	}

	return TRUE;
}

bool XBoxUart::disconnect()
{
	if (port == NULL) return FALSE;
	CloseHandle(port);
	port = NULL;
	return TRUE;
}
bool XBoxUart::updateState()
{
	DWORD res = XInputGetState(controllerID,&currentState);
	if(res==ERROR_SUCCESS)
		return TRUE;
	else
		return FALSE;
}

bool XBoxUart::send()
{
	char buffer [BUFFER_SIZE];					// Create buffer
	memset(buffer,0,BUFFER_SIZE);				// Clear buffer
	updateState();								// Update controller state
	XINPUT_GAMEPAD g = currentState.Gamepad;	// Get current state
	float LX = g.sThumbLX/256;
	float LY = g.sThumbLY/256;
	float speed = sqrt(LX*LX+LY*LY);
	float lmot;
	float rmot;
	int dir = 0;
	if(speed>40)
	{
		lmot = (LX>0)?speed:(128-abs(LX));		// Left motor speed
		rmot = (LX<0)?speed:(128-abs(LX));		// Right motor speed
		// Set direction
		dir=(g.sThumbLY>0)?1:0;					// 1-Forward / 0-Backward
	}
	else
	{
		// Compensate for deadzone
		lmot=0;
		rmot=0;
		dir=0;
		speed=0;
	}

	sprintf(buffer,"%d %d %d %d\n",(int)lmot,(int)rmot,(int)dir,g.wButtons);		// Write formatted data to buffer
	DWORD bytesTransmitted;
	if(!WriteFile(port,buffer, strlen(buffer), &bytesTransmitted, NULL))// Send data to UART
	{ 
		// Error occured
		DWORD Errors;
		COMSTAT Status;
		ClearCommError(port,&Errors,&Status);
		return FALSE;
	}
	else 
		return TRUE;
}

bool XBoxUart::receive(char *buffer)
{
	DWORD bytesTransmitted = 0;			// Byte counter
	DWORD status = EV_RXCHAR;			// transmission status mask

	memset(buffer, 0, BUFFER_SIZE);		// Clear input buffer

	SetCommMask (port, EV_RXCHAR);		// Set up event mask
	WaitCommEvent(port, &status, 0);	// Listen for RX event

	if(status & EV_RXCHAR)				// If event occured
	{
		DWORD success=0;
		char c = 0;
		do
		{
			if(!ReadFile(port,&c, 1, &success, NULL))	// Read 1 char
			{
				// If error occured, print the message and exit
				DWORD Errors;
				COMSTAT Status;
				ClearCommError(port,&Errors,&Status);		// Clear errors
				memset(buffer, 0, BUFFER_SIZE);				// Clear input buffer
				return FALSE;
			}
			else
			{
				buffer[bytesTransmitted]=c;			// Add last character
				bytesTransmitted++;					// Increase transm. counter
			}
		} while((success==1) && (c!='\n'));			// Repeat until the end of message
	}
	return TRUE;
}