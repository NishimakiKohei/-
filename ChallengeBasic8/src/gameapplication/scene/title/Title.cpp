#include "Title.hpp"
#include "../../../lib/graph.hpp"


CTitle::CTitle(std::shared_ptr<AppEnv>app_env) :
CScene(app_env),
STR_SELECT_HEIGHT(-150),
m_now_select(Scene::STAGE),
m_res(CResource::GetInstance())
{
	m_change_scene = Type::TITLE;
	StringInit();
	AddTransitionList();
	AddSelectEffectList();
	m_res.m_title_sound->looping(true);
	m_res.m_title_sound->play();
}

//　更新
CScene::Type CTitle::Update(){
	Control();
	RotationEffect();
	return m_change_scene;
}

//　描画
void CTitle::Draw(){
	drawTextureBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, 0, 0, 1024, 512,*m_res.m_title_graph, Color(1, 1, 1));
	m_title_str->DrawCenter("Defoliation", 0, HEIGHT / 2 - m_title_str->GetSize()*2, color256(102, 51, 255),10);

	m_title_select_str[0]->font_->DrawCenter(L"ゲームスタート", m_title_select_str[0]->pos_.x(), m_title_select_str[0]->pos_.y(), color256(102, 51, 255));
	m_title_select_str[1]->font_->DrawCenter(L"ランキング", m_title_select_str[1]->pos_.x(), m_title_select_str[1]->pos_.y(), color256(102, 51, 255));
	m_title_select_str[2]->font_->DrawCenter(L"ルール", m_title_select_str[2]->pos_.x(), m_title_select_str[2]->pos_.y(), color256(102, 51, 255));
}

//　操作
void CTitle::Control(){
	if (m_app_env->isPushKey(GLFW_KEY_ENTER)){
		m_change_scene = m_transition_list.find(m_now_select)->second;
		m_res.m_title_button_sound[1]->play();
		m_res.m_title_sound->stop();

	}
	else if (m_app_env->isPushKey(GLFW_KEY_LEFT)){
		m_now_select = static_cast<Scene>((static_cast<int>(m_now_select)+static_cast<int>(Scene::NUM) - 1) % static_cast<int>(Scene::NUM));
		m_res.m_title_button_sound[0]->play();
	}
	else if (m_app_env->isPushKey(GLFW_KEY_RIGHT)){

		m_now_select = static_cast<Scene>((static_cast<int>(m_now_select)+1) % static_cast<int>(Scene::NUM));
		m_res.m_title_button_sound[0]->play();
	}
}

//　文字の初期化
void CTitle::StringInit(){

	m_title_str = std::make_unique<Font>(60, L"Pacifico");

	m_title_select_str[0] = std::make_unique<StringData>(Vec2f(0, STR_SELECT_HEIGHT), 60, std::make_unique<Font>(60, L"ボクのたんけんニッキ"));
	m_title_select_str[1] = std::make_unique<StringData>(Vec2f(-400, STR_SELECT_HEIGHT), 30, std::make_unique<Font>(30, L"ボクのたんけんニッキ"));
	m_title_select_str[2] = std::make_unique<StringData>(Vec2f(400, STR_SELECT_HEIGHT), 30, std::make_unique<Font>(30, L"ボクのたんけんニッキ"));

}

//　回転のエフェクト
void CTitle::RotationEffect(){
	(m_select_effect_list.find(m_now_select)->second)();
}

//　遷移リストの追加
void CTitle::AddTransitionList(){
	m_transition_list.emplace(Scene::STAGE,Type::STAGE);
	m_transition_list.emplace(Scene::RULE, Type::RULE);
	m_transition_list.emplace(Scene::RANKING, Type::RANKING);
}


void CTitle::FontDrawOfSelectStage(){
	m_title_select_str[0]->pos_.x() = 0;
	m_title_select_str[1]->pos_.x() = -400;
	m_title_select_str[2]->pos_.x() = 400;

	m_title_select_str[0]->font_->TransformOfSize(60);
	m_title_select_str[1]->font_->TransformOfSize(30);
	m_title_select_str[2]->font_->TransformOfSize(30);
}
void CTitle::FontDrawOfSelectRule(){
	m_title_select_str[0]->pos_.x() = -400;
	m_title_select_str[1]->pos_.x() = 400;
	m_title_select_str[2]->pos_.x() = 0;

	m_title_select_str[0]->font_->TransformOfSize(30);
	m_title_select_str[1]->font_->TransformOfSize(30);
	m_title_select_str[2]->font_->TransformOfSize(60);
}
void CTitle::FontDrawOfSelectRanking(){
	m_title_select_str[0]->pos_.x() = 400;
	m_title_select_str[1]->pos_.x() = 0;
	m_title_select_str[2]->pos_.x() = -400;

	m_title_select_str[0]->font_->TransformOfSize(30);
	m_title_select_str[1]->font_->TransformOfSize(60);
	m_title_select_str[2]->font_->TransformOfSize(30);
}

//　選んでる項目によるエフェクトリストの追加
void CTitle::AddSelectEffectList(){
	m_select_effect_list.emplace(Scene::STAGE, std::bind(&CTitle::FontDrawOfSelectStage,this));
	m_select_effect_list.emplace(Scene::RULE, std::bind(&CTitle::FontDrawOfSelectRule,this));
	m_select_effect_list.emplace(Scene::RANKING, std::bind(&CTitle::FontDrawOfSelectRanking,this));
}