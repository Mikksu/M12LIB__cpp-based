#pragma once

#include "stdafx.h"

UINT CRC32_Calculate_BYTE(LPBYTE data, int length);
UINT CRC32_Calculate_UINT(LPUINT data, int length);
UINT Accumulate(LPUINT buffer, int length);