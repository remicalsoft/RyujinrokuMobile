#include <DxLib.h>
#include <cassert>
#include"BackgroundEX.h"
#include"tinyxml2.h"
#include"SpriteRenderer.h"
#include"Camera.h"
#include"Keyboard.h"
#include"Define.h"
#include"Utils.h"

#define DELTA_Y (-200)	//背景が切れてしまうのでちょっとずつずらす（SAI）

BackgroundEX::MapModelTask::MapModelTask(std::vector<int> imgHandle, std::vector<int> modelHandle, tinyxml2::XMLElement* root, VECTOR pos) {
	this->imgHandle = imgHandle;
	this->modelHandle = modelHandle;
	this->pos = pos;
	this->offset = VGet(0, 0, 0);
	for (const tinyxml2::XMLNode* node = root->FirstChild(); node; node = node->NextSibling()) {
		const tinyxml2::XMLElement* element = node->ToElement();
		if (element) {
			if (strcmp(element->Name(), "SpriteRenderer") == 0) {
				auto newObj = new SpriteRenderer();
				newObj->loadXmlElement(element);
				int texIndex = newObj->getObjectId();
				newObj->setHandle(this->imgHandle[texIndex]);
				newObj->getMaterial().Diffuse = GetColorF(0.2f, 0.2f, 0.2f, 1.0f);
				this->objList.push_back(newObj);
				this->objPosList.push_back(newObj->getPos());
			}
			if (strcmp(element->Name(), "MV1Renderer") == 0) {
				auto newObj = new MV1Renderer();
				newObj->loadXmlElement(element);
				int modelIndex = newObj->getObjectId();
				newObj->changeModel(this->modelHandle[modelIndex]);
				this->objList.push_back(newObj);
				this->objPosList.push_back(newObj->getPos());
			}
		}
	}
}

BackgroundEX::MapModelTask::~MapModelTask() {
	for (auto obj : this->objList) {
		delete obj;
	}
	this->objList.clear();
}

void BackgroundEX::MapModelTask::setOffset(VECTOR ofs) {
	this->offset = ofs;
}

bool BackgroundEX::MapModelTask::update() {
	auto p = this->pos;
	p.x += this->offset.x;
	p.y += this->offset.y;
	p.z += this->offset.z;

	for (unsigned int i = 0; i < this->objList.size(); i++) {
		auto homePos = this->objPosList[i];
		homePos.x += p.x;
		homePos.y += p.y;
		homePos.z += p.z;
		this->objList[i]->setPos(homePos);
		this->objList[i]->update();
	}
	return true;
}

void BackgroundEX::MapModelTask::draw() {
	for (unsigned int i = 0; i < this->objList.size(); i++) {
		this->objList[i]->draw();
	}
}

BackgroundEX::BackgroundEX() {
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	tinyxml2::XMLDocument doc;
	doc.LoadFile("dat2/xml/background/06/stage.txt");
	auto root = doc.FirstChildElement("ModelRoot");
	auto cameraXml = root->FirstChildElement("Camera");
	assert(root);
	assert(cameraXml);
	for (const tinyxml2::XMLNode* node = root->FirstChild(); node; node = node->NextSibling()) {
		const tinyxml2::XMLElement* element = node->ToElement();
		if (element) {
			if (strcmp("Texture", element->Name()) == 0) {
				int img = LoadGraph(element->GetText());
				if (img != -1) {
					this->imgHandle.push_back(img);
				}
			}
			if (strcmp("Model", element->Name()) == 0) {
				int model = MV1LoadModel(element->GetText());
				if (model != -1) {
					this->modelHandle.push_back(model);
				}
			}
		}
	}

	this->camera = new Camera(cameraXml);
	this->tasklist.push_back(new MapModelTask(this->imgHandle, this->modelHandle, root, VGet(0, 1024 * 0 + DELTA_Y, 0)));
	this->tasklist.push_back(new MapModelTask(this->imgHandle, this->modelHandle, root, VGet(0, 1024 * 1 + DELTA_Y, 0)));
	this->tasklist.push_back(new MapModelTask(this->imgHandle, this->modelHandle, root, VGet(0, 1024 * 2 + DELTA_Y, 0)));
	this->tasklist.push_back(new MapModelTask(this->imgHandle, this->modelHandle, root, VGet(0, 1024 * 3 + DELTA_Y, 0)));
	this->tasklist.push_back(new MapModelTask(this->imgHandle, this->modelHandle, root, VGet(0, 1024 * 4 + DELTA_Y, 0)));

	defaultCenter = camera->getCenter();
	defaultPos = camera->getPos();
	defaultV = camera->getV();
	defaultH = camera->getH();
	defaultT = camera->getT();
	count = 0;

	this->update();
	this->draw();
}

BackgroundEX::~BackgroundEX() {
	for (auto img : this->imgHandle) {
		DeleteGraph(img);
	}
	for (auto model : this->modelHandle) {
		MV1DeleteModel(model);
	}
	for (std::list<MapModelTask*>::iterator it = this->tasklist.begin(); it != this->tasklist.end();) {
		delete (*it);
		it = this->tasklist.erase(it);
	}
	delete this->camera;
}

bool BackgroundEX::update() {
	bool ret = Background::update();
	for (auto task : this->tasklist) {
		task->setOffset(this->getResultPos());
		task->update();
	}

	auto pos = this->getPos();
	pos.y -= 8.0f;
	if (pos.y <= -1024+ DELTA_Y) {
		pos.y = DELTA_Y;
	}
	this->setPos(pos);


	//カメラをゆらゆらさせる

	double x=0, y=0;
	double range = 200;
	Utils::getCycloid(x, y, range, range / 11 * 5, range / 11 * 3, PI2*count/2200);

	camera->setPos(defaultPos.x, defaultPos.y+y+500, defaultPos.z+x+200);
	camera->setCenter(defaultCenter.x, defaultCenter.y);
	camera->setVHT(defaultV + PI/100* sin(PI2*count/450)+PI/100,defaultH + PI / 80 * sin(PI2*count / 370),defaultT + PI / 70 * sin(PI2*count / 870));



	this->camera->update();

	count++;
	return ret;
}

void BackgroundEX::draw() {
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	int R, G, B;
	GetFogColor(&R,&G,&B);
	DrawBox(0,0, OUT_W, OUT_H,GetColor(R,G,B),TRUE);
	for (auto task : this->tasklist) {
		task->draw();
	}
//	VECTOR v2 = GetLightDirection();
//	DrawFormatString(500, 430, GetColor(255, 255, 255), "%.3f,%3.f,%3.f", v2.x, v2.y, v2.z);

	SetDrawMode(DX_DRAWMODE_NEAREST);
}
