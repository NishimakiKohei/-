#include "SweetPotato.hpp"
#include "../../../utility/CRandom.hpp"
#include "../../../scene/SceneManager.hpp"
#include "../../../object/character/player/Player.hpp"

CSweetPotato::CSweetPotato(std::shared_ptr<AppEnv>app_env, std::shared_ptr<Object> object) :
CImplant(app_env,object),
ADD_TAP_SCORE(1000),
ADD_SWIPE_SCORE(500),
m_score_graph(std::make_unique<Font>(60,L"FatBoy"))
{
	m_size = Vec2f(64, 64);
	m_pos = Vec2f(CRandom::Uniform(-CScene::WIDTH / 2 + m_size.x(), CScene::WIDTH / 2 - m_size.x()),
		CRandom::Uniform(-CScene::HEIGHT / 2 + m_size.y(), CScene::HEIGHT / 2 - m_size.y()-100));

	m_hit_pos = m_pos;
	m_hit_size = m_size;
	m_score_pos = m_pos + Vec2f(0,50);
	m_type = Type::SweetPotato;
	m_alpha = 0;
}

//　最初の処理
void CSweetPotato::Start(){
}

//　更新
void CSweetPotato::Update(){
	CImplant::isHit(m_player->GetPos());
	UpdateOfTap();
	UpdateOfSwaipe();
	Remove();


}

//　描画
void CSweetPotato::Draw(){

	DrawOfScore();
	DrawSWeetPotato();
}


//　タップしたときの処理
void CSweetPotato::UpdateOfTap(){
	if (!m_istap || isRemove)return;
	std::shared_ptr<CPlayer>player = std::dynamic_pointer_cast<CPlayer>(m_player);
	player->TransformOfScore(player->GetScore() + ADD_TAP_SCORE);
	m_res.m_hit_sound[0]->play();
	m_alpha = 255;
	isRemove = true;
}

//　スワイプしたときの処理
void CSweetPotato::UpdateOfSwaipe(){
	if (!m_isswipe || isRemove)return;
	std::shared_ptr<CPlayer>player = std::dynamic_pointer_cast<CPlayer>(m_player);
	player->TransformOfScore(player->GetScore() + ADD_SWIPE_SCORE);
	m_res.m_hit_sound[0]->play();
	m_alpha = 255;
	isRemove = true;
}

//　タップしたときのスコア表示
void CSweetPotato::DrawOfTapScore(){
	if (!m_istap)return;
	m_score_graph->DrawCenter(L"+1000", m_score_pos.x(), m_score_pos.y(),
		color256(0, 0, 255, m_alpha), 5);
}

void CSweetPotato::UpdateOfScore(){
	if (m_alpha <= 0)return;
	m_alpha -= 2;
	m_score_pos.y() += 1;
}

void CSweetPotato::DrawSWeetPotato(){
	if (isRemove)return;

	drawTextureBox(m_pos.x(), m_pos.y(), m_size.x(), m_size.y(),
		0, 0, 512, 512,
		*m_res.m_sweetpotato_graph, Color(1, 1, 1));

	drawCircle(m_hit_pos.x() + m_hit_size.x() / 2, m_hit_pos.y() + m_hit_size.y() / 2,
		m_hit_size.x() / 2, m_hit_size.y() / 2,
		30, 5, Color(1, 0, 0));
}

//　削除
void CSweetPotato::Remove(){
	if (!isRemove)return;
	UpdateOfScore();
	if (m_alpha <= 0){
		m_is_active = false;
	}
}

//　スワイプしたときのスコア
void CSweetPotato::DrawOfSwipeScore(){
	if (!m_isswipe)return;
	m_score_graph->DrawCenter(L"+500", m_score_pos.x(), m_score_pos.y(),
		color256(0, 0, 255, m_alpha), 5);
}

//　スコア表示
void CSweetPotato::DrawOfScore(){
	if (m_alpha <= 0)return;
	DrawOfTapScore();
	DrawOfSwipeScore();
}