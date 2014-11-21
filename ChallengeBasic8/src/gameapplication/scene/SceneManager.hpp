#pragma once
#include "../Uncopyable.hpp"
#include "../utility/Font.hpp"
#include "Scene.h"
#include "SceneFactory.h"
#include "../../lib/appEnv.hpp"
#include <memory>
#include <unordered_map>
#include <functional>

//========================================
//シーンマネージャークラス
//========================================

class CSceneManager :private Uncopyable{

public:
	CSceneManager(const std::shared_ptr<AppEnv>app_env);

	void Update();															//　更新

private:

	std::unique_ptr<CSceneFactory>m_factory;
	std::unique_ptr<CScene> m_scene;										//　シーンを入れる箱
	CScene::Type m_now_scene;												//　現在のシーン
	CScene::Type m_old_scene;												//　遷移する前のシーン
	std::shared_ptr<AppEnv>m_app_env;										//　アプリイベント
	int m_alpha;															//　アルファ値

	//　描画
	void Draw();

	// 遷移処理
	void Transition();

	//　フェードイン
	void FadeIn();

	//　フェードアウト
	void FadeOut();

	//　起動条件
	bool LaunchCondition();

	//　シーンの終了処理
	void Finalize();
};