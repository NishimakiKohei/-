#pragma once
#include "resource\Resource.hpp"
#include "scene\SceneManager.hpp"
#include "Uncopyable.hpp"
#include <memory>

//========================================
//ゲームアプリケーションクラス
//========================================

class CGameApplication : private Uncopyable{
public:

	CGameApplication();


	//　更新
	void Update();
private:

	std::shared_ptr<AppEnv>m_app_env;								//　アプリイベント
	std::unique_ptr<CSceneManager>m_scene_manager;					//　シーンマネージャー
	CResource& m_res;												//　リソース

	//　起動条件
	bool LaunchCondition();
};

