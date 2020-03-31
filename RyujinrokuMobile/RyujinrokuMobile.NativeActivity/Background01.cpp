#include "Background01.h"
#include "Define.h"
#include <DxLib.h>

using namespace std;

const static int START_N = -1;
const static int END_N = 7;

Background01::Background01(shared_ptr<Context> context) : Drawable(context)
{
    _handle[0] = LoadGraph("back.00_fusuma.png");
    _handle[1] = LoadGraph("back.00_floor.png");
    _handle[2] = _handle[0];
    _handle[3] = 0;
    for (int t = 0; t<Surface::DATANUM; t++) {
        for (int z = START_N; z<END_N; z++) {
            _list.push_back(make_shared<Surface>(z, _handle[t], t));
        }
    }
    {
        SetCameraNearFar(1.0f, 10000.f);		//カメラの有効範囲を設定
        SetCameraScreenCenter(Define::FIELD_W / 2.f, Define::FIELD_H / 2.f);
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

Background01::~Background01()
{
    for (auto g : _handle) {
        DeleteGraph(g);
    }
}

bool Background01::update() 
{
    for (auto srf : _list) {
        srf->update();
        if (srf->getZ() < srf->getZWid()*(START_N - 1)) {
            srf->addZ((END_N - START_N) * srf->getZWid());
        }
    }
    return true;
}

void Background01::draw() const
{
    VECTOR offset;//まだ何もない。画面を揺らすようの物
    offset.x = offset.y = offset.z = 0;
    draw(offset);
}

void Background01::draw(VECTOR offset) const
{
    SetDrawMode(DX_DRAWMODE_BILINEAR);
    for (auto srf : _list) {
        srf->draw(offset);
    }
    SetDrawMode(DX_DRAWMODE_NEAREST);
}
