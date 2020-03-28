#include <DxLib.h>
#include "SrfMgr05.h"
#include "Define.h"

SrfMgr05::SrfMgr05(){
	_handle[0] = LoadGraph("dat/image/background/05/襖.png");
	_handle[1] = LoadGraph("dat/image/background/05/床.png");
	_handle[2] = _handle[0];
	_handle[3] = 0;
	for (int t = 0; t<eSRF00_DATANUM; t++) {
		for (int z = START_N; z<END_N; z++) {
			_list.push_back(new Srf(z, _handle[t], t));
		}
	}
	{
		SetCameraNearFar(1.0f, 10000.f);		//カメラの有効範囲を設定
		SetCameraScreenCenter(OUT_W/2, OUT_H/2);
		SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, -100.0f), VGet(0.0f, 0.0f, 0.0f));
		SetFogEnable(TRUE);
		SetFogColor(0, 0, 0);
		SetFogStartEnd(0.0f, 300.0f);
	}
	{
		MATERIALPARAM Material;
		Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
		Material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
		Material.Ambient = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
		Material.Emissive = GetColorF(1.0f, 1.0f, 1.0f, 0.0f);
		Material.Power = 20.0f;
		SetMaterialParam(Material);
		SetMaterialUseVertSpcColor(FALSE);
		SetMaterialUseVertDifColor(FALSE);
	}
}

SrfMgr05::~SrfMgr05() {
	for (int i = 0; i<eSRF00_DATANUM; i++) {
		DeleteGraph(_handle[i]);
		_handle[i] = 0;
		for (std::list<Srf*>::iterator it = _list.begin(); it != _list.end();) {
			delete (*it);
			it = _list.erase(it);
		}
	}
}

bool SrfMgr05::update() {
	for (auto srf : _list) {
		srf->update();
		if (srf->getZ() < srf->getZWid()*(START_N - 1)) {
			srf->addZ((END_N - START_N) * srf->getZWid());
		}
	}
	return true;
}

void SrfMgr05::draw(VECTOR offset) {
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	for (auto srf : _list) {
		srf->draw(offset);
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
}
