#pragma once
#include<DxLib.h>
#include<string>
#include<vector>
#include"tinyxml2.h"

//
// オブジェクト共通情報基底
//
class Object {
protected:
	std::string name;
	int objectId;
	VECTOR pos;
	VECTOR angle;
	VECTOR scale;
public:
	Object();
	std::string getName();
	void setName(std::string name);
	int getObjectId();
	void setObjectId(int id);
	VECTOR getPos();
	VECTOR getAngle();
	VECTOR getScale();
	void setPos(VECTOR value);
	void setAngle(VECTOR angle);
	void setScale(VECTOR scale);
	virtual tinyxml2::XMLElement* saveXml(const char* name, tinyxml2::XMLElement* root, tinyxml2::XMLDocument& doc);
	virtual void loadXml(const char* name, tinyxml2::XMLElement* root);
	virtual void loadXmlElement(const tinyxml2::XMLElement* element);
	virtual void update();
	virtual void draw();
};

//
// 画像付きポリゴンを扱う。
//
class SpriteRenderer : public Object {
private:
	MATERIALPARAM material;
	VERTEX3D vertex[4];
	unsigned short index[6];
	MATRIX m;
	int imgHandle;
	int transFlag;
	VECTOR size;
public:
	VECTOR getSize();
	virtual tinyxml2::XMLElement* saveXml(const char* name, tinyxml2::XMLElement* root, tinyxml2::XMLDocument& doc);
	virtual void loadXml(const char* name, tinyxml2::XMLElement* root);
	virtual void loadXmlElement(const tinyxml2::XMLElement* element);
	bool isTrans();
	SpriteRenderer();
	SpriteRenderer(SpriteRenderer* src);
	MATERIALPARAM& getMaterial();
	void setTrans(int trans);
	void setSize(float x, float y);
	void setHandle(int handle);
	virtual void update() override;
	virtual void draw() override;
};

//
// テクスチャアニメーション付きスプライト
//
class SpriteAnimation : public SpriteRenderer {
private :
	std::vector<int> imgArray;
	unsigned int animTimeCount;
	unsigned int animSpeed;
public:
	SpriteAnimation();
	SpriteAnimation(SpriteAnimation* src);
	void addImage(int handle);
	virtual void update() override;
	virtual void draw() override;
};

//
// 3Dモデルを扱う
// 必ずハンドルに-1以外の値が入っていなければいけない。
// コンストラクタで必ず何がしかのモデルを設定する。
//
class MV1Renderer : public Object {
private:
	// 生成されたモデルのハンドル
	int handle;
	// モデルを削除する。
	void deleteModel();
	// 新たに生成されたモデルハンドルの設定を行う。
	// -1が入ってはいけない。
	void setHandle(int handle);
public:
	// パスからモデルをロードする。
	MV1Renderer(std::string path);
	// ハンドルからモデルを複製する。
	MV1Renderer(int handle);
	// 参照元のインスタンス情報をコピーしてモデルは複製する。
	MV1Renderer(MV1Renderer* src);
	// デフォルトコンストラクタ
	// ハンドルに-1が含まれているが例外的な使い方。
	MV1Renderer();
	// モデルを破棄する。
	~MV1Renderer();

	// 渡されたハンドルのモデルを複製して
	// 新たに発行されたハンドル番号を再設定する。
	void changeModel(int handle);
	virtual void update() override;
	virtual void draw() override;
};
