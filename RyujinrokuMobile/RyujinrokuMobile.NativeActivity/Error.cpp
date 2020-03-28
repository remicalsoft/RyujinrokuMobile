#define _CRT_SECURE_NO_WARNINGS

#include "Error.h"
#include <string>
#include <DxLib.h>
#include "Define.h"

using namespace std;

void Error::finish(const char * errorMessage, const char* funcName, int lineN)
{
	char name[1024];
	sprintf(name, "%s", funcName);
	printfDx("異常が発生しました。\n%s\n%s(%d)"
		,errorMessage
		,name
		,lineN
	);
	while (!ProcessMessage()) {
		ClearDrawScreen();
		ScreenFlip();
	}
	DxLib_End();
	exit(99);
}
