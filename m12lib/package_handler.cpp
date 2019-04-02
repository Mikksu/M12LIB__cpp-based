#include "stm32_crc32.h"
#include "package_handler.h"


#define HEADER					0x7E
#define API_IDENTIFIER_DATA		0x69
#define SIZE_HEADER				1
#define SIZE_LENGTH				2
#define SIZE_API_ID				1
#define SIZE_FRAME_ID			2
#define SIZE_COMMAND			1
#define SIZE_CRC				4
#define SIZE_OVERALL_COST		SIZE_HEADER + SIZE_LENGTH + SIZE_CRC

#define BUFFER_LEN				curByteInBuffer - buffer	// calculate the count of the available bytes in the buffer.

BYTE buffer[MAX_BUFFER_SIZE] = { 0 };		// buffer used to receive the incoming data.
LPBYTE curByteInBuffer = buffer;			// pointer to the next empty byte of the buffer.
bool IsHeaderReceived = false;				// indicates whether the header byte has received or not.
int LengthExpected = 0;						// the desired length of the package.

static void reset_buffer()
{
	curByteInBuffer = buffer;
	IsHeaderReceived = false;
	LengthExpected = 0;

	memset(buffer, 0, MAX_BUFFER_SIZE);
}

RXPACK_STA AddData(BYTE data, LPRXPACKAGE packageReceived)
{
	if (data == HEADER && IsHeaderReceived == false)
	{
		/*
		* If the package header is received. package is null
		* this is the header identifier rather than the payload.
		*/
		reset_buffer();

		*curByteInBuffer++ = data;
		IsHeaderReceived = true;
	}
	else if (IsHeaderReceived)
	{
		int availableBytes = curByteInBuffer - buffer;
		if (BUFFER_LEN > 0)
		{
			/*
			 * This is the payload, put it into the byte array.
			 */

			*curByteInBuffer++ = data;

			// The length of the package has received.
			if (BUFFER_LEN == 3)
			{
				LengthExpected = buffer[1] + buffer[2] * 256;
			}
			else if (LengthExpected > 0)
			{
				// We received a complete package
				if (BUFFER_LEN == LengthExpected + SIZE_OVERALL_COST)
				{
					//TODO too verbose without pointer?
					
					//buffer = memStream.ToArray();
			
					UINT crc_desired = CRC32_Calculate_BYTE(buffer, LengthExpected + SIZE_OVERALL_COST - SIZE_CRC);
					LPUINT crc_received = (LPUINT)(buffer + LengthExpected + SIZE_OVERALL_COST - SIZE_CRC);

					if (crc_desired == *crc_received)
					{
						memcpy(packageReceived, buffer, sizeof(RXPACKAGE));
						reset_buffer();
						
						return PACK_RECV;
					}
					else
					{
						return PACK_CRC_ERR;
					}
				}
			}
		}

		return PACK_NOT_FOUND;
	}
}