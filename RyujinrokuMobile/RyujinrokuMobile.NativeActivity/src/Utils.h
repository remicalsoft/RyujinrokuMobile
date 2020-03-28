#pragma once

#include <DxLib.h>
#include "Pad.h"
#include <vector>

float round_f(float fVal, int sN);
float randf ( float val );
float randf2( float val );
float stdRandf(float val);
float stdRandf2(float val);

class Utils {
public:
	static float getSinValue_90(float fRate, float fVal);
	static float getCosValue_90(float fRate, float fVal);
	static float sinAmount_180(float fRate, float fVal);
	static bool  isKeyPushed(ePad pad);
	static void  showNowLoading();
	static void  rotatePos (float *x, float *y, float ang, float mx, float my);
	static void  rotatePos2(float *x, float *y, float x0, float y0, float mx, float my, float ang);
	static float getLength(float x1, float y1, float x2, float y2);
	static float getSinValue_m90(float fRate, float fVal);
	static bool  isHit(
		float pt1x,
		float pt1y,
		float v,
		float angle,
		float range1,
		float pt2x,
		float pt2y,
		float range2
		);
	static void DrawSquare(int color, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);

	static int getIntFromString(const char* str);
	static char* getNowTimeString();
	
	const static int nPasTgl[12][12];
	//0〜1を渡すとベジェ曲線にして0〜1を返してくれる　LVは1から5 moveFlagは0が速い→遅い　1が遅い→速い→遅い  2が遅い→速い
	enum EBejeType{ EBejeType_QuickSlow, EBejeType_SlowQuickSlow, EBejeType_SlowQuick};
	static double GetBeje(int LV, EBejeType moveType, double rate);
	static float Utils::GetBejeSub(const float &y1, const float &y2, const float &t, const int &n);	//サブ関数

	//スピログラフの座標を代入する関数 sitaは0〜PI2
	static void getCycloid(double& x, double& y, double R, double r, double a, double sita);


	//点1に対する点2の角度を返す
	static float getAngle(float x1, float y1, float x2, float y2);
	static int creatableNumOfReplayFileName();
	static int maxNumOfReplayFileName();

	static void splitString(const std::string& s, const std::string& delim, std::vector<std::string>& result);
	static std::vector<std::string> splitString(const char* s, const char* delim);
	static std::string getShortVersionString(std::string v);
	static std::string getShortVersionString();
	static int convertPlayTimeToMoney(int playTime);

	//paramに負を与えると反対方向、sangleが開始角。
	static void DrawReversibleCircleGauge(const int x, const int y, const double size, const int handle, const double param, const double angle);
	static std::string getSavePath();
	static bool existsFolder(const char* path);
};

