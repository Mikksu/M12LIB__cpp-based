#pragma once

#include "stdafx.h"

#define MAX_BUFFER_SIZE			256

typedef enum
{
	PACK_RECV,
	PACK_NOT_FOUND,
	PACK_CRC_ERR

} RXPACK_STA;

typedef struct _RXPACKAGE
{
	BYTE		Header;
	UINT16		Length;
	BYTE		ApiIdentifier;
	UINT16		FrameID;
	BYTE		Command;
	BYTE		Payload[MAX_BUFFER_SIZE - 7];

} RXPACKAGE, *PRXPACKAGE, *LPRXPACKAGE;

RXPACK_STA AddData(BYTE data, LPRXPACKAGE packageReceived);
