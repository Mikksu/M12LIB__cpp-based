#include "stdafx.h"
#include "private_methods.h"

bool write_port(HANDLE hPort, BYTE data[], int length)
{
	DWORD bytesWriten = 0;
	bool ret = WriteFile(hPort, data, length, &bytesWriten, NULL);
	if (ret)
		return true;
	else
		return false;
}

bool read_port(HANDLE hPort, BYTE *data)
{
	DWORD dwCommModemStatus;
	DWORD bytesRead = 0;

	SetCommMask(hPort, EV_RXCHAR | EV_ERR);
	
	bool ret = ReadFile(hPort, data, 1, &bytesRead, NULL);

	return ret;

	/*
	WaitCommEvent(hPort, &dwCommModemStatus, NULL);
	if (dwCommModemStatus & EV_RXCHAR)
	{
		if (ReadFile(hPort, data, 1, &bytesRead, NULL))
			return true;
		else
			return false;
	}
	else if (dwCommModemStatus & EV_ERR)
	{
		return false;
	}
	else
	{
		return false;
	}
	*/
}