#pragma once

#include <wrl.h>
#include <stdio.h>

#define ASSERT _ASSERTE

template <typename ... Args>
void Trace(wchar_t const * format, Args ... args)
{
    wchar_t buffer[200];
    swprintf_s(buffer, format, args ...);
	
	wprintf(buffer);
}
