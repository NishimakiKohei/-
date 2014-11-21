#include "Stage.hpp"
#include "../../object/character/player/Player.hpp"
#include "../../object/character/holyghost/HolyGhost.hpp"
#include "../../object/item/sweet_potato/SweetPotato.hpp"
#include "../../object/character/enemy/Enemy.hpp"
#include <algorithm>

CStage::CStage(std::shared_ptr<AppEnv>app_env) :
CScene(app_env),
ReadyCenterPosX(-80),
isRemove(false),
isReady(true),
isFinish(false),
m_count(0),
m_stage_num(1),
m_ready_count(0),
m_ready_pos(Vec2f(CScene::WIDTH/2 +100,0)),
m_finish_pos(Vec2f(CScene::WIDTH / 2 + 150, 0)),
m_res(CResource::GetInstance()),
m_time(30)
{
	for (auto &font : m_time_graph){
		font = std::make_unique<Font>(60, L"ニコモジ");
	}

	for (auto &font : m_score_num_graph){
		font = std::make_unique<Font>(40, L"ニコモジ");
	}

	m_score_graph = std::make_unique<Font>(40, L"ニコモジ");
	m_stage_graph = std::make_unique<Font>(40, L"ニコモジ");
	m_stage_num_graph = std::make_unique<Font>(40, L"ニコモジ");
	m_combo_graph = std::make_unique<Font>(40, L"ニコモジ");
	m_combo_num_graph = std::make_unique<Font>(40, L"ニコモジ");
	m_ready_graph = std::make_unique<Font>(60, L"Pacifico");
	m_finish_graph = std::make_unique<Font>(60, L"Pacifico");



	m_obj_list.emplace_back(std::make_shared<CPlayer>(app_env));
	m_obj_list.emplace_back(std::make_shared<CHolyGhost>(app_env,m_time));
	m_obj_list.emplace_back(std::make_shared<CEnemy>(app_env, m_obj_list));
	m_obj_list.emplace_back(std::make_shared<CSweetPotato>(app_env,m_obj_list[0]));

	std::dynamic_pointer_cast<CHolyGhost>(m_obj_list[1])->Start(m_obj_list);
	m_res.m_stage_sound->looping(true);
	m_res.m_stage_sound->play();
	std::dynamic_pointer_cast<CPlayer>(m_obj_list[0])->Start(m_obj_list);
	m_change_scene = Type::STAGE;
	m_time_digit[0] = 0;
	m_time_digit[1] = 3;
	m_time_digit[2] = 0;
	for (auto& font : m_score_digit){
		font = 0;
	}
}

//　更新
CScene::Type CStage::Update(){
	Ready();
	Finish();
	UpdateOfAfterReady();
	ScoreUpdate();
	StageNumUpdate();
	TimeDigitUpdate();
	RemoveObject();
	return m_change_scene;
}

//　描画
void CStage::Draw(){
	drawTextureBox(-CScene::WIDTH / 2, -CScene::HEIGHT / 2, CScene::WIDTH, CScene::HEIGHT, 
		0, 0, 1024, 512, 
		*m_res.m_stage_graph, Color(1, 1, 1));

	TimeDraw();
	ScoreNumDraw();
	ScoreStringDraw();
	StageStringDraw();
	ComboStringDraw();
	if (!isFinish){
		for (auto it = m_obj_list.rbegin(); it != m_obj_list.rend(); it++){
			(*it)->Draw();
		}
	}
	ReadyStringDraw();
	FinishStringDraw();
}

//　操作
void CStage::Control(){
	if (m_app_env->isPushKey(GLFW_KEY_ENTER)){
		m_change_scene = Type::RESULT;
		m_res.m_stage_sound->stop();

	}
}

//　制限時間の処理
void CStage::TimeUpdate(){
	AddCount();


	Transition();
}

//　時間が減少する処理
void CStage::AddCount(){
	m_count++;
	ToLoseTime();
}

//　時間の描画
void CStage::TimeDraw(){
	m_time_graph[static_cast<int>(Digit::ONE)]->DrawCenter(std::to_wstring(m_time_digit[0]), 
		m_time_graph[0]->GetSize(), CScene::HEIGHT / 2 - m_time_graph[0]->GetSize() / 2, 
		color256(102, 51, 255), 3);

	m_time_graph[static_cast<int>(Digit::TWO)]->DrawCenter(std::to_wstring(m_time_digit[1]),
		0, CScene::HEIGHT / 2 - m_time_graph[1]->GetSize() / 2, 
		color256(102, 51, 255), 3);

	m_time_graph[static_cast<int>(Digit::THREE)]->DrawCenter(std::to_wstring(m_time_digit[2]),
		-m_time_graph[2]->GetSize(), CScene::HEIGHT / 2 - m_time_graph[2]->GetSize() / 2,
		color256(102, 51, 255), 3);
}

//　	桁の処理
void CStage::TimeDigitUpdate(){
	m_time_digit[static_cast<int>(Digit::ONE)] = m_time.count() % 10;
	m_time_digit[static_cast<int>(Digit::TWO)] = m_time.count() / 10 % 10;
	m_time_digit[static_cast<int>(Digit::THREE)] = m_time.count() / 100;
}

//　時間の更新
void CStage::ToLoseTime(){
	if (!(m_count % 60 == 0))return;

	m_time--;
}

//　スコアの描画
void CStage::ScoreNumDraw(){

	m_score_num_graph[static_cast<int>(Digit::ONE)]->Draw(std::to_wstring(m_score_digit[0]),
		-CScene::WIDTH / 2 + m_score_num_graph[0]->GetSize() * 4/1.5, CScene::HEIGHT / 2 - (m_score_num_graph[0]->GetSize() / 1.5)*2,
		color256(102, 51, 255));

	m_score_num_graph[static_cast<int>(Digit::TWO)]->Draw(std::to_wstring(m_score_digit[1]),
		-CScene::WIDTH / 2 + m_score_num_graph[1]->GetSize() * 3 / 1.5, CScene::HEIGHT / 2 - (m_score_num_graph[1]->GetSize() / 1.5) * 2,
		color256(102, 51, 255));

	m_score_num_graph[static_cast<int>(Digit::THREE)]->Draw(std::to_wstring(m_score_digit[2]),
		-CScene::WIDTH / 2 + m_score_num_graph[2]->GetSize() * 2 / 1.5, CScene::HEIGHT / 2 - (m_score_num_graph[2]->GetSize() / 1.5) * 2,
		color256(102, 51, 255));

	m_score_num_graph[static_cast<int>(Digit::FOUR)]->Draw(std::to_wstring(m_score_digit[3]),
		-CScene::WIDTH / 2 + m_score_num_graph[3]->GetSize() * 1 / 1.5, CScene::HEIGHT / 2 - (m_score_num_graph[3]->GetSize() / 1.5) * 2,
		color256(102, 51, 255));

	m_score_num_graph[static_cast<int>(Digit::FIVE)]->Draw(std::to_wstring(m_score_digit[4]),
		-CScene::WIDTH / 2 + m_score_num_graph[4]->GetSize() * 0 / 1.5, CScene::HEIGHT / 2 - (m_score_num_graph[4]->GetSize() / 1.5) * 2,
		color256(102, 51, 255));

}

//　スコアの更新
void CStage::ScoreUpdate(){
	std::shared_ptr<CPlayer>player = std::dynamic_pointer_cast<CPlayer>(m_obj_list[0]);

	m_score_digit[static_cast<int>(Digit::ONE)] = player->GetScore() % 10;
	m_score_digit[static_cast<int>(Digit::TWO)] = player->GetScore() / 10 % 10;
	m_score_digit[static_cast<int>(Digit::THREE)] = player->GetScore() / 100 % 10;
	m_score_digit[static_cast<int>(Digit::FOUR)] = player->GetScore() / 1000 % 10;
	m_score_digit[static_cast<int>(Digit::FIVE)] = player->GetScore() / 10000;
}

//　スコアの文字描画
void CStage::ScoreStringDraw(){
	m_score_graph->Draw(L"SCORE",
		-CScene::WIDTH / 2, CScene::HEIGHT / 2 - m_score_graph->GetSize() / 1.5,
		color256(102, 51, 255));

}

//　ステージの文字描画
void CStage::StageStringDraw(){
	m_stage_graph->Draw(L"STAGE",
		-CScene::WIDTH / 2, -CScene::HEIGHT / 2,
		color256(102, 51, 255));
	m_stage_num_graph->Draw(std::to_wstring(m_stage_num),
		- CScene::WIDTH / 2 + m_stage_graph->GetSize() * 4, -CScene::HEIGHT / 2,
		color256(102, 51, 255));
}

//　ステージ数の更新
void CStage::StageNumUpdate(){
	if (m_obj_list[2]->GetisActive())return;
	m_stage_num++;
}

//　コンボの文字描画
void CStage::ComboStringDraw(){
	if ((std::dynamic_pointer_cast<CPlayer>(m_obj_list[0])->GetCombo()) <= 0)return;
	m_combo_graph->Draw(L"COMBO!",
		CScene::WIDTH / 2 - m_combo_graph->GetSize() * 9, CScene::HEIGHT / 2 - m_combo_graph->GetSize() * 2,
		color256(102, 51, 255));
	m_combo_num_graph->Draw(std::to_wstring(std::dynamic_pointer_cast<CPlayer>(m_obj_list[0])->GetCombo()),
		CScene::WIDTH / 2 - m_combo_graph->GetSize() * 4, CScene::HEIGHT / 2 - m_combo_graph->GetSize() * 2,
		color256(102, 51, 255));
}

//　遷移処理
void CStage::Transition(){
	if (isFinish)return;
	if (m_time.count() <= 0){
		m_time = std::chrono::seconds(0);
		isFinish = true;
		m_res.m_stage_sound->stop();
		m_res.m_finish_sound->play();
	}
}

//　準備後の処理
void CStage::UpdateOfAfterReady(){
	if (isReady || isFinish)return;
	Control();
	TimeUpdate();

	for (auto &Obj : m_obj_list){
		Obj->Update();
	}
	std::dynamic_pointer_cast<CPlayer>(m_obj_list[0])->UpdateOfObject(m_obj_list);

}

//　準備の処理
void CStage::Ready(){
	if (!isReady)return;
	m_ready_count++;
	MoveReadyStirng();
	if (m_ready_count > 300){
		isReady = false;
		m_res.m_start_sound->play();
	}
}

//　レディーの描画
void CStage::ReadyStringDraw(){
	if (!isReady)return;
	m_ready_graph->Draw("Ready",
		m_ready_pos.x(), m_ready_pos.y(),
		color256(102, 51, 255));
}

//　レディーの移動処理
void CStage::MoveReadyStirng(){
	if (!(m_ready_count > 120 && 240 > m_ready_count))return;
	m_ready_pos.x() -= 10;
	if (m_ready_pos.x() < ReadyCenterPosX){
		m_ready_pos.x() = ReadyCenterPosX;
	}
}

//　準備の処理
void CStage::Finish(){
	if (!isFinish)return;
	MoveFinishStirng();
}

//　準備の描画
void CStage::FinishStringDraw(){
	if (!isFinish)return;
	m_finish_graph->Draw("Finish",
		m_finish_pos.x(), m_finish_pos.y(),
		color256(102, 51, 255));
}

//　レディの移動処理
void CStage::MoveFinishStirng(){
	if (isRemove)return;
	m_finish_pos.x() -= 10;
	if (m_finish_pos.x() < ReadyCenterPosX){
		m_finish_pos.x() = ReadyCenterPosX;
		m_change_scene = Type::RESULT;
		//m_obj_list.clear();
		//m_obj_list.emplace_back(std::make_shared<CPlayer>(m_app_env, m_is_control));
		//m_obj_list.emplace_back(std::make_shared<CSweetPotato>(m_app_env, m_obj_list[0]));
		//m_obj_list.emplace_back(std::make_shared<CHolyGhost>(m_app_env, m_time));
		//std::dynamic_pointer_cast<CHolyGhost>(m_obj_list[2])->Start(m_obj_list);
		isRemove = true;
	}
}

void CStage::RemoveObject(){
	auto it = m_obj_list.begin();
	while (it != m_obj_list.end()){
		if ((*it)->isRemove()){
			auto type = (*it)->GetType();
			m_obj_list.erase(it);
			switch (type){
			case Object::Type::SweetPotato:
				m_obj_list.emplace_back(std::make_shared<CSweetPotato>(m_app_env, m_obj_list[0]));
				break;
			case Object::Type::HolyGhost:
				m_obj_list.emplace_back(std::make_shared<CHolyGhost>(m_app_env, m_time));
				std::dynamic_pointer_cast<CHolyGhost>(m_obj_list[3])->Start(m_obj_list);
				break;
			case Object::Type::Enemy:
				m_obj_list.emplace_back(std::make_shared<CEnemy>(m_app_env, m_obj_list));
				break;
			}
		}
		it++;
	}
}