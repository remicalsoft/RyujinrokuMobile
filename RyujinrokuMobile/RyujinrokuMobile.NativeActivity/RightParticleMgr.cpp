#include "RightParticleMgr.h"

using namespace std;

RightParticleMgr::RightParticleMgr(std::shared_ptr<Context> context) : Drawable(context)
{
    _img = LoadGraph("menu.back_particle.png");
    _counter = 0;
}

RightParticleMgr::~RightParticleMgr()
{
    DeleteGraph(_img);
}

bool RightParticleMgr::update()
{
    _counter++;
    // １フレーム目の描画時に十分パーティクルが存在するように最初だけ沢山更新する
    if (_counter == 1) {
        for (int i = 0; i < 100; i++) {
            update();
        }
    }
    for (int i = 0; i < 50; i++) {
        _list.emplace_back(make_shared<RightParticle>(_context, 791, 475, _img));
    }
    for (auto it = _list.begin(); it != _list.end();) {
        if ((*it)->update() == false) {
            it = _list.erase(it);
        }
        else {
            ++it;
        }
    }
    return true;
}

void RightParticleMgr::draw() const
{
    SetDrawMode(DX_DRAWMODE_BILINEAR);
    for (auto particle : _list) {
        particle->draw();
    }
    SetDrawMode(DX_DRAWMODE_NEAREST);
}
