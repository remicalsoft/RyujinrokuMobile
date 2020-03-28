#include "DxLib.h"

// プログラムは android_main から始まります
int android_main(void)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	DrawBox(220, 140, 420, 340, GetColor(255, 255, 255), TRUE);	// 四角形を描画する

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了 
}