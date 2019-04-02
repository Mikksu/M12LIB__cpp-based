#pragma once

bool write_port(HANDLE hPort, BYTE data[], int length);
bool read_port(HANDLE hPort, BYTE *data);