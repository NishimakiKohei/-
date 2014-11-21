#include "Enemy.hpp"
#include "../../../scene/SceneManager.hpp"
#include "../player/Player.hpp"
#include "../../../utility/CRandom.hpp"

CEnemy::CEnemy(std::shared_ptr<AppEnv>app_env, std::vector<std::shared_ptr<Object>>obj_list) :
CCharacter(app_env),
count(0),
press_count(0),
push_count(0),
flag(0),
move_flag(1),
isRemove(false),
ADD_SCORE(500),
DIFF_SCORE(-500),
m_isswipe(false),
m_istap(false),
m_score_graph(std::make_unique<Font>(60, L"FatBoy")),
m_obj_list(obj_list),
m_res(CResource::GetInstance())
{
	//m_pos = Vec2f(0, 0);
	m_size = Vec2f(128, 128);
	m_pos = Vec2f(CRandom::Uniform(-CScene::WIDTH / 2 + m_size.x(), CScene::WIDTH / 2 - m_size.x()),
		CRandom::Uniform(-CScene::HEIGHT / 2 + m_size.y(), CScene::HEIGHT / 2 - m_size.y() - 100));
	m_hit_pos = m_pos;
	m_hit_size = m_size;
	m_type = Type::Enemy;
	m_score_pos = m_pos + Vec2f(0, 50);
	m_alpha = 0;
}

//　更新
void CEnemy::Update(){
	count += 1;

	if (flag == 0 && count % 200 == 0)move_flag *= -1;
	if (flag == 0 && move_flag == 1)m_pos.x() += 0.5;
	if (flag == 0 && move_flag == -1)m_pos.x() -= 0.5;
	if (m_pos.x() <= - CScene::WIDTH/ 2)move_flag = 1;
	if (m_pos.x() >= CScene::WIDTH / 2 + 128)move_flag = -1;

	Remove();
}

//　描画
void CEnemy::Draw(){

	DrawOfScore();

	if (flag == 0 && hit(m_obj_list[0]->GetPos()) == 1){
		m_alpha = 255;
		m_istap = true;
		flag = 1;
	}
	if (flag == 1){
		push_count += 1;
		drawTextureBox(m_pos.x(), m_pos.y(), m_size.x(), m_size.y(), 0, 0, m_size.x(), m_size.y(), *m_res.m_enemy_death_graph, Color(1, 1, 1));
		if (push_count == 40){
			isRemove = true;
			//m_is_active = false;
		}
	}

	if (hit(m_obj_list[0]->GetPos()) == 1){
		std::shared_ptr<CPlayer>player = std::dynamic_pointer_cast<CPlayer>(m_obj_list[0]);
		player->TransformOfScore(player->GetScore() + ADD_SCORE);
	}
	
	if (flag ==2&&press_count==1 ){
		std::shared_ptr<CPlayer>player = std::dynamic_pointer_cast<CPlayer>(m_obj_list[0]);
		player->TransformOfScore(player->GetScore() + DIFF_SCORE);
		if (player->GetScore() < 0){
			player->TransformOfScore(0);
		}
	}


	if (flag == 0 && hit(m_obj_list[0]->GetPos()) == 2){
		m_alpha = 255;
		m_isswipe = true;
		flag = 2;
	}

	if (flag == 2){
		press_count += 1;
		if (press_count % 3 == 0){
			m_pos.x() += CRandom::Uniform(-5, 5);
			m_pos.y() += CRandom::Uniform(-5, 5);
		}
		if (press_count == 60){
			isRemove=true;
			//m_pos.x() = CRandom::Uniform(-CScene::WIDTH / 2, CScene::WIDTH / 2 - 128);
			//m_pos.y() = CRandom::Uniform(-CScene::HEIGHT / 2, CScene::HEIGHT / 2 - 128);
			//press_count = 0;
			//flag = 0;
		}
	}


	if (move_flag==1&&flag == 0 || move_flag==1&&flag == 2){
		drawTextureBox(m_pos.x(), m_pos.y(), m_size.x(), m_size.y(), 0, 0, m_size.x(), m_size.y(), *m_res.m_enemy_graph, Color(1, 1, 1));
	}
	if (move_flag == -1 && flag == 0 || move_flag == -1 && flag == 2){
		drawTextureBox(m_pos.x(), m_pos.y(), m_size.x(), m_size.y(), m_size.x(), 0, -m_size.x(), m_size.y(), *m_res.m_enemy_graph, Color(1, 1, 1));
	}
}

//　当たり判定
int CEnemy::hit(Vec2f& point_pos){
	if (m_pos.x() < point_pos.x() && point_pos.x() < m_pos.x() + m_size.x()){
		if (m_pos.y() < point_pos.y() && point_pos.y() < m_pos.y() + m_size.y()){
			if (m_app_env->isPushButton(Mouse::LEFT)){
				return 1;
			}
			else if (m_app_env->isPressButton(Mouse::LEFT)){
				return 2;
			}
		}
	}
	return 0;
}

void CEnemy::UpdateOfScore(){
	if (m_alpha <= 0)return;
	m_alpha -= 2;
	m_score_pos.y() += 1;
}

void CEnemy::Remove(){
	if (flag==0)return;
	UpdateOfScore();
	if (m_alpha <= 0){
		m_is_active = false;
	}
}

void CEnemy::DrawOfTapScore(){
	if (!m_istap)return;
	m_score_graph->DrawCenter(L"+500", m_score_pos.x(), m_score_pos.y(),
		color256(0, 0, 255, m_alpha), 5);
}

void CEnemy::DrawOfSwipeScore(){
	if (!m_isswipe)return;
	m_score_graph->DrawCenter(L"-500", m_score_pos.x(), m_score_pos.y(),
		color256(255, 0, 0, m_alpha), 5);
}

void CEnemy::DrawOfScore(){
	//if (m_alpha <= 0)return;
	DrawOfTapScore();
	DrawOfSwipeScore();
}
