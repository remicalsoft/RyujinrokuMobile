#include <DxLib.h>
#include<cassert>
#include"Background02.h"
#include"tinyxml2.h"
#include"SpriteRenderer.h"
#include"Camera.h"
#include"Keyboard.h"

// マテリアルの働きに関しては
// http://hpcgi2.nifty.com/natupaji/bbs/patio.cgi?mode=view&no=2019

Background02::MapModelTask::MapModelTask(std::vector<int> imgHandle, tinyxml2::XMLElement* root, VECTOR pos) {
	this->imgHandle = imgHandle;
	this->pos = pos;
	this->offset = VGet(0, 0, 0);
	for (const tinyxml2::XMLNode* node = root->FirstChild(); node; node = node->NextSibling()) {
		const tinyxml2::XMLElement* element = node->ToElement();
		if (element) {
			if (strcmp(element->Name(), "SpriteRenderer") == 0) {
				const char* name = element->Attribute("name");
				if (name != NULL && strcmp("effect_light", name) == 0) {
					auto sprite_anim = new SpriteAnimation();
					sprite_anim->loadXmlElement(element);
					int texIndex = sprite_anim->getObjectId();
					sprite_anim->addImage(this->imgHandle[6 + 0]);
					sprite_anim->addImage(this->imgHandle[6 + 1]);
					sprite_anim->addImage(this->imgHandle[6 + 2]);
					sprite_anim->addImage(this->imgHandle[6 + 3]);
					sprite_anim->getMaterial().Diffuse = GetColorF(1.0f, 0.2f, 0.0f, 1.0f);
					sprite_anim->getMaterial().Emissive = GetColorF(1.0f, 0.2f, 0.0f, 1.0f);
					this->objList.push_back(sprite_anim);
					this->objPosList.push_back(sprite_anim->getPos());
				}
				else {
					auto sprite_renderer = new SpriteRenderer();
					sprite_renderer->loadXmlElement(element);
					int texIndex = sprite_renderer->getObjectId();
					sprite_renderer->setHandle(this->imgHandle[texIndex]);
					sprite_renderer->getMaterial().Diffuse = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
					sprite_renderer->getMaterial().Emissive = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
					this->objList.push_back(sprite_renderer);
					this->objPosList.push_back(sprite_renderer->getPos());
				}
			}
		}
	}
}

Background02::MapModelTask::~MapModelTask() {
	for (auto obj : this->objList) {
		delete obj;
	}
	this->objList.clear();
}

void Background02::MapModelTask::setOffset(VECTOR ofs) {
	this->offset = ofs;
}

bool Background02::MapModelTask::update() {
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

void Background02::MapModelTask::draw() {
	for (unsigned int i = 0; i < this->objList.size(); i++) {
		this->objList[i]->draw();
	}
}

Background02::Background02() {
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	tinyxml2::XMLDocument doc;
	doc.LoadFile("dat2/xml/background/02/stage.txt");
	auto root = doc.FirstChildElement("ModelRoot");
	assert(root != NULL);
	for (const tinyxml2::XMLNode* node = root->FirstChild(); node; node = node->NextSibling()) {
		const tinyxml2::XMLElement* element = node->ToElement();
		if (element) {
			int cmp = strcmp("Texture", element->Name());
			if (cmp == 0) {
				int img = LoadGraph(element->GetText());
				if (img != -1) {
					this->imgHandle.push_back(img);
				}
			}
		}
	}

	auto cameraXml = root->FirstChildElement("Camera");
	assert(cameraXml != NULL);
	this->camera = new Camera(cameraXml);
	this->tasklist.push_back(new MapModelTask(this->imgHandle, root, VGet(0, 0, 0)));
	this->tasklist.push_back(new MapModelTask(this->imgHandle, root, VGet(0, 1024, 0)));
	this->tasklist.push_back(new MapModelTask(this->imgHandle, root, VGet(0, 2048, 0)));
	this->update();
	this->draw();
}

Background02::~Background02() {
	for (auto img : this->imgHandle) {
		DeleteGraph(img);
	}
	for (std::list<MapModelTask*>::iterator it = this->tasklist.begin(); it != this->tasklist.end();) {
		delete (*it);
		it = this->tasklist.erase(it);
	}
	delete this->camera;
}

bool Background02::update() {
	bool ret = Background::update();
	for (auto task : this->tasklist) {
		task->setOffset(this->getResultPos());
		task->update();
	}

	auto pos = this->getPos();
	pos.y -= 2.0f;
	if (pos.y <= -1024) {
		pos.y = 0;
	}
	this->setPos(pos);
	this->camera->update();
	return ret;
}

void Background02::draw() {
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	for (auto task : this->tasklist) {
		task->draw();
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
}
