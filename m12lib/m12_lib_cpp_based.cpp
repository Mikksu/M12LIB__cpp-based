// m12_lib_cpp_based.cpp : Defines the exported functions for the DLL application.
//

#include <windows.h>
#include "stdafx.h"
#include "m12_lib_cpp_based.h"

HANDLE hComm;

int Open(LPCUWSTR PortName, const int BaudRate)
{
	DCB dcb;

	// Open the port
	hComm = CreateFile(PortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	// unable to open the comm port.
	if (hComm == (HANDLE)-1)
		return ERR_OPEN_COMM_FAILED;

	// unable to get the comm DCB.
	if (!GetCommState(hComm, &dcb))
		return ERR_GET_COMM_DCB;

	// set DCB.
	dcb.BaudRate = BaudRate;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;	
	if (!SetCommState(hComm, &dcb))
		return ERR_SET_COMM_DCB;

	// set timeouts
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = MAXDWORD;
	timeouts.ReadTotalTimeoutConstant = MAXDWORD;
	timeouts.ReadTotalTimeoutConstant = 300;
	timeouts.WriteTotalTimeoutConstant = 300;
	timeouts.WriteTotalTimeoutMultiplier = MAXDWORD;
	if (!SetCommTimeouts(&hComm, &timeouts))
		return ERR_SET_TIMEOUT;

	return 0;
}

void Close()
{
	CloseHandle(hComm);
}



