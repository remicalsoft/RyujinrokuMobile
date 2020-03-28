#include "BGEditorScene.h"
#include "ScenePrmBase.h"
#include "Keyboard.h"
#include "Board.h"
#include "tinyxml2.h"
#include "Image.h"
#include <DxLib.h>
#include <string>
#include <codecvt> 
#include "InspectorView.h"
#include "CameraInspectorView.h"

//
// 		for (const tinyxml2::XMLNode* node = root->FirstChild(); node; node = node->NextSibling()) {
//			const tinyxml2::XMLElement* element = node->ToElement();
//			if (element) {
//				return element;
//			}
//		}
//
//
// 3Dエディタ
// モデルの配置情報や、カメラ情報などをxml化して書き出す作業を行う。
// 
#define BUTTONID_OBJ_SHOW_INSPECTOR             (  1 )
#define BUTTONID_OBJ_CREATE_SPRITE_RENDERER     (  2 )
#define BUTTONID_OBJ_CREATE_MV1MODEL            (  3 )
#define BUTTONID_OBJ_DELETE                     (  4 )
#define BUTTONID_OBJ_COPY                       (  5 )
#define BUTTONID_OBJ_CREATE_PLANE               (  6 )
#define BUTTONID_OBJ_NEXT                       (  7 )
#define BUTTONID_OBJ_PREV                       (  8 )
#define BUTTONID_CAMERA_SHOW_CAMERA_INSPECTOR   (  9 )
#define BUTTONID_TEX_NEXT                       ( 10 )
#define BUTTONID_TEX_PREV                       ( 11 )
#define BUTTONID_SAVE_MAPDATA                   ( 12 )
#define BUTTONID_LOAD_MAPDATA                   ( 13 )
using namespace Editor;

namespace {
	// 
	// エディタ用
	// フォーカスが当たっているオブジェクトのみ明るくする処理が入っている。
	// 
	class EditorSpriteRenderer : public SpriteRenderer {
	private:
		BGEditorScene* __me;
	public:
		EditorSpriteRenderer(BGEditorScene* __me) {
			this->__me = __me;
		}
		EditorSpriteRenderer(EditorSpriteRenderer* src) : SpriteRenderer(src) {
		}

		virtual void update() {
			auto self = this->__me;
			auto current = self->getCurrentObject();
			auto color = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
			if (current == this) {
				color = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
			}
			this->getMaterial().Emissive = color;

			SpriteRenderer::update();
		}
	};

	// 
	// メインメニューウィンドウ
	// 
	class MainMenuView : public DxGUI::Window {
	private:
		std::vector<DxGUI::Button*> guilist;
		BGEditorScene* __me;
	public:
		MainMenuView(BGEditorScene* __me, VECTOR pos) {
			this->initialize(pos, VGet(330, 550, 0), "MainMenu");
			this->addButtonView("Show Inspector", BUTTONID_OBJ_SHOW_INSPECTOR);
			this->addButtonView("Show Camera Inspector", BUTTONID_CAMERA_SHOW_CAMERA_INSPECTOR);
			this->addButtonView("[Object] Create Sprite", BUTTONID_OBJ_CREATE_SPRITE_RENDERER);
			this->addButtonView("[Object] Create Model", BUTTONID_OBJ_CREATE_MV1MODEL);
			this->addButtonView("[Object] Delete", BUTTONID_OBJ_DELETE);
			this->addButtonView("[Object] Copy", BUTTONID_OBJ_COPY);
			this->addButtonView("[Object] Create Plane", BUTTONID_OBJ_CREATE_PLANE);
			this->addButtonView("[Object] >>", BUTTONID_OBJ_NEXT);
			this->addButtonView("[Object] <<", BUTTONID_OBJ_PREV);
			this->addButtonView("[Texture] >>", BUTTONID_TEX_NEXT);
			this->addButtonView("[Texture] <<", BUTTONID_TEX_PREV);
			this->addButtonView("Save Map Data", BUTTONID_SAVE_MAPDATA);
			this->addButtonView("Load Map Data", BUTTONID_LOAD_MAPDATA);
			this->__me = __me;
		}

		void addButtonView(std::string text, int id) {
			VECTOR pos = VGet(0, 0, 0);
			VECTOR size = VGet(280, 35, 0);
			unsigned int color1 = GetColor(64, 64, 64);
			unsigned int color2 = GetColor(128, 0, 128);
			this->guilist.push_back(new DxGUI::Button(text, pos, size, color1, color2, this, id));
		}

		virtual void onUpdate() {
			auto basePos = this->getBasePosition();
			for (unsigned int i = 0; i < this->guilist.size(); i++) {
				auto gui = this->guilist[i];
				gui->setPos(basePos.x + 15, basePos.y + (40 * i));
				gui->update();
			}
		}

		virtual void onDraw() {
			for (auto gui : this->guilist) {
				gui->draw();
			}
		}

		void onClick(Task* sender) {
			auto button = dynamic_cast<DxGUI::Button*>(sender);
			if (button) {
				int instanceId = button->getInstanceId();
				switch (instanceId) {
				case BUTTONID_OBJ_SHOW_INSPECTOR:
					this->showInspector();
					break;
				case BUTTONID_CAMERA_SHOW_CAMERA_INSPECTOR:
					this->showCameraInspector();
					break;
				case BUTTONID_OBJ_CREATE_SPRITE_RENDERER:
					this->createSpriteRenderer();
					break;
				case BUTTONID_OBJ_CREATE_MV1MODEL:
					this->createMV1Model();
					break;
				case BUTTONID_OBJ_NEXT:
					this->moveNextObject();
					break;
				case BUTTONID_OBJ_PREV:
					this->movePrevObject();
					break;
				case BUTTONID_TEX_NEXT:
					this->moveNextTexture();
					break;
				case BUTTONID_TEX_PREV:
					this->movePrevTexture();
					break;
				case BUTTONID_SAVE_MAPDATA:
					this->saveMapData();
					break;
				case BUTTONID_LOAD_MAPDATA:
					this->loadMapData();
					break;
				case BUTTONID_OBJ_DELETE:
					this->deleteObject();
					break;
				case BUTTONID_OBJ_COPY:
					this->copyObject();
					break;
				case BUTTONID_OBJ_CREATE_PLANE:
					this->createPlane();
					break;
				}
			}
		}

		void showInspector() {
			auto self = this->__me;
			self->getTaskById<InspectorView>()->setVisible(true);
			self->getTaskById<CameraInspectorView>()->setVisible(false);
		}

		void showCameraInspector() {
			auto self = this->__me;
			self->getTaskById<InspectorView>()->setVisible(false);
			self->getTaskById<CameraInspectorView>()->setVisible(true);
		}

		void createSpriteRenderer() {
			auto self = this->__me;
			auto img = self->getImageHandle(0);
			auto newObj = new EditorSpriteRenderer(self);
			newObj->setTrans(FALSE);
			newObj->setSize(256, 256);
			newObj->setHandle(img);
			newObj->setObjectId(0);
			self->insertObject(newObj);
		}

		void createMV1Model() {
			auto self = this->__me;
			auto newObj = new MV1Renderer(self->getCurrentModelHandle());
			self->insertObject(newObj);
		}

		void moveNextObject() {
			auto self = this->__me;
			self->nextSpriteIndex();
			Object* ref = self->getCurrentObject();
			self->getTaskById<InspectorView>()->setRef(ref);
		}

		void movePrevObject() {
			auto self = this->__me;
			self->prevSpriteIndex();
			Object* ref = self->getCurrentObject();
			self->getTaskById<InspectorView>()->setRef(ref);
		}

		void moveNextTexture() {
			auto self = this->__me;
			self->nextTexIndex();
			auto currentSprite = dynamic_cast<SpriteRenderer*>(self->getCurrentObject());
			if (currentSprite) {
				currentSprite->setHandle(self->getCurrentImgHandle());
				currentSprite->setObjectId(self->getCurrentTexIndex());
			}
		}

		void movePrevTexture() {
			auto self = this->__me;
			self->prevTexIndex();
			auto currentSprite = dynamic_cast<SpriteRenderer*>(self->getCurrentObject());
			if (currentSprite) {
				currentSprite->setHandle(self->getCurrentImgHandle());
				currentSprite->setObjectId(self->getCurrentTexIndex());
			}
		}

		void saveMapData() {
			auto self = this->__me;
			self->saveMapData();
		}

		void loadMapData() {
			auto self = this->__me;
			self->loadMapData();
		}

		void deleteObject() {
			auto self = this->__me;
			Object* currentSprite = self->getCurrentObject();
			self->deleteObject(currentSprite);
		}

		void copyObject() {
			auto self = this->__me;
			auto current = self->getCurrentObject();
			self->copyObject(current);
		}

		void createPlane() {
			auto self = this->__me;
			auto sprite = new SpriteRenderer();
			sprite->setSize(1028, 1028);
			sprite->setHandle(self->getImageHandle(5));
			sprite->setObjectId(5);
			self->insertObject(sprite);
		}
	};
}


// 
// class BGEditorScene
// 
BGEditorScene::BGEditorScene(ISceneChangedListener *impl, ScenePrmBase* prm) : Scene(impl) {
	auto inspectorView = new InspectorView(VGet(900, 50, 0));
	auto cameraInspectorView = new CameraInspectorView(VGet(900, 50, 0));
	auto mainMenuView = new MainMenuView(this, VGet(0, 0, 0));
	inspectorView->setVisible(true);
	cameraInspectorView->setVisible(false);
	mainMenuView->setVisible(true);

	this->viewTask.push_back(inspectorView);
	this->viewTask.push_back(cameraInspectorView);
	this->viewTask.push_back(mainMenuView);
	this->guiTask.push_back(new DxGUI::MouseCursor());
	this->gameUITask.push_back(new Board());
	this->currentObj = 0;
	this->currentTex = 0;
	this->currentModelIndex = 0;
	this->camera = new Camera(Camera::PositionAndAngle);
	cameraInspectorView->setFocus(this->camera);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
}

BGEditorScene::~BGEditorScene() {
	delete this->camera;
}

Object* BGEditorScene::getCurrentObject() {
	if (this->currentObj >= 0 && this->currentObj < this->objList.size()) {
		return this->objList[this->currentObj];
	}
	return NULL;
}

int BGEditorScene::getImageHandle(unsigned int index) {
	if (index >= 0 && index < this->imgList.size()) {
		return this->imgList[index].handle;
	}
	return -1;
}

int BGEditorScene::getModelHandle(unsigned int index) {
	if (index >= 0 && index < this->modelList.size()) {
		return this->modelList[index].handle;
	}
	return -1;
}

int BGEditorScene::getCurrentTexIndex() {
	return this->currentTex;
}

int BGEditorScene::getCurrentImgHandle() {
	if (this->currentTex >= 0 && this->currentTex < this->imgList.size()) {
		return this->imgList[this->currentTex].handle;
	}
	return -1;
}

int BGEditorScene::getCurrentModelHandle() {
	if (this->currentModelIndex >= 0 && this->currentModelIndex < this->modelList.size()) {
		return this->modelList[this->currentModelIndex].handle;
	}
	return -1;
}

int BGEditorScene::nextSpriteIndex() {
	this->currentObj++;
	if (this->currentObj >= this->objList.size()) {
		this->currentObj = 0;
	}
	return this->currentObj;
}

int BGEditorScene::prevSpriteIndex() {
	this->currentObj--;
	if (this->currentObj < 0) {
		this->currentObj = this->objList.size() - 1;
	}
	return this->currentObj;
}

int BGEditorScene::nextTexIndex() {
	this->currentTex++;
	if (this->currentTex >= this->imgList.size()) {
		this->currentTex = 0;
	}
	return this->currentTex;
}

int BGEditorScene::prevTexIndex() {
	this->currentTex--;
	if (this->currentTex < 0) {
		this->currentTex = this->imgList.size() - 1;
	}
	return this->currentTex;
}

int BGEditorScene::nextModelIndex() {
	this->currentModelIndex++;
	if (this->currentModelIndex >= this->modelList.size()) {
		this->currentModelIndex = 0;
	}
	return this->currentModelIndex;
}

int BGEditorScene::prevModelIndex() {
	this->currentModelIndex--;
	if (this->currentModelIndex < 0) {
		this->currentModelIndex = this->modelList.size() - 1;
	}
	return this->currentModelIndex;
}

void BGEditorScene::deleteObject(Object* current) {
	if (current) {
		for (std::vector<Object*>::iterator iter = this->objList.begin(); iter != this->objList.end(); ++iter) {
			if ((*iter) == current) {
				this->objList.erase(iter);
				delete current;
				this->currentObj = this->objList.size() - 1;
				this->getTaskById<InspectorView>()->setRef(NULL);
				break;
			}
		}
	}
}

void BGEditorScene::insertObject(Object* obj) {
	this->objList.push_back(obj);
	this->currentObj = this->objList.size() - 1;
	this->getTaskById<InspectorView>()->setRef(this->getCurrentObject());
}

void BGEditorScene::copyObject(Object* current) {
	auto sourceSprite = dynamic_cast<SpriteRenderer*>(current);
	auto sourceModel = dynamic_cast<MV1Renderer*>(current);
	if (sourceSprite) {
		this->insertObject(new SpriteRenderer(sourceSprite));
	}
	if (sourceModel) {
		this->insertObject(new MV1Renderer(sourceModel));
	}
}

void BGEditorScene::saveMapData() {
	tinyxml2::XMLDocument doc;
	auto root = doc.NewElement("ModelRoot");
	doc.LinkEndChild(root);

	for (auto tex : this->imgList) {
		auto texture = doc.NewElement("Texture");
		texture->SetText(tex.path.c_str());
		root->LinkEndChild(texture);
	}
	for (auto m : this->modelList) {
		auto model = doc.NewElement("Model");
		model->SetText(m.path.c_str());
		root->LinkEndChild(model);
	}
	{
		this->camera->saveXml("Camera", root, doc);
	}


	for (auto obj : this->objList) {
		std::string name = "";
		if (dynamic_cast<SpriteRenderer*>(obj)) { name = "SpriteRenderer"; }
		if (dynamic_cast<MV1Renderer*>(obj))    { name = "MV1Renderer"   ; }
		obj->saveXml(name.c_str(), root, doc);
	}
	doc.SaveFile("edit_stage_model.txt");
	MessageBox(NULL, "保存しました！", "Save Map Data", MB_OK);
}

void BGEditorScene::loadMapData() {
	tinyxml2::XMLDocument doc;
	doc.LoadFile("edit_stage_model.txt");
	auto root = doc.FirstChildElement("ModelRoot");
	for (const tinyxml2::XMLNode* node = root->FirstChild(); node; node = node->NextSibling()) {
		const tinyxml2::XMLElement* element = node->ToElement();
		if (element) {
			if (strcmp(element->Name(), "SpriteRenderer") == 0) {
				auto newObj = new SpriteRenderer();
				newObj->loadXmlElement(element);
				int texIndex = newObj->getObjectId();
				newObj->setHandle(this->getImageHandle(texIndex));
				this->insertObject(newObj);
			}
			if (strcmp(element->Name(), "MV1Renderer") == 0) {
				auto newObj = new MV1Renderer();
				newObj->loadXmlElement(element);
				int modelIndex = newObj->getObjectId();
				newObj->changeModel(this->getModelHandle(modelIndex));
				this->insertObject(newObj);
			}
			if (strcmp(element->Name(), "Camera") == 0) {
				this->camera->loadXml(element);
			}
			if (strcmp(element->Name(), "Texture") == 0) {
				const char* path = element->GetText();
				int img = LoadGraph(path);
				if (img != -1) {
					ImgInfo info = { img , path };
					this->imgList.push_back(info);
				}
			}
			if (strcmp(element->Name(), "Model") == 0) {
				const char* path = element->GetText();
				int model = MV1LoadModel(path);
				if (model != -1) {
					ModelInfo info = { model , path };
					this->modelList.push_back(info);
				}
			}
		}
	}
}

bool BGEditorScene::update(){
	auto key = Keyboard::getIns();
	if (key->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
		PostMessage(GetMainWindowHandle(), WM_QUIT, NULL, NULL);
		return false;
	}
	for (auto s : this->objList) {
		s->update();
	}
	for (auto s : this->gameUITask) {
		s->update();
	}
	for (auto v : this->viewTask) {
		v->update();
	}
	for (auto gui : this->guiTask) {
		gui->update();
	}
	this->camera->update();
	return true;
}

void BGEditorScene::draw() {
	for (auto s : this->objList) {
		s->draw();
	}
	for (auto s : this->gameUITask) {
		s->draw();
	}
	for (auto v : this->viewTask) {
		v->draw();
	}
	for (auto gui : this->guiTask) {
		gui->draw();
	}
	this->camera->draw();
}
