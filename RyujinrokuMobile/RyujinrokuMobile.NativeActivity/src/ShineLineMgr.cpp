#include "ShineLineMgr.h"
#include "Define.h"
#include <DxLib.h>
#include "ShineLineIn.h"
#include "ShineLineOut.h"
#include "Utils.h"

using namespace std;

ShineLineMgr::ShineLineMgr(){
	_counter = 0;
	_imgShine = LoadGraph("dat/image/menu/shine.png");
//	LoadDivGraph("dat/image/menu/shine.png", 8, 8, 1, 100, 100, _imgShine);
}

ShineLineMgr::~ShineLineMgr(){
	list<ShineLine*>::iterator it = _list.begin();
    while( it != _list.end() ) {
		delete *it;
		it = _list.erase(it);
    }
	DeleteGraph(_imgShine);
//	for (int i = 0; i < 8; i++) {
//		DeleteGraph(_imgShine[i]);
//	}
}

void ShineLineMgr::regist() {
	float x = SHINE_X - GetRand(50000) / 100.f + 250;
	float y = SHINE_Y - GetRand(50000) / 100.f + 250;
	ShineLine *p = new ShineLineIn(x, y);
	_list.push_back(p);
	/*
	ShineLine *p = new ShineLineOut(SHINE_X,SHINE_Y);
	_list.push_back(p);
	*/
}

bool ShineLineMgr::update(){
	_counter++;
	if(_counter%1==0){
		regist();
		regist();
		regist();
	}
	list<ShineLine*>::iterator it = _list.begin();
    while( it != _list.end() ) {
		if((*it)->update()==false){
			delete *it;
			it = _list.erase(it);
		} else {
			++it;
		}
    }
	return true;
}

void ShineLineMgr::draw(){
	SetDrawBlendMode(DX_BLENDMODE_ADD, 64);
	for (int i = 0; i < 4; i++) {
		DrawRotaGraph(SHINE_X, SHINE_Y, 0.2+ randf(0.8), 0, _imgShine, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	for(auto a : _list){
		a->draw();
	}
}
