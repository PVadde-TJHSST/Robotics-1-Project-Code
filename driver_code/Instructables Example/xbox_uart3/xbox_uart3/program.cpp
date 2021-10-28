// xbox_uart3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#include "xbox_uart.h"

#define WIN32_LEAN_AND_MEAN			// Strip the unwanted components

#pragma comment (lib,"XInput.lib")	// Necessary for linker

using namespace std;

void parseData(char *buffer);
void printData(char *data);

struct Response
{
	int PortB;
};

int _tmain(int argc, _TCHAR* argv[])
{
	XBoxUart gpad1;					// Create a gamepad with last ID assigned
	char buffer[BUFFER_SIZE];
	memset(buffer,0,BUFFER_SIZE);	// Clear the buffer
	if(gpad1.controllerID<0)		// Check if connected
	{
		cerr << "WARNING: Gamepad not found.\n";
		system("PAUSE");
		return 1;
	}

	if(!gpad1.connect(L"COM8:",115200)) // Check if COM port connects
	{
		cerr << "ERROR: Unable to connect to " << argv[1] << "\n";
		system("PAUSE");
		return 1;
	}
	while(gpad1.send())
	{
		gpad1.receive(buffer);
		system("CLS");		// Clear screen
		cout << "XBOX GAMEPAD TO UART V0.0\n\n" ;
		Sleep(1);
		cout << buffer << "\n";
	}

	gpad1.disconnect();
	system("PAUSE");
	return 0;
}