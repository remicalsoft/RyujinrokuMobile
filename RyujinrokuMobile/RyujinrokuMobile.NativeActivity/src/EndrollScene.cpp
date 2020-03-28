#include "EndrollScene.h"
#include <DxLib.h>
#include "Pad.h"
#include "Define.h"
#include "SavedData.h"
#include "BGM.h"

static const char* STAFF[][10] =
{
	{"メインプログラマー",			"Dixq", 0, },
	{"メイングラフィック制作者",	"マッす",0, },
	{"サブグラフィック制作者",		"Yulii","やっぽん","ファンタＧ",0, },
	{"背景制作",					"Dixq","せんちゃ",0, },
	{"弾幕メイン制作者",			"Dixq",0, },
	{"弾幕制作協力者",				"アメヒルネ","宙羽最",0, },
	{"音楽作曲者",					"アメヒルネ",0, },
	{"音楽編曲者",					"moiz",0, },
	{"効果音作成者",				"moiz",0, },
	{"シナリオ原作者",				"Dixq",0, },
	{"シナリオ脚本者",				"壱刀斎",0, },
	{"シナリオレビュワー",			"宙羽最","issssei","ますけん",0, },
	{"キャラデザイナー",			"Dixq","マッす",0, },
	{"プログラム制作協力者",		"宙羽最","アメヒルネ",0, },
	{"素材提供サイト様",			"Music-Note.jp様","Senses Circuit様","dbuMusic様","ポケットサウンド様","紺碧の世界に夜露死苦様","君津市のデザイン屋様","　",0, },
	{"　",							"　",0, },
	{"プロデューサー",				"Dixq",0, },
	{"　",							"　",0, },
	{"　",							"　",0, },
	{"制作",						"RemicalSoft",0,},
	{0,},
};

using namespace std;

EndrollScene::EndrollScene(ISceneChangedListener *impl, ScenePrmBase * prm) : Scene(impl)
{
	_staffID = 0;
	_nameN= 0;
	_counter = 0;
	_isNameShowing = false;
	_intervalCounter = 0;
	_isRegisterable = true;
	_endrollImage = nullptr;
	_endrollImageN = 0;
	_font = CreateFontToHandle(FONT, 32, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_bgm = LoadSoundMem("dat/bgm/endroll/endroll.ogg");
	SavedData::getIns()->markPlayedMusic(eMusicType_Endroll);

	int volume = BGM::getIns()->getVolume();
	ChangeVolumeSoundMem(volume * 255 / 100, _bgm);
}


EndrollScene::~EndrollScene()
{
	DeleteFontToHandle(_font);
	DeleteSoundMem(_bgm);
	if (_endrollImage != nullptr) {
		delete _endrollImage;
	}
}

bool EndrollScene::update()
{
	if (_counter==0) {
		PlaySoundMem(_bgm, DX_PLAYTYPE_BACK);
	}
	_counter++;
	if (_isRegisterable) {
		if (_counter>180) {
			_intervalCounter++;
		}
		if (!_isNameShowing) {
			if (_intervalCounter == 150) {
				NameBullet *p = new NameBullet(_font, 100, WIN_H + 20.f, STAFF[_staffID][0], GetColor(255, 255, 0));
				_list.push_back(shared_ptr<NameBullet>(p));
				_intervalCounter = 0;
				_isNameShowing = !_isNameShowing;
				_nameN++;
			}
		}
		else {
			if (_intervalCounter == 80) {
				NameBullet *p = new NameBullet(_font, 200, WIN_H + 20.f, STAFF[_staffID][_nameN], GetColor(200, 200, 200));
				_list.push_back(shared_ptr<NameBullet>(p));
				_intervalCounter = 0;
				_nameN++;
				if (STAFF[_staffID][_nameN] == 0) {
					_isNameShowing = !_isNameShowing;
					_nameN = 0;
					_staffID++;
					if (STAFF[_staffID][_nameN] == 0) {
						_isRegisterable = false;
					}
				}
			}
		}
	}
	if (_counter > 240) {
		if (_endrollImage == nullptr || !_endrollImage->update()) {
			if (_endrollImageN<=12) {
				char path[256];
				sprintf(path, "dat/image/endroll/%02d.png", _endrollImageN);
				_endrollImage = new EndrollImage(path);
				_endrollImageN++;
			}
			else if(_endrollImageN==13) {
				_endrollImage = new EndrollImage("dat/image/endroll/tobecontinued.png", true);
				_endrollImageN++;
			}
			else {
				StopSoundMem(_bgm);
				_implSceneChanged->onSceneChanged(eScene::Menu, false, nullptr);
				return false;
			}
		}
	}
	for (list<shared_ptr<NameBullet>>::iterator it = _list.begin(); it != _list.end();) {
		if ((*it)->update() == false) {
			it = _list.erase(it);
		}
		else {
			it++;
		}
	}
	if (Pad::getIns()->get(ePad::start) == 1) {
		StopSoundMem(_bgm);
		_implSceneChanged->onSceneChanged(eScene::Menu, false, nullptr);
	}
	return false;
}

void EndrollScene::draw()
{
	DrawString(900, 0, "Esc(スタートボタン)でスキップ", GetColor(155, 155, 155));
	for (auto b : _list) {
		b->draw();
	}
	if (_endrollImage != nullptr) {
		_endrollImage->draw();
	}
}
