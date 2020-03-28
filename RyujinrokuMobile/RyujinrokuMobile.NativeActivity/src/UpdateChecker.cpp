#include "UpdateChecker.h"
#include <windows.h>
#include <wininet.h>
#include "Utils.h"
#include <string>
#include "Define.h"

using namespace std;

bool UpdateChecker::isUpdate()
{
	HINTERNET hInet;
	HINTERNET hFile;
	LPTSTR lpsz;
	DWORD dwSize;
	char version[1023];
	bool ret = true;

	lpsz = (LPTSTR)GlobalAlloc(GPTR, 1024);

	// ハンドル作成
	hInet = InternetOpen(TEXT("TEST"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	// 通信成功時
	if (InternetAttemptConnect(0) == ERROR_SUCCESS && hInet != NULL) {

		// ＵＲＬオープン
		hFile = InternetOpenUrl(hInet, TEXT("http://dixq.net/ryujin2/version/version.txt"), NULL, 0, INTERNET_FLAG_RELOAD, 0);

		// ファイル読み込み
		if (!InternetReadFile(hFile, lpsz, 1023, &dwSize)) {
			InternetCloseHandle(hFile);
			InternetCloseHandle(hInet);
			return true;
		}
		sprintf(version, "%s", lpsz);		// char化

		int newVersion = Utils::getIntFromString(version);
		int nowVersion = Utils::getIntFromString(VERSION);

		if (newVersion == -1 || nowVersion == -1) {
			MessageBox(NULL, TEXT("更新確認でエラーが発生しました"), TEXT("更新確認"), MB_OK);
		}
		else if (newVersion>nowVersion) {
			char str[1024];
			string newSVer = Utils::getShortVersionString(version);
			string nowSVer = Utils::getShortVersionString();
			sprintf(str,"最新バージョンがあります。更新しますか？\n　　　v%s\n　　　↓\n　　　v%s",nowSVer.c_str(),newSVer.c_str());
			int Win_flag = MessageBox(NULL, TEXT(str), TEXT("更新情報"), MB_YESNO | MB_ICONQUESTION);
			if (Win_flag == IDYES) {
				//system("start http://dixq.net/ryujin2/binary");	// ←最新バージョンダウンロード用URL
				ShellExecute(NULL, NULL, "http://dixq.net/ryujin2/download.html", NULL, NULL, SW_SHOWNORMAL);
				ret = false;
			}
		}
		// 終了処理 
		InternetCloseHandle(hFile);
		InternetCloseHandle(hInet);
	}
	return ret;
}
