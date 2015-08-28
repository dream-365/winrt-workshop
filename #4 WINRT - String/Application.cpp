// Application.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <winstring.h>

#pragma comment(lib, "runtimeobject")

template <unsigned length>
HSTRING CreateHString(wchar_t const (&string)[length])
{
	HSTRING result;

	WindowsCreateString(string,
		length - 1,
		&result);

	return result;
}


int main()
{
	// windows string creating
	HSTRING text = CreateHString(L"Application.Name!");

	// decrements the reference count of a string buffer
	WindowsDeleteString(text);

	PCWSTR str = WindowsGetStringRawBuffer(text, nullptr);

	bool isEmpty = WindowsIsStringEmpty(text);

	wprintf(L"Address: 0x%x, Text: %s\n", str, str);

	wprintf(L"Is Empty: %s\n", isEmpty ? L"YES" : L"NO");

	HSTRING dupText;

	// windows string duplication
	WindowsDuplicateString(text, &dupText);

	PCWSTR dupStr = WindowsGetStringRawBuffer(text, nullptr);

	wprintf(L"Address1: 0x%x, Address2: 0x%x\n", str, dupStr);

    return 0;
}

