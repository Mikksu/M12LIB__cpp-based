#pragma once

#include "atlstr.h"

#ifdef M12LIBCPPBASED_EXPORTS
#define M12LIBCPPBASED_API __declspec(dllexport)
#else
#define M12LIBCPPBASED_API __declspec(dllimport)
#endif

#define ERR_NONE					0x0
#define ERR_OPEN_COMM_FAILED		0x00000001
#define ERR_GET_COMM_DCB			0x00000002
#define ERR_SET_COMM_DCB			0x00000003
#define ERR_SET_TIMEOUT				0x00000004

extern "C" M12LIBCPPBASED_API int Open(LPCUWSTR PortName, const int BaudRate);
extern "C" M12LIBCPPBASED_API void Close();