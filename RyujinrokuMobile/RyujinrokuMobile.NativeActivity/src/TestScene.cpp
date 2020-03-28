#include "TestScene.h"
#include "CameraInspectorView.h"
#include "Keyboard.h"

static VECTOR getVect(VECTOR a, VECTOR b) {
	VECTOR result = VGet(0, 0, 0);
	result.x = a.x - b.x;
	result.y = a.x - b.x;
	result.z = a.x - b.x;
	return result;
}

static VECTOR Cross(VECTOR a, VECTOR b) {
	VECTOR result;
	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);
	return result;
}

static double VECTOR_Length(VECTOR v) {
	double length = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return length;
}

static VECTOR VECTOR_Normalize( VECTOR v ) {
	double length = VECTOR_Length(v);
	VECTOR result = VGet(0, 0, 0);
	result.x = v.x / (float)length;
	result.y = v.y / (float)length;
	result.z = v.z / (float)length;
	return result;
}

struct EditorPolygon {
	VERTEX3D vertex[4];
	unsigned short indices[6];

	void init() {
		// 左上
		vertex[0].dif = GetColorU8(255, 255, 255, 255);
		vertex[0].spc = GetColorU8(0, 0, 0, 0);
		vertex[0].u = 0.0f;
		vertex[0].v = 0.0f;
		vertex[0].su = 0.0f;
		vertex[0].sv = 0.0f;

		// 右上
		vertex[1].dif = GetColorU8(255, 255, 255, 255);
		vertex[1].spc = GetColorU8(0, 0, 0, 0);
		vertex[1].u = 1.0f;
		vertex[1].v = 0.0f;
		vertex[1].su = 0.0f;
		vertex[1].sv = 0.0f;

		// 右下
		vertex[2].dif = GetColorU8(255, 255, 255, 255);
		vertex[2].spc = GetColorU8(0, 0, 0, 0);
		vertex[2].u = 1.0f;
		vertex[2].v = 1.0f;
		vertex[2].su = 0.0f;
		vertex[2].sv = 0.0f;

		// 左下
		vertex[3].dif = GetColorU8(255, 255, 255, 255);
		vertex[3].spc = GetColorU8(0, 0, 0, 0);
		vertex[3].u = 0.0f;
		vertex[3].v = 1.0f;
		vertex[3].su = 0.0f;
		vertex[3].sv = 0.0f;

		// 2ポリゴン分のインデックスデータをセット
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 3;
		indices[4] = 0;
		indices[5] = 2;


		float xsize  = 256;
		float ysize  = 256;
		float top    = (ysize / 2);
		float bottom = (ysize / 2) * -1;
		float left   = (xsize / 2) * -1;
		float right  = (xsize / 2);
		vertex[0].pos = VGet(left, top, 0.0f);
		vertex[1].pos = VGet(right, top, 0.0f);
		vertex[2].pos = VGet(right, bottom, 0.0f);
		vertex[3].pos = VGet(left, bottom, 0.0f);

	//	VECTOR V01 = getVect(vertex[0].pos, vertex[1].pos);
	//	VECTOR V12 = getVect(vertex[1].pos, vertex[2].pos);
	//	VECTOR cross = Cross(V01, V12);
	//	VECTOR normal = VECTOR_Normalize(cross);
		vertex[0].norm = VGet(0, 0, -1);
		vertex[1].norm = VGet(0, 0, -1);
		vertex[2].norm = VGet(0, 0, -1);
		vertex[3].norm = VGet(0, 0, -1);
	}

	void setPos(int index, VECTOR pos) {
		this->vertex[index].pos = pos;
	}
};

EditorPolygon polygon1;
EditorPolygon polygon2;
EditorPolygon polygon3;
EditorPolygon polygon4;
MATRIX m0;
MATRIX m1;
MATRIX m2;
MATRIX m3;
MATRIX m4;
int VertexShaderHandle;
int PixelShaderHandle;
int ModelHandle;

TestScene::TestScene(ISceneChangedListener *impl, ScenePrmBase* prm) : Scene(impl) {
	img = LoadGraph("dat/image/background/02/03.jpg");
	this->pos = VGet(0, 0, 0);
	this->angle = VGet(0, 0, 0);
	this->scale = VGet(1, 1, 1);

	this->camera = new Camera(Camera::PositionAndAngle);
	auto cameraView = new Editor::CameraInspectorView(VGet(0, 0, 0));
	cameraView->setFocus(this->camera);
	cameraView->setVisible(true);
	this->gui.push_back(cameraView);
	this->cursor = new DxGUI::MouseCursor();
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	polygon1.init();
	polygon2.init();
	polygon3.init();
	polygon4.init();
	ModelHandle = MV1LoadModel("dat/image/background/03/Object1.mqo");
	// 頂点シェーダーを読み込む
//	VertexShaderHandle = LoadVertexShader("dat/NormalMesh_DirLightVS.vso");
	// ピクセルシェーダーを読み込む
//	PixelShaderHandle = LoadPixelShader("dat/NormalMesh_DirLightPS.pso");
	// 使用する頂点シェーダーをセット
//	SetUseVertexShader(VertexShaderHandle);
	// 使用するピクセルシェーダーをセット
//	SetUsePixelShader(PixelShaderHandle);

//	polygon1.setPos(0, VGet(-128,  128, -128));
//	polygon1.setPos(1, VGet( 128,  128, -128));
//	polygon1.setPos(2, VGet( 128, -128, -128));
//	polygon1.setPos(3, VGet(-128, -128, -128));

//	polygon2.setPos(0, VGet( 128,  128, -128));
//	polygon2.setPos(1, VGet( 128,  128,  128));
//	polygon2.setPos(2, VGet( 128, -128,  128));
//	polygon2.setPos(3, VGet( 128, -128, -128));

//	polygon3.setPos(0, VGet(-128,  128,  128));
//	polygon3.setPos(1, VGet(-128,  128, -128));
//	polygon3.setPos(2, VGet(-128, -128, -128));
//	polygon3.setPos(3, VGet(-128, -128,  128));

//	polygon4.setPos(0, VGet(-128,  128,  128));
//	polygon4.setPos(1, VGet( 128,  128,  128));
//	polygon4.setPos(2, VGet( 128, -128,  128));
//	polygon4.setPos(3, VGet(-128, -128,  128));
}

TestScene::~TestScene() {
	delete this->cursor;
	delete this->camera;
}

void TestScene::createTriangle() {
}

// virtual
bool TestScene::update() {
	for (auto task : this->gui) {
		task->update();
	}
	this->camera->update();
	this->cursor->update();
	return true;
}

// virtual
void TestScene::draw() {
	this->angle.y += 3.14f / 120.0f;
	this->m = MGetTranslate(this->pos);
	this->m = MMult(MGetRotX(this->angle.x), this->m);
	this->m = MMult(MGetRotY(this->angle.y), this->m);
	this->m = MMult(MGetRotZ(this->angle.z), this->m);
	this->m = MMult(MGetScale(this->scale), this->m);


	m1 = MMult(MGetTranslate(VGet(300, 0, -128)), this->m);
	m1 = MMult(MGetRotX(0), m1);
	m1 = MMult(MGetRotY(0), m1);
	m1 = MMult(MGetRotZ(0), m1);
	m1 = MMult(MGetScale(VGet(1, 1, 1)), m1);
	VERTEX3D tmpVertex[4];
	memcpy(tmpVertex, polygon1.vertex, sizeof(polygon1.vertex));
	for (int i = 0; i < 4; i++) {
		tmpVertex[i].pos = VTransform(tmpVertex[i].pos, m1);
	}
	MATERIALPARAM mat;
	// マテリアルの自己発光色を暗い青色にする
	mat.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
	mat.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	mat.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	mat.Emissive = GetColorF(0.0f, 0.0f, 0.5f, 0.0f);
	mat.Power = 20.0f;
	SetMaterialParam(mat);
	DrawPolygonIndexed3D(tmpVertex, 4, polygon1.indices, 2, DX_NONE_GRAPH, FALSE);
	MV1SetRotationXYZ(ModelHandle, this->angle);
	MV1DrawModel(ModelHandle);

	for (auto task : this->gui) {
		task->draw();
	}
	this->camera->draw();
	this->cursor->draw();
}