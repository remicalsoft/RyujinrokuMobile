#pragma once

#include "Scene.h"
#include <vector>
#include "DxGUI.h"
#include "SpriteRenderer.h"
#include "Camera.h"


class TestScene : public Scene {
private:
	std::vector<DxGUI::Window*> gui;
	Camera* camera;
	DxGUI::MouseCursor* cursor;
	VECTOR pos;
	VECTOR angle;
	VECTOR scale;
	MATRIX m;
	int img;
public:
	TestScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~TestScene();
	void createTriangle();
	virtual bool update() override;
	virtual void draw() override;
};