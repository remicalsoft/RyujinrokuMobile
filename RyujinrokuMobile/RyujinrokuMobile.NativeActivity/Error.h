#pragma once

class Error
{
public:
	static void finish(const char* errorMessage, const char* funcName, int lineN);
};
