#include"Camera.h"
#include"tinyxml2.h"
#include<assert.h>

void Camera::initialize(CameraType type) {
	this->type = type;
	// カメラの初期パラメータをoriginalに設定する。
	SetFogStartEnd(param.fogStart, param.fogEnd);
	this->origial.camNear = GetCameraNear();
	this->origial.camFar = GetCameraFar();
	GetCameraScreenCenter(&this->origial.center.x, &this->origial.center.y);
	this->origial.pos = GetCameraPosition();
	this->origial.target = GetCameraTarget();
	this->origial.fogEnable = GetFogEnable();
	GetFogColor(&this->origial.fogR, &this->origial.fogG, &this->origial.fogB);
	GetFogStartEnd(&this->origial.fogStart, &this->origial.fogEnd);
	this->origial.V = GetCameraAngleVRotate();
	this->origial.H = GetCameraAngleHRotate();
	this->origial.T = GetCameraAngleTRotate();

	this->setCenter(this->origial.center.x, this->origial.center.y);
	this->setPos(this->origial.pos.x, this->origial.pos.y, this->origial.pos.z);
	this->setTarget(this->origial.target.x, this->origial.target.y, this->origial.target.z);
	this->setNearFar(this->origial.camNear, this->origial.camFar);
	this->setFogEnable(this->origial.fogEnable);
	this->setFogColor(this->origial.fogR, this->origial.fogG, this->origial.fogB);
	this->setFogStartEnd(this->origial.fogStart, this->origial.fogEnd);
	this->setVHT(this->origial.V, this->origial.H, this->origial.T);
}

Camera::Camera() {
	this->initialize(PositionAndTarget);
}

Camera::Camera(CameraType type) {
	this->initialize(type);
}

Camera::Camera(tinyxml2::XMLElement* root) {
	this->loadXml(root);
}

Camera::~Camera() {
	this->reset();
}

void Camera::setCamera(const CameraParam& param) {
	auto pos = VGet(param.pos.x, param.pos.y, param.pos.z);
	auto target = VGet(param.target.x, param.target.y, param.target.z);
	SetCameraNearFar(param.camNear, param.camFar);		//カメラの有効範囲を設定
	SetCameraScreenCenter(param.center.x, param.center.y);
	SetFogEnable(param.fogEnable);
	SetFogColor(param.fogR, param.fogG, param.fogB);
	SetFogStartEnd(param.fogStart, param.fogEnd);
	switch (this->type) {
	case PositionAndTarget:
		SetCameraPositionAndTarget_UpVecY(pos, target);
		break;
	case PositionAndAngle:
		SetCameraPositionAndAngle(pos, param.V, param.H, param.T);
		break;
	}
}

VECTOR Camera::getPos() {
	return this->param.pos;
}

VECTOR Camera::getTarget() {
	return this->param.target;
}

VECTOR Camera::getCenter() {
	return this->param.center;
}

float Camera::getV() {
	return this->param.V;
}

float Camera::getH() {
	return this->param.H;
}

float Camera::getT() {
	return this->param.T;
}

// オリジナルの設定に戻す
void Camera::reset() {
	this->setCamera(this->origial);
}

void Camera::setFogEnable(BOOL enable) {
	this->param.fogEnable = enable;
}

void Camera::setFogColor(int r, int g, int b) {
	this->param.fogR = r;
	this->param.fogG = g;
	this->param.fogB = b;
}

void Camera::setFogStartEnd(float start, float end) {
	this->param.fogStart = start;
	this->param.fogEnd = end;
}

void Camera::setNearFar(float _near, float _far) {
	this->param.camNear = _near;
	this->param.camFar  = _far;
}

void Camera::setCenter(float x, float y) {
	this->param.center = VGet(x, y, 0);
}

void Camera::setPos(float x, float y, float z) {
	this->param.pos = VGet(x, y, z);
}

void Camera::setTarget(float x, float y, float z) {
	this->param.target = VGet(x, y, z);
}

void Camera::setVHT(float v, float h, float t) {
	this->param.V = v;
	this->param.H = h;
	this->param.T = t;
}

void Camera::saveXml(const char* name, tinyxml2::XMLElement* root, tinyxml2::XMLDocument& doc) {
	auto myRoot = doc.NewElement(name);
	auto type = doc.NewElement("Type");
	auto pos = doc.NewElement("Pos");
	auto target = doc.NewElement("Target");
	auto center = doc.NewElement("Center");
	auto angle = doc.NewElement("Angle");
	auto fog = doc.NewElement("Fog");
	auto nearFar = doc.NewElement("NearFar");
	root->LinkEndChild(myRoot);

	myRoot->LinkEndChild(type);
	myRoot->LinkEndChild(pos);
	myRoot->LinkEndChild(target);
	myRoot->LinkEndChild(center);
	myRoot->LinkEndChild(angle);
	myRoot->LinkEndChild(fog);
	myRoot->LinkEndChild(nearFar);

	type->SetText(this->type);
	pos->SetAttribute("x", this->param.pos.x);
	pos->SetAttribute("y", this->param.pos.y);
	pos->SetAttribute("z", this->param.pos.z);
	target->SetAttribute("x", this->param.target.x);
	target->SetAttribute("y", this->param.target.y);
	target->SetAttribute("z", this->param.target.z);
	center->SetAttribute("x", this->param.center.x);
	center->SetAttribute("y", this->param.center.y);
	angle->SetAttribute("V", this->param.V);
	angle->SetAttribute("H", this->param.H);
	angle->SetAttribute("T", this->param.T);
	fog->SetAttribute("enable", this->param.fogEnable);
	fog->SetAttribute("r", this->param.fogR);
	fog->SetAttribute("g", this->param.fogG);
	fog->SetAttribute("b", this->param.fogB);
	fog->SetAttribute("start", this->param.fogStart);
	fog->SetAttribute("end", this->param.fogEnd);
	nearFar->SetAttribute("near", this->param.camNear);
	nearFar->SetAttribute("far", this->param.camFar);
}

void Camera::loadXml(const tinyxml2::XMLElement* root) {
	assert(root != NULL);
	auto type = root->FirstChildElement("Type");
	auto fog = root->FirstChildElement("Fog");
	auto pos = root->FirstChildElement("Pos");
	auto target = root->FirstChildElement("Target");
	auto center = root->FirstChildElement("Center");
	auto angle = root->FirstChildElement("Angle");
	auto nearFar = root->FirstChildElement("NearFar");

	CameraType cameraType = PositionAndTarget;
	if (type) {
		cameraType = (CameraType)atoi(type->GetText());
	}
	this->initialize(cameraType);
	if (pos) {
		float x = pos->FloatAttribute("x");
		float y = pos->FloatAttribute("y");
		float z = pos->FloatAttribute("z");
		this->setPos(x, y, z);
	}
	if (target) {
		float x = target->FloatAttribute("x");
		float y = target->FloatAttribute("y");
		float z = target->FloatAttribute("z");
		this->setTarget(x, y, z);
	}
	if (center) {
		float x = center->FloatAttribute("x");
		float y = center->FloatAttribute("y");
		this->setCenter(x, y);
	}
	if (angle) {
		float v = angle->FloatAttribute("V");
		float h = angle->FloatAttribute("H");
		float t = angle->FloatAttribute("T");
		this->setVHT(v, h, t);
	}
	if (fog) {
		int enable = fog->IntAttribute("enable");
		int r = fog->IntAttribute("r");
		int g = fog->IntAttribute("g");
		int b = fog->IntAttribute("b");
		float start = fog->FloatAttribute("start");
		float end = fog->FloatAttribute("end");
		this->setFogEnable(enable);
		this->setFogColor(r, g, b);
		this->setFogStartEnd(start, end);
	}
	if (nearFar) {
		float Near = nearFar->FloatAttribute("near");
		float Far = nearFar->FloatAttribute("far");
		this->setNearFar(Near, Far);
	}
}

bool Camera::update() {
	this->setCamera(this->param);
	return true;
}

void Camera::draw(){
}