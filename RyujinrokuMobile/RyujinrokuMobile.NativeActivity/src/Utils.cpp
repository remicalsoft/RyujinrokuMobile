#include <math.h>
#include <DxLib.h>
#include "Utils.h"
#include "Define.h"
#include "Pad.h"
#include <string>
#include <vector>
#include <time.h>
#include <Windows.h>
#include "shlobj.h"

using namespace std;

/*
 *@brief fValの小数点第sN位を四捨五入して丸める 
 */
float round_f(float fVal, int sN){
    float fAns;
    fAns = fVal * pow(10.f, +sN-1 );
    fAns = (float)(int)(fAns + 0.5f);
    return fAns * pow(10.f, -sN+1 );
}

/*
* @brief 0~valまでの乱数を返す
*/
float randf(float val) {
	return GetRand(1000000) / 1000000.f * val;
}

/*
* @brief -val~valまでの乱数を返す
*/
float randf2(float val) {
	return GetRand(1000000) / 500000.f * val - val;
}

/*
* @brief 0~valまでの乱数を返す
*/
float stdRandf(float val) {
	return rand() / (float)RAND_MAX * val;
}

/*
* @brief -val~valまでの乱数を返す
*/
float stdRandf2(float val) {
	return rand() / (float)(RAND_MAX/2) * val - val;
}

/*
	@brief	弾とキャラとのあたり判定を行う

	弾のスピードが弾のあたり判定範囲を超えていたら軌跡を辿ってあたり判定を行う

	@param[in]	vPos1	弾の座標
	@param[in]	fSpd1	弾のスピード
	@param[in]	fAng1	弾の角度
	@param[in]	fRange1	弾のあたり判定半径
	@param[in]	fvPos2	キャラの座標
	@param[in]	fRange2	キャラのあたり判定半径

	@warning	キャラはあたり判定半径以上のスピードで動かないことを前提としている。
				そのため，極細レーザー上をキャラが横切る時などはすり抜ける可能性がある
*/
bool Utils::isHit( 
	float x1,
	float y1,
	float v,
	float angle,
	float r1,
	float x2,
	float y2,
	float r2
){
	float x,y,r;
	x = x1-x2;
	y = y1-y2;
	r = r1 + r2;
	if( x*x + y*y < r*r ){		//ほとんどはこの判定式のみで済む。
		return true;
	}
	
	//軌跡を辿る時のみ計算量が増える(math計算)ようにするため，別計算にしてある
	float sx, sy;
	for( float i=0.5; v > r*i; i+=0.5f ){
		sx = x1-cos(angle+PI)*r*i;
		sy = y1-sin(angle+PI)*r*i;
		x  = sx-x2;
		y  = sy-y2;
		if( x*x + y*y < r*r ){
			return true;
		}
	}
		
	return false;
}

/*
@brief	sin波の0〜1の変化量を求める
0〜90度までの変化量を0〜1にするので、急に変化が始まって滑らかに1になる

@param [in] fRate	sin波に変換したい位置を0〜1で指定
@param [in] fVal	変化させたい最大値
*/
float Utils::getSinValue_90(float fRate, float fVal) {
	if (fRate > 1.f) {
		fRate = 1.f;
	}
	if (fRate < 0) {
		fRate = 0;
	}
	return sin(PI / 2 * fRate) * fVal;
}

/*
@brief	sin波の0〜1の変化量を求める
-90〜0度までの変化量を0〜1にするので、滑らかに変化が始まって急にfValになってとまる

@param [in] fRate	sin波に変換したい位置を0〜1で指定
@param [in] fVal	変化させたい最大値
*/
float Utils::getSinValue_m90(float fRate, float fVal) {
	if (fRate > 1.f) {
		fRate = 1.f;
	}
	if (fRate < 0) {
		fRate = 0;
	}
	fRate = 1 - fRate;
	return (sin(-PI/2*fRate)+1) * fVal;
}

/*
@brief	cos波の0〜1の変化量を求める
0〜90度までの変化量を0〜1にするので、急に変化が始まって滑らかに1になる

@param [in] fRate	cos波に変換したい位置を0〜1で指定
@param [in] fVal	変化させたい最大値
*/
float Utils::getCosValue_90(float fRate, float fVal) {
	if (fRate > 1.f) {
		fRate = 1.f;
	}
	if (fRate < 0) {
		fRate = 0;
	}
	return cos(PI / 2 * fRate) * fVal;
}

/*
	@brief	sin波の0〜1の変化量を求める
	-90〜90度までの変化量を0〜1にするので、滑らかに変化が始まって滑らかに1になる

	@param [in] fRate	sin波に変換したい位置を0〜1で指定
	@param [in] fVal	変化させたい最大値
*/
float Utils::sinAmount_180( float fRate, float fVal )
{
	if( fRate > 1.f ){
		fRate = 1.f;
	}
	if( fRate < 0 ){
		fRate = 0;
	}
	return (sin( -PI/2 + PI*fRate )+1.f)/2.f * fVal;
}


bool Utils::isKeyPushed(ePad pad)
{
	int key = Pad::getIns()->get(pad);
	if (key == 1 || key > KEY_REPERT && key % KEY_REPERT_ITVL == 0) {
		return true;
	}
	return false;
}

void Utils::showNowLoading()
{
	ClearDrawScreen();
	LoadGraphScreen(WIN_W-802, WIN_H-179, "dat/image/common/nowloading.png", TRUE);
	ScreenFlip();
}

void Utils::rotatePos(float *x, float *y, float ang, float mx, float my) {
	float ox = *x - mx, oy = *y - my;
	*x = ox*cos(ang) + oy*sin(ang);
	*y = -ox*sin(ang) + oy*cos(ang);
	*x += mx;
	*y += my;
}

float Utils::getLength(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

void Utils::DrawSquare(int color, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
	DrawTriangle((int)x0, (int)y0, (int)x1, (int)y1, (int)x2, (int)y2, color, TRUE);
	DrawTriangle((int)x0, (int)y0, (int)x3, (int)y3, (int)x2, (int)y2, color, TRUE);
}

void Utils::splitString(const string& s, const string& delim, vector<string>& result)
{
	result.clear();

	using string = std::string;
	string::size_type pos = 0;

	while (pos != string::npos)
	{
		string::size_type p = s.find(delim, pos);

		if (p == string::npos)
		{
			result.push_back(s.substr(pos));
			break;
		}
		else {
			result.push_back(s.substr(pos, p - pos));
		}

		pos = p + delim.size();
	}
}

std::vector<std::string> Utils::splitString(const char * as, const char * adelim)
{
	vector<string> result;
	string s(as);
	string delim(adelim);

	using string = std::string;
	string::size_type pos = 0;

	while (pos != string::npos)
	{
		string::size_type p = s.find(delim, pos);

		if (p == string::npos)
		{
			result.push_back(s.substr(pos));
			break;
		}
		else {
			result.push_back(s.substr(pos, p - pos));
		}

		pos = p + delim.size();
	}
	return result;
}

std::string Utils::getShortVersionString(std::string ver)
{
	vector<string> list = Utils::splitString(ver.c_str(), ".");
	int v[3] = { atoi(list[0].c_str()), atoi(list[1].c_str()), atoi(list[2].c_str()) };
	string str;
	str += to_string(v[0]) + "." + to_string(v[1]) + "." + to_string(v[2]);
	return str;
}

std::string Utils::getShortVersionString()
{
	vector<string> list = Utils::splitString(VERSION, ".");
	int v[3] = { atoi(list[0].c_str()), atoi(list[1].c_str()), atoi(list[2].c_str()) };
	string str;
	str += to_string(v[0]) + "." + to_string(v[1]) + "." + to_string(v[2]);
	return str;
}

int Utils::convertPlayTimeToMoney(int playTime)
{
	return playTime/1000;
}

/*!
 * @brief "1.2.23"を10223というint型にして返す
 */
int Utils::getIntFromString(const char * str)
{
	{//strの中に数字か.以外が含まれていないかチェック
		int i = 0;
		if (str[i] == '\0') {
			return -1;
		}
		while (str[i] != '\0') {
			if ('0' <= str[i] && str[i] <= '9' || str[i] == '.') {
			}
			else {
				return -1;
			}
			i++;
		}
	}
	vector<string> result;
	splitString(str, ".", result);
	if (result.size() != 3) {//1.12.23のような3分割にならなかったらエラー
		return -1;
	}
	return atoi(result[0].c_str()) * 10000 + atoi(result[1].c_str()) * 100 + atoi(result[2].c_str());
}

char * Utils::getNowTimeString()
{
	char* str = new char[1024];
	time_t timer;
	struct tm *t_st;
	time(&timer);
	ctime(&timer);
	t_st = localtime(&timer);
	sprintf(str, "%d時%d分%d秒", t_st->tm_hour, t_st->tm_min, t_st->tm_sec);
	return str;
}

//座標回転
//(x0,y0)から(mx,my)を基準にang角回転した角度を(x,y)にいれる
void Utils::rotatePos2(float *x, float *y, float x0, float y0, float mx, float my, float ang) {
	float ox = x0 - mx, oy = y0 - my;
	*x = ox*cos(ang) + oy*sin(ang);
	*y = -ox*sin(ang) + oy*cos(ang);
	*x += mx;
	*y += my;
}


//Dixqさん流ベジェ曲線
const int Utils::nPasTgl[12][12] = {
	{ 1 },
	{ 1,1 },
	{ 1,2,1 },
	{ 1,3,3,1 },
	{ 1,4,6,4,1 },
	{ 1,5,10,10,5,1 },
	{ 1,6,15,20,15,6,1 },
	{ 1,7,21,35,35,21,7,1 },
	{ 1,8,28,56,70,56,28,8,1 },
	{ 1,9,36,84,126,126,84,36,9,1 },
	{ 1,10,45,120,210,252,210,120,45,10,1 },
	{ 1,11,55,165,330,464,464,330,165,55,11,1 }
};

float Utils::GetBejeSub(const float &y1, const float &y2, const float &t, const int &n)
{
	float b = t > 1 ? 1 : (t < 0 ? 0 : t);
	float a = 1 - b;
	float ay = 0;
	float y[4] = { 0, y1, y2, 1 };
	int m;
	for (int i = 0; i <= n; i++) {
		m = i == 0 ? 0 : (i == n ? 3 : (i <= n / 2 ? 1 : 2));//yの添え字決定
		ay += nPasTgl[n][i] * pow(a, n - i)*pow(b, i)*y[m];
	}
	return ay;
}

//0〜1を渡すとベジェ曲線にして0〜1を返してくれる　LVは1から5 moveTypeは0が速い→遅い　1が遅い→速い→遅い  2が遅い→速い
double Utils::GetBeje(int LV, EBejeType moveType, double rate)
{
	int n = LV * 2 + 1;                //n次元指定
	if (LV>5 || LV<1)
	{
		printfDx("不正なLV（GetBeje）");
		return 0;
	}
	float y1, y2;
	if (moveType == 0)
	{
		y1 = 1;
		y2 = 1;
	}
	else if (moveType == 1)
	{
		y1 = 0;
		y2 = 1;
	}
	else if (moveType == 2)
	{
		y1 = 0;
		y2 = 0;
	}
	else
	{
		printfDx("不正なmoveType（GetBeje）");
		return 0;
	}
	return GetBejeSub(y1, y2, float(rate), n);
}

//スピログラフの座標を代入する関数 sitaは0〜PI2
void Utils::getCycloid(double& x, double& y, double R, double r, double a, double sita)
{
	x = (R - r)*cos(sita + PI / 2) + a*cos((R / r - 1)*sita);
	y = (R - r)*sin(sita + PI / 2) - a*sin((R / r - 1)*sita);
}


//点1に対する点2の角度を返す
float Utils::getAngle(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	if (dx == 0 && dy == 0)	//両方０なら０を返すことにする
		return 0;
	else
		return atan2(dy, dx);
}

int Utils::creatableNumOfReplayFileName() {
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;

	int exists[1000] = {};
	string path = getSavePath();
	char cpath[1024];
	sprintf(cpath, "%sリプレイデータ/*", path.c_str());

	hFind = FindFirstFile(cpath, &win32fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		return -1;
	}

	do {
		if (!(win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			char name[4] = {};
			strncpy(name, win32fd.cFileName, 3);
			int n = atoi(name);
			exists[n] = 1;
		}
	} while (FindNextFile(hFind, &win32fd));

	if (exists[0] == 0) {
		return 0;
	}
	for (int i = 0; i < 1000-1; i++) {
		if (exists[i] == 1 && exists[i+1] == 0) {
			return i + 1;
		}
	}
	return 999;
}

int Utils::maxNumOfReplayFileName() {
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;

	string path = getSavePath();
	char cpath[1024];
	sprintf(cpath, "%sリプレイデータ/*", path.c_str());

	hFind = FindFirstFile(cpath, &win32fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		return -1;
	}

	int max = -1;
	do {
		if (!(win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			char name[4] = {};
			strncpy(name, win32fd.cFileName, 3);
			int n = atoi(name);
			if (n > max) {
				max = n;
			}
		}
	} while (FindNextFile(hFind, &win32fd));
	return max;
}

// paramに負を与えると反対方向、sangleが開始角。
void Utils::DrawReversibleCircleGauge(const int x, const int y, const double size, const int handle, const double param, const double angle)
{
	//パラメータを取得
	float useparam = (float)fabs(param) / 25.0f;
	int rev = (param>0.0) * 2 - 1;

	//長さを取得
	int SX, SY;
	GetGraphSize(handle, &SX, &SY);

	//４つに分ける
	for (int i = 0; i<4; ++i) {
		//使用する角度分
		float ang = useparam;
		if (ang>1.0f)ang = 1.0f;

		//使用した分だけ消費
		useparam -= ang;

		//宣言
		VERTEX vec[3];

		//位置を指定
		vec[0].x = x + float((sinf(DX_PI_F + (i + 0)*0.5f*DX_PI_F*rev)*SX - 0.5f)*size);
		vec[0].y = y + float((cosf(DX_PI_F + (i + 0)*0.5f*DX_PI_F*rev)*SY - 0.5f)*size);

		vec[1].x = x + float((sinf(DX_PI_F + (i + ang)*0.5f*DX_PI_F*rev)*SX - 0.5f)*size);
		vec[1].y = y + float((cosf(DX_PI_F + (i + ang)*0.5f*DX_PI_F*rev)*SY - 0.5f)*size);

		vec[2].x = float(x - 0.5f*size);
		vec[2].y = float(y - 0.5f*size);

		//色は暫定
		for (int j = 0; j<3; ++j) {
			vec[j].a = 255;
			vec[j].r = 255;
			vec[j].g = 255;
			vec[j].b = 255;
		}

		//テクスチャ座標
		vec[0].u = sinf(DX_PI_F + (i + 0)*0.5f*DX_PI_F*rev + float(angle))*1.0f + 0.5f;
		vec[0].v = cosf(DX_PI_F + (i + 0)*0.5f*DX_PI_F*rev + float(angle))*1.0f + 0.5f;

		vec[1].u = sinf(DX_PI_F + (i + ang)*0.5f*DX_PI_F*rev + float(angle))*1.0f + 0.5f;
		vec[1].v = cosf(DX_PI_F + (i + ang)*0.5f*DX_PI_F*rev + float(angle))*1.0f + 0.5f;

		vec[2].u = 0.5f;
		vec[2].v = 0.5f;

		//描画
		DrawPolygon(vec, 3, handle, TRUE, FALSE);

		//角度を消費しきってたら中断
		if (useparam <= 0.0f)break;
	}
}

std::string Utils::getSavePath()
{
	TCHAR myDocumentsFolder[MAX_PATH];
	SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, NULL, myDocumentsFolder);
	string path(myDocumentsFolder);
	path += "/RemicalSoft/四聖龍神録2/";
	return path;
}

bool Utils::existsFolder(const char * path)
{
	switch (::GetFileAttributes(TEXT(path))) {
	case FILE_ATTRIBUTE_DIRECTORY: return true;
	}
	return false;
}

