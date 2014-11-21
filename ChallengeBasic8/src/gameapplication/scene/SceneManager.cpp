#include "SceneManager.hpp"
#include "title\Title.hpp"
#include "stage\Stage.hpp"
#include "rule\Rule.hpp"
#include "ranking\Ranking.hpp"
#include "result\Result.hpp"


CSceneManager::CSceneManager(std::shared_ptr<AppEnv>app_env) :
m_factory(std::make_unique<CSceneFactory>(app_env)),
m_scene(nullptr),
m_now_scene(CScene::Type::TITLE),
m_app_env(app_env),
m_alpha(255)
{
}

//　遷移処理
void CSceneManager::Transition(){
	m_scene = m_factory->GetScene(m_now_scene);
	m_old_scene = m_now_scene;
	FadeIn();
}

//　更新
void CSceneManager::Update(){
	Transition();
	while (LaunchCondition() && m_now_scene == m_scene->Update()){
		Draw();
	}
	Finalize();
}

//　描画
void CSceneManager::Draw(){

	// 描画準備
	m_app_env->setupDraw();

	m_scene->Draw();

	drawFillBox(-m_scene->WIDTH / 2, -m_scene->HEIGHT / 2, m_scene->WIDTH, m_scene->HEIGHT, color256(0, 0, 0, m_alpha));

	// 画面更新
	m_app_env->update();
}

//　フェードイン
void CSceneManager::FadeIn(){
	while (LaunchCondition() && m_alpha > 0){
		m_alpha -= 2;
		Draw();
	}
}

//　フェードアウト
void CSceneManager::FadeOut(){
	while (LaunchCondition() && m_alpha < 255){
		m_alpha += 2;
		Draw();
	}
}

//　起動条件
bool CSceneManager::LaunchCondition(){
	return m_app_env->isOpen() && !m_app_env->isPushKey(GLFW_KEY_ESCAPE) ? true : false;
}

//　シーンの終了処理
void CSceneManager::Finalize(){
	m_now_scene = m_scene->Update();
	FadeOut();
}