#include "Player.hpp"
#include "../../item/sweet_potato/SweetPotato.hpp"
#include "../holyghost/HolyGhost.hpp"
#include "../enemy/Enemy.hpp"

CPlayer::CPlayer(std::shared_ptr<AppEnv>app_env) :
CCharacter(app_env),
m_score(0),
m_combo_num(-1)
{
	m_pos = m_app_env->mousePosition();
	m_size = Vec2f(128, 128);
}

//　最初の処理
void CPlayer::Start(std::vector<std::shared_ptr<Object>>obj_list){
	m_combo_num = -1;
	m_score = 0;
	m_pos = Vec2f(0, 0);
	m_obj_list = obj_list;
}

//　更新
void CPlayer::Update(){
	if (!m_is_active)return;
	Control();
	ComboUpdate();
}

//　描画
void CPlayer::Draw(){
	if (!m_is_active)return;
	drawTextureBox(m_pos.x() - m_size.x() / 2, m_pos.y() - m_size.y() / 2, m_size.x(), m_size.y(),
		0, 0, 512, 512,
		*m_res.m_player_graph, Color(1, 1, 1));
}

//　コンボの更新
void CPlayer::ComboUpdate(){
	if (!m_is_active)return;
	UpdateComboOfSweetpotato();
	UpdateComboOfHolyghost();
	UpdateComboOfEnemy();
}

//　芋のコンボ更新
void CPlayer::UpdateComboOfSweetpotato(){
	for (auto it = m_obj_list.begin(); it != m_obj_list.end(); it++){
		if ((*it)->GetType() == Type::SweetPotato){
			if (((*it)->GetisActive()))return;
			if (std::dynamic_pointer_cast<CSweetPotato>(*it)->GetisSwipe()){
				m_combo_num = -1;
			}
			else{
				m_combo_num++;
			}
		}
	}
}

//　神様のコンボ更新
void CPlayer::UpdateComboOfHolyghost(){
	for (auto it = m_obj_list.begin(); it != m_obj_list.end(); it++){
		if ((*it)->GetType() == Type::HolyGhost){
			if (((*it)->GetisActive()))return;
			if (std::dynamic_pointer_cast<CHolyGhost>(*it)->GetisSwipe()){
				m_combo_num = -1;
			}
			else{
				m_combo_num++;
			}
		}
	}
}

//　虫のコンボ更新
void CPlayer::UpdateComboOfEnemy(){
	for (auto it = m_obj_list.begin(); it != m_obj_list.end(); it++){
		if ((*it)->GetType() == Type::Enemy){
			if (((*it)->GetisActive()))return;
			if (std::dynamic_pointer_cast<CEnemy>(*it)->GetisSwipe()){
				m_combo_num = -1;
			}
			else{
				m_combo_num++;
			}
		}
	}
}

void CPlayer::UpdateOfObject(std::vector<std::shared_ptr<Object>>obj_list){
	m_obj_list = obj_list;
}

//　操作
void CPlayer::Control(){

	m_pos = m_app_env->mousePosition();

}