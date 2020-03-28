#include "AbstractScene.h"

/*!
@brief コンストラクタ
@param impl シーン変更のリスナー
@param parameter 前のシーンから渡されたパラメータ
*/
AbstractScene::AbstractScene(std::shared_ptr<Context> context, IOnSceneChangedListener* impl, const Parameter& parameter) : Drawable(context),
    _implSceneChanged(impl)
{
}
