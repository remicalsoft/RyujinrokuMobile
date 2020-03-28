#include <DxLib.h>
#include "BackgroundPH.h"

BackgroundPH::BackgroundPH(){
	_srfMgr = new SrfMgr05();
}

BackgroundPH::~BackgroundPH(){
	if( _srfMgr ){ delete _srfMgr; _srfMgr = nullptr; }
	SetFogEnable( FALSE ) ;
}

bool BackgroundPH::update(){
	Background::update();
	offset.x /= 10.f;
	offset.y /= 10.f;
	offset.z /= 10.f;
	_srfMgr->update();
	return true;
}

void BackgroundPH::draw(){
	_srfMgr->draw(this->offset);
}
