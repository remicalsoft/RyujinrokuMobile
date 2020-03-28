#include <DxLib.h>
#include "Background05.h"

Background05::Background05(){
	_srfMgr = new SrfMgr05();
}

Background05::~Background05(){
	if( _srfMgr ){ delete _srfMgr; _srfMgr = nullptr; }
	SetFogEnable( FALSE ) ;
}

bool Background05::update(){
	Background::update();
	offset.x /= 10.f;
	offset.y /= 10.f;
	offset.z /= 10.f;
	_srfMgr->update();
	return true;
}

void Background05::draw(){
	_srfMgr->draw(this->offset);
}
