#include <Windows.h>

#ifdef _DEBUG
void _trace(LPCWSTR lpszFmt, ...);
#ifndef TRACE
#define TRACE _trace
#endif
#else
#define TRACE false && _trace
#endif