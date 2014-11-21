#include "Rule.hpp"


CRule::CRule(std::shared_ptr<AppEnv>app_env):
CScene(app_env),
m_font(std::make_unique<Font>(90))
{
	m_change_scene = Type::RULE;
}

//　更新
CScene::Type CRule::Update(){
	Control();
	return m_change_scene;
}

//　描画
void CRule::Draw(){
	m_font->DrawCenter(L"ルール画面", 0, 200, Color(1, 1, 1));
}

//　操作
void CRule::Control(){
	if (m_app_env->isPushKey(GLFW_KEY_ENTER)){
		m_change_scene = Type::TITLE;
	}
}