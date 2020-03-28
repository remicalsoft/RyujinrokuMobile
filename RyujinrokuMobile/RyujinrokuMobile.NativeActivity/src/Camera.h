#pragma once
#include<DxLib.h>
#include"Task.h"
#include"tinyxml2.h"


class Camera : public Task {
public:
	enum CameraType {
		PositionAndTarget = 0 ,
		PositionAndAngle  = 1 ,
	};
private:
	struct CameraParam {
		VECTOR center;
		VECTOR pos;
		VECTOR target;
		float camNear;
		float camFar;
		BOOL fogEnable;
		int fogR;
		int fogG;
		int fogB;
		float fogStart;
		float fogEnd;
		float V;
		float H;
		float T;
	};
	CameraParam origial; // 一番最初のカメラパラメータ
	CameraParam param  ; // 設定中のカメラパラメータ
	CameraType type;
public:
	void initialize(CameraType type);
	Camera();
	Camera(CameraType type);
	Camera(tinyxml2::XMLElement* root);
	~Camera();
	VECTOR getPos();
	VECTOR getTarget();
	VECTOR getCenter();
	float getV();
	float getH();
	float getT();
	void reset();
	void setCamera(const CameraParam& param);
	void setFogEnable(BOOL enable);
	void setFogColor(int r, int g, int b);
	void setFogStartEnd(float start, float end);
	void setNearFar( float _near, float _far);
	void setCenter(float x, float y);
	void setPos(float x, float y, float z);
	void setTarget(float x, float y, float z);
	void setVHT(float v, float h, float t);
	void saveXml(const char* name, tinyxml2::XMLElement* root, tinyxml2::XMLDocument& doc);
	void loadXml(const tinyxml2::XMLElement* root);
	virtual bool update() override;
	virtual void draw() override;
};