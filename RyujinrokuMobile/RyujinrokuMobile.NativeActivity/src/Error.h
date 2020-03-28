#pragma once

#include <Windows.h>

class Error
{
public:
	static void finalize(char* errorMessage, LPCTSTR lpszFuncName, int lineN);
};

