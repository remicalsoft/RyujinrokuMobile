#include "Error.h"
#include <string>
#include "Keyboard.h"
#include <DxLib.h>
#include "Define.h"
#include "Utils.h"
#include <string>

using namespace std;

void Error::finalize(char * errorMessage, LPCTSTR lpszFuncName, int lineN)
{
	char funcName[1024];
	sprintf(funcName, "%s", lpszFuncName);
	printfDx("異常が発生しました。\n\n%s\n%s(%d) ver%s\n\nお手数ですが公式HPかryujinroku2@gmail.comまで御報告をお願いします\nエラー内容は「エラー内容.txt」に出力されています\n\nEscで終了します"
		,errorMessage
		,funcName
		,lineN
		, VERSION
		);
	string path = Utils::getSavePath();
	path += "エラー内容.txt";
	FILE *fp = fopen(path.c_str(),"w");
	if (fp != NULL) {
		fprintf(fp, "%s\n%s(%d) ver%s"
			, errorMessage
			, funcName
			, lineN
			, VERSION
			);
		fclose(fp);
	}
	while (!ProcessMessage()) {
		ClearDrawScreen();
		Keyboard::getIns()->update();
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
		ScreenFlip();
	}
	DxLib_End();
	exit(99);
}
