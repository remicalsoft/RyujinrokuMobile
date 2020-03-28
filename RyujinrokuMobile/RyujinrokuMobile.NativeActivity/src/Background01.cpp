#include <DxLib.h>
#include <cassert>
#include"Background01.h"
#include"Srf.h"
#include"tinyxml2.h"
#include"SpriteRenderer.h"
#include"Camera.h"

void Background01::MapModelTask::saveXml(tinyxml2::XMLDocument& doc) {
	auto root = doc.NewElement("MapRoot");
	doc.LinkEndChild(root);
	this->floor->saveXml("floor", root, doc);
	for (int i = 0; i < WOOD_COUNT; i++) {
		char name[64];
		sprintf_s<64>(name, "wood_%d", i);
		this->wood[i].saveXml(name, root, doc);
	}
}

void Background01::MapModelTask::loadXml(tinyxml2::XMLElement* root) {
	auto myRoot = root->FirstChildElement("MapRoot");
	this->floor->loadXml("floor", myRoot);
	for (int i = 0; i < WOOD_COUNT; i++) {
		char name[64];
		sprintf_s<64>(name, "wood_%d", i);
		this->wood[i].loadXml(name, myRoot);
	}
}

Background01::MapModelTask::MapModelTask( int grFloor, int grWood1, tinyxml2::XMLElement* root , VECTOR pos ) {
	this->currentEdit = -1;
	this->pos = pos;
	this->offset.x = 0;
	this->offset.y = 0;
	this->offset.z = 0;
	this->floor = new SpriteRenderer();
	this->wood = new SpriteRenderer[WOOD_COUNT];

	this->loadXml(root);
	this->floor->setHandle(grFloor);
	this->floor->setSize(1024, 1024);
	this->floor->setTrans(FALSE);
	this->floor->getMaterial().Diffuse = GetColorF(0.25f, 0.25f, 0.25f, 1);
	for (int i = 0; i < WOOD_COUNT; i++) {
		auto handle = grWood1;
		this->wood[i].setHandle(handle);
		this->wood[i].setSize(300, 400);
		this->wood[i].getMaterial().Diffuse = GetColorF(0.5f, 0.5f, 0.5f, 1);
		this->poslist[i] = this->wood[i].getPos();
	}
}

Background01::MapModelTask::~MapModelTask() {
	delete this->floor;
	delete[] this->wood;
}

void Background01::MapModelTask::setOffset(VECTOR ofs) {
	this->offset = ofs;
}

bool Background01::MapModelTask::update(){
	auto p = this->pos;
	p.x += this->offset.x;
	p.y += this->offset.y;
	p.z += this->offset.z;

	{
		this->floor->setPos(p);
		this->floor->update();
	}
	for (int i = 0; i < WOOD_COUNT; i++) {
		auto homePos = this->poslist[i];
		auto angle = this->wood[i].getAngle();
		homePos.x += p.x;
		homePos.y += p.y;
		homePos.z += p.z;
		this->wood[i].setPos(homePos);
		this->wood[i].setAngle(angle);
		this->wood[i].update();
	}
	return true;
}

void Background01::MapModelTask::draw(){
}

void Background01::MapModelTask::drawFloor() {
	this->floor->draw();
}

void Background01::MapModelTask::drawWood() {
	for (int i = 0; i < WOOD_COUNT; i++) {
		this->wood[i].draw();
	}
}

Background01::Background01() {
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	tinyxml2::XMLDocument doc;
	doc.LoadFile("dat2/xml/background/01/stage01.xml");
	auto root = doc.FirstChildElement("Root");
	auto camera = root->FirstChildElement("Camera");
	assert(root);
	this->handle1 = LoadGraph("dat/image/background/01/03.jpg");
	this->handle2 = LoadGraph("dat/image/background/01/02.png");

	this->camera = new Camera(camera);
	this->tasklist.push_back(new MapModelTask(this->handle1, this->handle2, root, VGet(0, 0, 0)));
	this->tasklist.push_back(new MapModelTask(this->handle1, this->handle2, root, VGet(0, 1024, 0)));
	this->tasklist.push_back(new MapModelTask(this->handle1, this->handle2, root, VGet(0, 2048, 0)));

	count=0;
}

Background01::~Background01() {
	DeleteGraph(this->handle1);
	DeleteGraph(this->handle2);
	delete this->camera;
	for (std::list<MapModelTask*>::iterator it = this->tasklist.begin(); it != this->tasklist.end();) {
		delete (*it);
		it = this->tasklist.erase(it);
	}
}

bool Background01::update() {
	bool ret = Background::update();
	this->camera->update();
	for (auto task : this->tasklist) {
		task->setOffset(this->getResultPos());
		task->update();
	}

	auto pos = this->getPos();
	pos.y -= 3.0f;
	if (pos.y <= -1024) {
		pos.y = 0;
	}
	this->setPos(pos);

	count++;
	return ret;
}

void Background01::draw() {
	if(count==0) return;	//最初の１回目は座標データが代入されていないため正しく描画されないのでスキップ
	SetDrawAlphaTest(DX_CMP_GREATER, 128);
	this->camera->draw();
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	for (auto task : this->tasklist) {
		task->drawFloor();
	}
	for (auto task : this->tasklist) {
		task->drawWood();
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
	SetDrawAlphaTest(-1, 0);
}
