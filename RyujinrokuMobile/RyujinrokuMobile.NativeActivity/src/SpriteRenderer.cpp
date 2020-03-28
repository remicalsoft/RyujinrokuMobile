#include"SpriteRenderer.h"
#include"tinyxml2.h"
#include<assert.h>


Object::Object() {
	this->objectId = 0;
	this->pos = VGet(0, 0, 0);
	this->angle = VGet(0, 0, 0);
	this->scale = VGet(1.0f, 1.0f, 1.0f);
	this->name = "noname";
}

std::string Object::getName() {
	return this->name;
}

void Object::setName(std::string name) {
	this->name = name;
}

int Object::getObjectId() {
	return this->objectId;
}
void Object::setObjectId(int id) {
	this->objectId = id;
}

VECTOR Object::getPos() {
	return this->pos;
}

void Object::setPos(VECTOR value) {
	this->pos = value;
}

VECTOR Object::getAngle() {
	return this->angle;
}

void Object::setAngle(VECTOR angle) {
	this->angle = angle;
}

VECTOR Object::getScale() {
	return this->scale;
}

void Object::setScale(VECTOR scale) {
	this->scale = scale;
}

tinyxml2::XMLElement* Object::saveXml(const char* name, tinyxml2::XMLElement* root, tinyxml2::XMLDocument& doc) {
	auto myRoot = doc.NewElement(name);
	auto pos = doc.NewElement("Pos");
	auto angle = doc.NewElement("Angle");
	auto scale = doc.NewElement("Scale");
	if (root) {
		root->LinkEndChild(myRoot);
	}
	myRoot->SetAttribute("objectId", this->objectId);
	myRoot->SetAttribute("name", this->name.c_str());
	myRoot->LinkEndChild(pos);
	myRoot->LinkEndChild(angle);
	myRoot->LinkEndChild(scale);

	pos->SetAttribute("x", this->pos.x);
	pos->SetAttribute("y", this->pos.y);
	pos->SetAttribute("z", this->pos.z);

	angle->SetAttribute("x", this->angle.x);
	angle->SetAttribute("y", this->angle.y);
	angle->SetAttribute("z", this->angle.z);

	scale->SetAttribute("x", this->scale.x);
	scale->SetAttribute("y", this->scale.y);
	scale->SetAttribute("z", this->scale.z);
	return myRoot;
}

void Object::loadXml(const char* name, tinyxml2::XMLElement* root) {
	this->loadXmlElement(root->FirstChildElement(name));
}

void Object::loadXmlElement(const tinyxml2::XMLElement* element) {
	assert(element != NULL);
	auto pos = element->FirstChildElement("Pos");
	auto angle = element->FirstChildElement("Angle");
	auto scale = element->FirstChildElement("Scale");
	auto objectId = element->IntAttribute("objectId");
	const char* name = element->Attribute("name");

	if (pos != NULL) {
		float x = pos->FloatAttribute("x");
		float y = pos->FloatAttribute("y");
		float z = pos->FloatAttribute("z");
		this->setPos(VGet(x, y, z));
	}
	if (angle != NULL) {
		float x = angle->FloatAttribute("x");
		float y = angle->FloatAttribute("y");
		float z = angle->FloatAttribute("z");
		this->setAngle(VGet(x, y, z));
	}
	if (scale != NULL) {
		float x = scale->FloatAttribute("x");
		float y = scale->FloatAttribute("y");
		float z = scale->FloatAttribute("z");
		this->setScale(VGet(x, y, z));
	}
	if (name != NULL) {
		this->name = name;
	}
	this->objectId = objectId;
}

// virtual
void Object::update() {
}

// virtual
void Object::draw() {
}

SpriteRenderer::SpriteRenderer(SpriteRenderer* src) {
	this->setHandle(src->imgHandle);
	this->setTrans(src->transFlag);
	for (int i = 0; i < 4; i++) {
		this->vertex[i] = src->vertex[i];
	}
	for (int i = 0; i < 6; i++) {
		this->index[i] = src->index[i];
	}
	this->material = src->material;
	this->setObjectId(src->getObjectId());
	this->setPos(src->getPos());
	this->setAngle(src->getAngle());
	this->setScale(src->getScale());
	this->setSize(src->getSize().x, src->getSize().y);
}

SpriteRenderer::SpriteRenderer() : Object(){
	this->imgHandle = DX_NONE_GRAPH;
	this->transFlag = TRUE;
	this->setSize(1, 1);

	// 左上
	vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);
	vertex[0].dif = GetColorU8(255, 255, 255, 255);
	vertex[0].spc = GetColorU8(0, 0, 0, 0);
	vertex[0].u = 0.0f;
	vertex[0].v = 0.0f;
	vertex[0].su = 0.0f;
	vertex[0].sv = 0.0f;

	// 右上
	vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);
	vertex[1].dif = GetColorU8(255, 255, 255, 255);
	vertex[1].spc = GetColorU8(0, 0, 0, 0);
	vertex[1].u = 1.0f;
	vertex[1].v = 0.0f;
	vertex[1].su = 0.0f;
	vertex[1].sv = 0.0f;

	// 右下
	vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
	vertex[2].dif = GetColorU8(255, 255, 255, 255);
	vertex[2].spc = GetColorU8(0, 0, 0, 0);
	vertex[2].u = 1.0f;
	vertex[2].v = 1.0f;
	vertex[2].su = 0.0f;
	vertex[2].sv = 0.0f;

	// 左下
	vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);
	vertex[3].dif = GetColorU8(255, 255, 255, 255);
	vertex[3].spc = GetColorU8(0, 0, 0, 0);
	vertex[3].u = 0.0f;
	vertex[3].v = 1.0f;
	vertex[3].su = 0.0f;
	vertex[3].sv = 0.0f;

	// 2ポリゴン分のインデックスデータをセット
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 3;
	index[4] = 0;
	index[5] = 2;

	material.Diffuse = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
	material.Ambient = GetColorF(0.5f, 0.4f, 0.5f, 1.0f);
	material.Emissive = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	material.Power = 20.0f;
}

bool SpriteRenderer::isTrans() {
	if (this->transFlag == TRUE) {
		return true;
	}
	return false;
}

tinyxml2::XMLElement* SpriteRenderer::saveXml(const char* name, tinyxml2::XMLElement* root, tinyxml2::XMLDocument& doc) {
	auto myRoot = Object::saveXml(name, root, doc);
	auto size = doc.NewElement("Size");
	auto trans = doc.NewElement("TransFlag");
	myRoot->LinkEndChild(size);
	myRoot->LinkEndChild(trans);
	size->SetAttribute("x", this->size.x);
	size->SetAttribute("y", this->size.y);
	trans->SetText(this->transFlag);
	return myRoot;
}

void SpriteRenderer::loadXml(const char* name, tinyxml2::XMLElement* root) {
	Object::loadXml(name, root);
}

void SpriteRenderer::loadXmlElement(const tinyxml2::XMLElement* element) {
	Object::loadXmlElement(element);
	auto size = element->FirstChildElement("Size");
	auto trans = element->FirstChildElement("TransFlag");
	if (size != NULL) {
		float x = size->FloatAttribute("x");
		float y = size->FloatAttribute("y");
		this->setSize(x, y);
	}
	if (trans != NULL) {
		this->setTrans(atoi(trans->GetText()));
	}
}

MATERIALPARAM& SpriteRenderer::getMaterial() {
	return this->material;
}

void SpriteRenderer::update() {
	this->m = MGetTranslate(this->pos);
	this->m = MMult(MGetRotX(this->angle.x), this->m);
	this->m = MMult(MGetRotY(this->angle.y), this->m);
	this->m = MMult(MGetRotZ(this->angle.z), this->m);
	this->m = MMult(MGetScale(this->scale), this->m);
}

void SpriteRenderer::draw() {
	VERTEX3D tmpVertex[4];
	memcpy(tmpVertex, this->vertex, sizeof(this->vertex));
	for (int i = 0; i < 4; i++) {
		tmpVertex[i].pos = VTransform(tmpVertex[i].pos, this->m);
	}

	SetMaterialParam(this->material);
	SetMaterialUseVertSpcColor(FALSE);
	SetMaterialUseVertDifColor(FALSE);
	DrawPolygonIndexed3D(tmpVertex, 4, this->index, 2, this->imgHandle, this->transFlag);
}

void SpriteRenderer::setHandle(int handle) {
	this->imgHandle = handle;
}

void SpriteRenderer::setTrans(int trans) {
	this->transFlag = trans;
}

void SpriteRenderer::setSize(float x, float y) {
	this->size = VGet(x, y, 0);
	float top    = (this->size.y / 2);
	float bottom = (this->size.y / 2) * -1;
	float left   = (this->size.x / 2) * -1;
	float right  = (this->size.x / 2);
	vertex[0].pos = VGet(left , top   , 0.0f);
	vertex[1].pos = VGet(right, top   , 0.0f);
	vertex[2].pos = VGet(right, bottom, 0.0f);
	vertex[3].pos = VGet(left , bottom, 0.0f);
}

VECTOR SpriteRenderer::getSize() {
	return this->size;
}


// class SpriteAnimation
SpriteAnimation::SpriteAnimation() : SpriteRenderer(){
	this->animTimeCount = 0;
	this->animSpeed = 1;
}

SpriteAnimation::SpriteAnimation(SpriteAnimation* src) : SpriteRenderer(src) {
	this->animTimeCount = src->animTimeCount;
	this->animSpeed = src->animSpeed;
}

void SpriteAnimation::addImage(int handle) {
	this->imgArray.push_back(handle);
}

void SpriteAnimation::update() {
	int count = this->animTimeCount / this->animSpeed;
	int length = this->imgArray.size();
	int index = count % length;
	this->setHandle(this->imgArray[index]);
	this->animTimeCount++;
	SpriteRenderer::update();
}

void SpriteAnimation::draw() {
	SpriteRenderer::draw();
}


//
// MV1Renderer
//
MV1Renderer::MV1Renderer(std::string path) {
	this->setHandle(MV1LoadModel(path.c_str()));
}

MV1Renderer::MV1Renderer(int handle) {
	this->setHandle(MV1DuplicateModel(handle));
}

MV1Renderer::MV1Renderer(MV1Renderer* src) {
	this->setHandle(MV1DuplicateModel(src->handle));
	this->setObjectId(src->getObjectId());
	this->setPos(src->getPos());
	this->setAngle(src->getAngle());
	this->setScale(src->getScale());
}

MV1Renderer::MV1Renderer() {
	this->handle = -1;
}


MV1Renderer::~MV1Renderer() {
	this->deleteModel();
}

void MV1Renderer::changeModel(int handle) {
	this->deleteModel();
	this->setHandle(MV1DuplicateModel(handle));
}

void MV1Renderer::deleteModel() {
	if (this->handle != -1) {
		MV1DeleteModel(this->handle);
		this->handle = -1;
	}
}

void MV1Renderer::setHandle(int handle) {
	assert(handle != -1);
	this->handle = handle;
}

void MV1Renderer::update() {
	MV1SetPosition(this->handle, this->pos);
	MV1SetRotationXYZ(this->handle, this->angle);
	MV1SetScale(this->handle, this->scale);
}

void MV1Renderer::draw() {
	MV1DrawModel(this->handle);
}