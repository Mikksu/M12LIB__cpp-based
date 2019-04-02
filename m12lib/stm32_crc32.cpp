#include "stm32_crc32.h"
#include "stdafx.h"

#define INIT_VAL	0xFFFFFFFF;
#define POLY		0x4C11DB7;

#define RESET()		crc_retval = INIT_VAL

static UINT crc_retval = INIT_VAL;

static void calculate(UINT data)
{
	int bindex = 0;
	UINT crc = data ^ crc_retval;

	while (bindex < 32)
	{
		if ((crc & 0x80000000) > 0)
		{
			crc = (crc << 1) ^ POLY;
		}
		else
		{
			crc <<= 1;
		}

		bindex++;
	}

	crc_retval = crc;
}

UINT Accumulate(LPUINT buffer, int length)
{
	for (int i = 0; i < length; i++)
	{
		calculate(buffer[i]);
	}

	return crc_retval;
}

UINT CRC32_Calculate_UINT(LPUINT data, int length)
{
	RESET();
	return Accumulate(data, length);
}

UINT CRC32_Calculate_BYTE(LPBYTE data, int length)
{
	// if the length of data is not 4-byte aligned, 
	// fill with zero to the end of the buf to make 
	// it 4-byte aligned.
	int len = (length + 3) / 4;
	UINT* buf = new UINT[len];

	memset((LPBYTE)buf, 0, len * 4);
	memcpy((LPBYTE)buf, data, length);

	UINT crc = CRC32_Calculate_UINT(buf, len);

	delete buf;

	return crc;
}