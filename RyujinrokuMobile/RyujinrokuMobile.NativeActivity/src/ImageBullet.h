#pragma once
#include "Singleton.h"
#include <vector>
#include <DxLib.h>

enum eBulletType {
	eSmall,		//0
	eBarrier,	//1
	eSparkSmall,//2
	eKome,		//3
	eUmaibo,	//4
	eSparkBig,	//5
	eKodama,	//6
	eYosei,		//7
	eRing,		//8
	eAme,		//9
	eTama,		//10
	eOdama,		//11
	eLaser,		//12
	eOfuda,		//13
	eStar,		//14
	eRain,		//15
	eRainbow,	//16

	eTypeNum,
};

const float WEIGHT = 0.71;
const float BULLET_RANGE[] = {
	 5.5f * WEIGHT,//Small
	 4.0f * WEIGHT,//Barrier
	 4.0f * WEIGHT,//SparkSmall
	 5.0f * WEIGHT,//Kome
	 4.5f * WEIGHT,//Umaibo
	 9.0f * WEIGHT,//SparkBig
	10.0f * WEIGHT,//Kodama	//実測12.0f
	 6.5f * WEIGHT,//Yosei
	 9.0f * WEIGHT,//Ring
	11.0f * WEIGHT,//Ame
	19.5f * WEIGHT,//Tama	//実測23.0f
	38.0f * WEIGHT,//Odama
	 2.8f * WEIGHT,//Laser
	10.0f * WEIGHT,//Ofuda
	 5.0f * WEIGHT,//Star
	 6.0f * WEIGHT,//Rain
	 9.0f * WEIGHT,//Rainbow
};

const float BULLET_SORT[] = {
	3,//Small
	4,//Barrier
	4,//SparkSmall
	4,//Kome
	5,//Umaibo
	5,//SparkBig
	8,//Kodama
	8,//Yosei
	10,//Ofuda
	15,//Ring
	20,//Ame
	22,//Tama
	32,//Odama
	3,//Laser
	5,//Star
	5,//Rain
	8,//Rainbow
};

enum eBulletColor {
	eBlue,
	ePurple,
	ePink,
	eOrenge,
	eYellow,
	eGreen,
	eLime,
	eAqua,
	eColorNum,
};

class wh_t {
public:
	int w, h;
	wh_t() {
		w = 0;
		h = 0;
	}
	wh_t(int w, int h) {
			this->w = w;
		this->h = h;
	}
};

class ImageBullet :	public Singleton<ImageBullet> {

	std::vector<int*> _list;
	std::vector<wh_t*> _whList;

public:
	ImageBullet() {
		_whList.push_back(new wh_t(16, 16));//0
		_whList.push_back(new wh_t(28, 30));//1
		_whList.push_back(new wh_t(38, 38));//2
		_whList.push_back(new wh_t(18, 31));//3
		_whList.push_back(new wh_t(64, 64));//4
		_whList.push_back(new wh_t(76, 76));//5
		_whList.push_back(new wh_t(32, 32));//6
		_whList.push_back(new wh_t(54, 54));//7
		_whList.push_back(new wh_t(36, 36));//8
		_whList.push_back(new wh_t(30, 57));//9
		_whList.push_back(new wh_t(62, 62));//10
		_whList.push_back(new wh_t(108, 108));//11
		_whList.push_back(new wh_t(12, 240));//12
		_whList.push_back(new wh_t(28, 32));//13
		_whList.push_back(new wh_t(34, 34));//14
		_whList.push_back(new wh_t(20, 34));//15
		_whList.push_back(new wh_t(20, 20));//16
		myLoadDivGraph("dat/image/bullet/00.small.png");
		myLoadDivGraph("dat/image/bullet/01.barrier.png");
		myLoadDivGraph("dat/image/bullet/02.sparkSmall.png");
		myLoadDivGraph("dat/image/bullet/03.kome.png");
		myLoadDivGraph("dat/image/bullet/04.umaibo.png");
		myLoadDivGraph("dat/image/bullet/05.sparkBig.png");
		myLoadDivGraph("dat/image/bullet/06.kodama.png");
		myLoadDivGraph("dat/image/bullet/07.yosei.png");
		myLoadDivGraph("dat/image/bullet/08.ring.png");
		myLoadDivGraph("dat/image/bullet/09.ame.png");
		myLoadDivGraph("dat/image/bullet/10.tama.png");
		myLoadDivGraph("dat/image/bullet/11.odama.png");
		myLoadDivGraph("dat/image/bullet/12.laser.png");
		myLoadDivGraph("dat/image/bullet/13.ofuda.png");
		myLoadDivGraph("dat/image/bullet/14.star.png");
		myLoadDivGraph("dat/image/bullet/15.rain.png");
		myLoadDivGraph("dat/image/bullet/16.rainbow.png");
	}
	void load() {}
	void myLoadDivGraph(char* fname) {
		int id = _list.size();
		wh_t* size = _whList[id];
		int *bullets = new int[8];
		LoadDivGraph(fname, 8, 8, 1, size->w, size->h, bullets);
		_list.push_back(bullets);
	}
//	int get(eType type, eColor color) {
	int get(int type, int color) {
		if (type < 0 || eTypeNum <= type) {
			printfDx("弾のtypeが不正です：%d\n",type);
			return 0;
		}
		if (color < 0 || eColorNum <= color) {
			printfDx("弾のcolorが不正です：%d\n",color);
			return 0;
		}
		return _list[type][color];
	}
	const wh_t* getSize(int type) {
		if (type<0||_whList.size()<=type) {
			printfDx("wh_tのgetSizeの指定が間違っています");
			return nullptr;
		}
		return _whList[type];
	}
};
