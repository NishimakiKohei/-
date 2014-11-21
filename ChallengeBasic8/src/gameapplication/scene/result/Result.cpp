#include "Result.hpp"


CResult::CResult(std::shared_ptr<AppEnv>app_env):
CScene(app_env),
m_font(std::make_unique<Font>(60))
{
	m_change_scene = Type::RESULT;
}


//　更新
CScene::Type CResult::Update(){
	Control();
	return m_change_scene;
}

//　描画
void CResult::Draw(){
	m_font->DrawCenter(L"リザルト画面", 0, 0, Color(1, 1, 1));
}

//　操作
void CResult::Control(){
	if (m_app_env->isPushKey(GLFW_KEY_ENTER)){
		m_change_scene = Type::TITLE;
	}
}