#pragma once
#include "Scene.h"
#include <unordered_map>

//========================================
//シーンファクトリークラス
//========================================

class CSceneFactory{
public:
	CSceneFactory(std::shared_ptr<AppEnv>app_env);

	//　シーンを取得
	std::unique_ptr<CScene> GetScene(CScene::Type type);

private:
	std::unordered_map<CScene::Type, std::function<void()>>m_scene_create_list;			//　シーン生成リスト
	std::unique_ptr<CScene> m_scene;													//　シーンの箱
};