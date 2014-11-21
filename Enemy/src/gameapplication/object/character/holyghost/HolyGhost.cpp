#include "HolyGhost.hpp"
#include "../../../utility/CRandom.hpp"
#include "../../../scene/SceneManager.hpp"
#include "../../../utility/Collision.hpp"
#include "../player/Player.hpp"


CHolyGhost::CHolyGhost(std::shared_ptr<AppEnv>app_env,std::chrono::seconds& time) :
CCharacter(app_env),
ADD_SCORE(1000),
DIFF_SCORE(-500),
ADD_TIME(10),
DIFF_TIME(-10),
m_istap(false),
m_isswipe(false),
isRemove(false),
m_time(time),
m_score_graph(std::make_unique<Font>(60, L"FatBoy"))
{
	m_size = Vec2f(64, 64);
	m_pos = Vec2f(CRandom::Uniform(-CScene::WIDTH / 2 + m_size.x(), CScene::WIDTH / 2 - m_size.x()), 
		CRandom::Uniform(-CScene::HEIGHT / 2 + m_size.y(), CScene::HEIGHT / 2 - m_size.y()-100));
	m_hit_pos = m_pos;
	m_hit_size = m_size;
	m_res.m_hit_sound[1]->gain(2.0);
	m_type = Type::HolyGhost;
	m_score_pos = m_pos + Vec2f(0, 50);
}

//　最初の処理
void CHolyGhost::Start(std::vector<std::shared_ptr<Object>>obj_list){
	m_obj_list = obj_list;
}

//　更新
void CHolyGhost::Update(){
	UpdateOfTap();
	UpdateOfSwaipe();
	isHit(m_obj_list[0]->GetPos());
	Remove();
}

//　描画
void CHolyGhost::Draw(){
	DrawOfScore();
	HolyGhostDraw();
}

void CHolyGhost::isHit(Vec2f& pos){
	if (isRemove)return;
	if (Collision::CircleAndPoint(m_hit_pos, m_hit_size.x(), pos)){
		if (m_app_env->isPushButton(Mouse::LEFT)){
			m_istap = true;
		}
		else if (m_app_env->isPressButton(Mouse::LEFT)){
			m_isswipe = true;
		}
	}
}

//　タップしたときの処理
void CHolyGhost::UpdateOfTap(){
	if (!m_istap || isRemove)return;
	std::shared_ptr<CPlayer>player = std::dynamic_pointer_cast<CPlayer>(m_obj_list[0]);
	player->TransformOfScore(player->GetScore() + ADD_SCORE);
	m_time += ADD_TIME;
	m_res.m_hit_sound[0]->play();
	m_alpha = 255;
	isRemove = true;
}

//　スワイプしたときの処理
void CHolyGhost::UpdateOfSwaipe(){
	if (!m_isswipe || isRemove)return;
	std::shared_ptr<CPlayer>player = std::dynamic_pointer_cast<CPlayer>(m_obj_list[0]);
	player->TransformOfScore(player->GetScore() + DIFF_SCORE);
	m_time += DIFF_TIME;
	if (player->GetScore() < 0){
		player->TransformOfScore(0);
	}
	m_res.m_hit_sound[1]->play();
	m_alpha = 255;
	isRemove = true;
}

//　タップしたときのスコア表示
void CHolyGhost::DrawOfTapScore(){
	if (!m_istap)return;
	m_score_graph->DrawCenter(L"+1000 +sec10", m_score_pos.x(), m_score_pos.y(),
		color256(0, 0, 255, m_alpha), 5);
}

void CHolyGhost::UpdateOfScore(){
	if (m_alpha <= 0)return;
	m_alpha -= 2;
	m_score_pos.y() += 1;
}

void CHolyGhost::DrawSWeetPotato(){
	if (isRemove)return;

	drawTextureBox(m_pos.x(), m_pos.y(), m_size.x(), m_size.y(),
		0, 0, 512, 512,
		*m_res.m_sweetpotato_graph, Color(1, 1, 1));

	drawCircle(m_hit_pos.x() + m_hit_size.x() / 2, m_hit_pos.y() + m_hit_size.y() / 2,
		m_hit_size.x() / 2, m_hit_size.y() / 2,
		30, 5, Color(1, 0, 0));
}

//　削除
void CHolyGhost::Remove(){
	if (!isRemove)return;
	UpdateOfScore();
	if (m_alpha <= 0){
		m_is_active = false;
	}
}

//　スワイプしたときのスコア
void CHolyGhost::DrawOfSwipeScore(){
	if (!m_isswipe)return;
	m_score_graph->DrawCenter(L"-500 -sec10", m_score_pos.x(), m_score_pos.y(),
		color256(255, 0, 0, m_alpha), 5);
}

//　スコア表示
void CHolyGhost::DrawOfScore(){
	if (m_alpha <= 0)return;
	DrawOfTapScore();
	DrawOfSwipeScore();
}

void CHolyGhost::HolyGhostDraw(){
	if (isRemove)return;

	drawTextureBox(m_pos.x(), m_pos.y(), m_size.x(), m_size.y(),
		0, 0, 256, 256,
		*m_res.m_holyghost_graph, Color(1, 1, 1));

	drawCircle(m_hit_pos.x() + m_hit_size.x() / 2, m_hit_pos.y() + m_hit_size.y() / 2,
		m_hit_size.x() / 2, m_hit_size.y() / 2,
		30, 5, Color(1, 0, 0));
}