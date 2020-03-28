#include <DxLib.h>
#include <cassert>
#include"Background04.h"
#include"tinyxml2.h"
#include"SpriteRenderer.h"
#include"Camera.h"
#include"Keyboard.h"

#define DELTA_Y (-200)	//背景が切れてしまうのでちょっとずつずらす

Background04::MapModelTask::MapModelTask(std::vector<int> imgHandle, std::vector<int> modelHandle, tinyxml2::XMLElement* root, VECTOR pos) {
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

Background04::MapModelTask::~MapModelTask() {
	for (auto obj : this->objList) {
		delete obj;
	}
	this->objList.clear();
}

void Background04::MapModelTask::setOffset(VECTOR ofs) {
	this->offset = ofs;
}

bool Background04::MapModelTask::update() {
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

void Background04::MapModelTask::draw() {
	for (unsigned int i = 0; i < this->objList.size(); i++) {
		this->objList[i]->draw();
	}
}

Background04::Background04() {
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	tinyxml2::XMLDocument doc;
	doc.LoadFile("dat2/xml/background/04/stage.txt");
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

	this->update();
	this->draw();
}

Background04::~Background04() {
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

bool Background04::update() {
	bool ret = Background::update();
	for (auto task : this->tasklist) {
		task->setOffset(this->getResultPos());
		task->update();
	}

	auto pos = this->getPos();
	pos.y -= 1.0f;
	if (pos.y <= -1024 + DELTA_Y) {
		pos.y = DELTA_Y;
	}
	this->setPos(pos);
	this->camera->update();
	return ret;
}

void Background04::draw() {
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	for (auto task : this->tasklist) {
		task->draw();
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
}
