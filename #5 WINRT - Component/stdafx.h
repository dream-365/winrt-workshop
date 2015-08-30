// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <wrl.h>
#include <winstring.h>
#include <stdio.h>

template <typename ... Args>
void Trace(wchar_t const * format, Args ... args)
{
	wchar_t buffer[200];

	swprintf_s(buffer, format, args ...);

	OutputDebugString(buffer);
}
