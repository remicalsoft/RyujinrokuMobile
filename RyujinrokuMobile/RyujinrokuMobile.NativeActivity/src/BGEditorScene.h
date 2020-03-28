#pragma once
#include "Scene.h"
#include <vector>
#include "DxGUI.h"
#include "SpriteRenderer.h"
#include "Camera.h"


class BGEditorScene : public Scene {
public :
	struct ImgInfo {
		int handle;
		std::string path;
	};
	struct ModelInfo {
		int handle;
		std::string path;
	};
private:
	std::vector<DxGUI::Window*> viewTask;
	std::vector<Task*> guiTask;
	std::vector<Object*> objList;
	std::vector<ImgInfo> imgList;
	std::vector<ModelInfo> modelList;
	std::vector<Task*> gameUITask;
	int currentObj;
	int currentTex;
	int currentModelIndex;
	Camera* camera;
public:
	BGEditorScene(ISceneChangedListener *impl, ScenePrmBase* prm);
	~BGEditorScene();
	virtual bool update() override;
	virtual void draw() override;
	void insertObject(Object* obj);
	void deleteObject(Object* current);
	void copyObject(Object* current);
	void saveMapData();
	void loadMapData();
	Object* getCurrentObject();
	int getImageHandle(unsigned int index);
	int getModelHandle(unsigned int index);
	int getCurrentTexIndex();
	int getCurrentImgHandle();
	int getCurrentModelHandle();
	int nextSpriteIndex();
	int prevSpriteIndex();
	int nextTexIndex();
	int prevTexIndex();
	int nextModelIndex();
	int prevModelIndex();

	template<typename T>
	T* getTaskById() {
		T* result = NULL;
		for (auto v : this->viewTask) {
			result = dynamic_cast<T*>(v);
			if (result != NULL) {
				return result;
			}
		}
		return NULL;
	}
};