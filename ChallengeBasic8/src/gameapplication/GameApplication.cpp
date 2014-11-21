#include "GameApplication.hpp"
#include <ctime>

CGameApplication::CGameApplication() :
m_app_env(std::make_shared<AppEnv>(CScene::WIDTH, CScene::HEIGHT, false, true)),
m_scene_manager(std::make_unique<CSceneManager>(m_app_env)),
m_res(CResource::GetInstance())
{
}

//@XV
void CGameApplication::Update(){
	while (LaunchCondition()){
		m_app_env->flushInput();
		m_scene_manager->Update();
	}
}

bool CGameApplication::LaunchCondition(){
	return m_app_env->isOpen() && !m_app_env->isPushKey(GLFW_KEY_ESCAPE) ? true : false;
}