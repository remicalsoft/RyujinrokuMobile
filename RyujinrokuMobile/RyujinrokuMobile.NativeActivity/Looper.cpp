#include "Looper.h"
#include "TitleScene.h"
#include "TouchEvent.h"
#include "Image.h"
#include "Font.h"
//#include "Error.h"
//#include "GameScene.h"
//#include "Macro.h"

using namespace std;

Looper::Looper()
{
    _context = make_shared<Context>(Image::getIns(), TouchEvent::getIns(), Font::getIns());
    _fps = make_unique<Fps>(_context);
    Image::getIns()->load();
    Font::getIns()->load();
    Parameter parameter;
    _sceneStack.push(make_shared<TitleScene>(_context, this, parameter)); //ゲーム画面シーンを作ってpush
}

/*!
@brief スタックのトップのシーンの処理をする
*/
bool Looper::loop() 
{
    TouchEvent::getIns()->update(); //タッチイベントの更新
    _sceneStack.top()->update();    //スタックのトップのシーンを更新
    _sceneStack.top()->draw();      //スタックのトップのシーンを描画
    _fps->draw();                    //FPSの表示
    _fps->update();                  //設定したFPSになるように待機
    return true;
}

/*!
@brief シーン変更(各シーンからコールバックされる)
@param scene 変更するシーンのenum
@param parameter 前のシーンから引き継ぐパラメータ
@param stackClear 現在のシーンのスタックをクリアするか
*/
void Looper::onSceneChanged(const eScene scene, const Parameter& parameter, const bool stackClear)
{
    if (stackClear) {//スタッククリアなら
        while (!_sceneStack.empty()) {//スタックを全部ポップする(スタックを空にする)
            _sceneStack.pop();
        }
    }
    switch (scene) {
    case Title:
        _sceneStack.push(make_shared<TitleScene>(_context, this, parameter));
        break;
    //case Game:
    //    _sceneStack.push(make_shared<GameScene>(this, parameter));
    //    break;
    default:
//      ERR("あるはずのないシーンが呼ばれました");
        break;
    }
}
