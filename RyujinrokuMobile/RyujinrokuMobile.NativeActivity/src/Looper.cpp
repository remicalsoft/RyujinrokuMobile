#include "Looper.h"
#include "Define.h"
#include "GameScene.h"
#include "OpScene.h"
#include "StoryPreGameScene.h"
#include "MenuScene.h"
#include "LevelSelectScene.h"
#include "LevelSelectSceneEX.h"
#include "StorySelectScene.h"
#include "ScenePrmBase.h"
#include "StoryScene.h"
#include "MusicRoomScene.h"
#include "EdScene.h"
#include "Utils.h"
#include "SE.h"
#include "ExOpScene.h"
#include "ExEdScene.h"
#include "PhOpScene.h"
#include "PhEdScene.h"
#include "GameData.h"
#include "EndrollScene.h"
#include "Toast.h"
#include "PracticeSelectScene.h"
#include "SpellPracticeScene.h"
#include "ConfigScene.h"
#include "ShoSelectScene.h"
#include "StoreScene.h"
#include "StoreBuyScene.h"
#include "LogoScene.h"
#include "ReplayScene.h"
#include "Replayer.h"
#include "ContinueScene.h"
#include "ShoIntroScene.h"
#include "DebugMode.h"
#include "ChapterSelectScene.h"
#include "ItemEquipScene.h"

using namespace std;

Looper::Looper()
{
//	Utils::showNowLoading();

	GameScenePrm *prm = nullptr;
	prm = new GameScenePrm(eStage1, eLevel_Easy);

//	_scene.push_back(shared_ptr<Scene>(new LogoScene(this, nullptr)));

//	_scene.push_back(shared_ptr<Scene>(new GameScene(this, prm)));
//	_scene.push_back(shared_ptr<Scene>(new ItemEquipScene(this, nullptr)));
//	_scene.push_back(shared_ptr<Scene>(new ReplayScene(this, nullptr)));
//	_scene.push_back(shared_ptr<Scene>(new MenuScene(this, nullptr)));
//	_scene.push_back(shared_ptr<Scene>(new StoreScene(this, nullptr)));
//	_scene.push_back(shared_ptr<Scene>(new EndrollScene(this, nullptr)));

//	_scene.push_back(shared_ptr<Scene>(new OpScene(this, nullptr)));
	_scene.push_back(shared_ptr<Scene>(new EdScene(this, nullptr)));
//  _scene.push_back(shared_ptr<Scene>(new ExOpScene(this, nullptr)));
//  _scene.push_back(shared_ptr<Scene>(new ExEdScene(this, nullptr)));
//	_scene.push_back(shared_ptr<Scene>(new PhEdScene(this, nullptr)));

//  _scene.push_back(shared_ptr<Scene>(new StoryPreGameScene(this, nullptr)));
//	_scene.push_back(shared_ptr<Scene>(new StorySelectScene(this, nullptr)));
//	_scene.push_back(shared_ptr<Scene>(new ConfigScene(this, nullptr)));
	_scene.back()->initialize();


	if (prm != nullptr) {
		delete prm;
	}
}

Looper::~Looper()
{
}

/*!
	@brief シーンのチェンジ
	@note 各シーンクラスからコールバックされる
	@retval stack : trueならシーンをスタックする(トップメニュー画面→のように)
	@retval stack : falseならスタックをクリアする(ゲーム画面のように下のレイヤーにシーンが無い場合)
*/
void Looper::onSceneChanged(eScene scene, bool stack, ScenePrmBase* prm, int addDeleteLayerN){

	switch (scene) {
	case ExOp:
	case Op:
	case Ed:
	case StoryPreGame:
	case Game:
		Utils::showNowLoading();
		break;
	}

	if (!stack) {
		_scene.clear();
	}
	for (int i = 0; i < addDeleteLayerN; i++) {
		_scene.pop_back();
	}
	switch(scene){
	case Logo:
		_scene.push_back(shared_ptr<Scene>(new LogoScene(this, prm)));
		break;
	case Menu:
		_scene.push_back(shared_ptr<Scene>(new MenuScene(this, prm)));
		break;
	case Replay:
		_scene.push_back(shared_ptr<Scene>(new ReplayScene(this, prm)));
		break;
	case Op:
		_scene.push_back(shared_ptr<Scene>(new OpScene(this, prm)));
		break;
	case Ed:
		_scene.push_back(shared_ptr<Scene>(new EdScene(this, prm)));
		break;
	case ExOp:
		_scene.push_back(shared_ptr<Scene>(new ExOpScene(this, prm)));
		break;
	case ExEd:
		_scene.push_back(shared_ptr<Scene>(new ExEdScene(this, prm)));
		break;
	case PhOp:
		_scene.push_back(shared_ptr<Scene>(new PhOpScene(this, prm)));
		break;
	case PhEd:
		_scene.push_back(shared_ptr<Scene>(new PhEdScene(this, prm)));
		break;
	case StoryPreGame:
		_scene.push_back(shared_ptr<Scene>(new StoryPreGameScene(this, prm)));
		break;
	case Game:
		_scene.push_back(shared_ptr<Scene>(new GameScene(this, prm)));
		break;
	case ShoSelect:
		_scene.push_back(shared_ptr<Scene>(new ShoSelectScene(this, prm)));
		break;
	case LevelSelect:
		_scene.push_back(shared_ptr<Scene>(new LevelSelectScene(this, prm)));
		break;
	case LevelSelectEX:
		_scene.push_back(shared_ptr<Scene>(new LevelSelectSceneEX(this, prm)));
		break;
	case PracticeStageSelect:
		_scene.push_back(shared_ptr<Scene>(new PracticeSelectScene(this, prm)));
		break;
	case SpellPracticeSelect:
		_scene.push_back(shared_ptr<Scene>(new SpellPracticeScene(this, prm)));
		break;
	case StorySelect:
		_scene.push_back(shared_ptr<Scene>(new StorySelectScene(this, prm)));
		break;
	case Story:
		_scene.push_back(shared_ptr<Scene>(new StoryScene(this, prm)));
		break;
	case ToBeContinued:
		_scene.push_back(shared_ptr<Scene>(new ContinueScene(this, prm)));
		break;
	case Music:
		_scene.push_back(shared_ptr<Scene>(new MusicRoomScene(this, prm)));
		break;
	case KeyConfig:
		_scene.push_back(shared_ptr<Scene>(new ConfigScene(this, prm)));
		break;
	case Endroll:
		_scene.push_back(shared_ptr<Scene>(new EndrollScene(this, prm)));
		break;
	case Store:
		_scene.push_back(shared_ptr<Scene>(new StoreScene(this, prm)));
		break;
	case StoreBuy:
		_scene.push_back(shared_ptr<Scene>(new StoreBuyScene(this, prm)));
		break;
	case ShoIntro:
		_scene.push_back(shared_ptr<Scene>(new ShoIntroScene(this, prm)));
		break;
	case SelectChapter:
		_scene.push_back(shared_ptr<Scene>(new ChapterSelectScene(this, prm)));
		break;
	case ItemEquip:
		_scene.push_back(shared_ptr<Scene>(new ItemEquipScene(this, prm)));
		break;
	case SceneDelete:
		_scene.pop_back();
		break;
	case End:
		//nothing
		return;
	default: ERR("Looper::onSceneChangedで不明なscene");
	}
	if (_scene.back()!=nullptr) {
		_scene.back()->initialize();
	}
}

bool Looper::update()
{
	Replayer::getIns()->update();
	int n = Replayer::getIns()->getPlaySpeed();
	Replayer::getIns()->setFps(_fps.get());
	for (int i = 0; i < n; i++) {
		_scene.back()->update();
		if (_scene.size() == 0) {	//シーンが無くなったらアプリ終了
			return false;			//falseを返すとシステムマネージャーが終了する
		}
	}
	return true;
}

bool Looper::main() {
	if (!update()) {
		return false;
	}
	_scene.back()->draw();
	_fps.draw();
	_fps.wait();
	Toast::getIns()->update();
	Toast::getIns()->draw();
	DebugMode::getIns()->update();
	SE::getIns()->play();
	return true;
}
