#include "trace.h"
#include "stdio.h"

#ifdef _DEBUG
void _trace(LPCWSTR lpszFmt, ...)
{
	va_list args;  
	va_start(args, lpszFmt);  

	int len = _vscwprintf(lpszFmt, args) + 1;  
	wchar_t* lpszBuf = new wchar_t[len];  
	vswprintf_s(lpszBuf, len, lpszFmt, args);  
	va_end(args);  
	OutputDebugStringW(lpszBuf);  

	delete[] lpszBuf;  
}
#endif