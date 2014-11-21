#pragma once
#include "../Uncopyable.hpp"
#include "../../lib/texture.hpp"
#include <memory>
//========================================
//リソースクラス
//========================================
class CResource : private Uncopyable{
public:
	//　インスタンスの取得
	static CResource &GetInstance(){
		static CResource instance;
		return instance;
	}

	//　画像
	const std::unique_ptr<Texture>m_title_graph;
	const std::unique_ptr<Texture>m_stage_graph;
	const std::unique_ptr<Texture>m_player_graph;
	const std::unique_ptr<Texture>m_holyghost_graph;
	const std::unique_ptr<Texture>m_sweetpotato_graph;
	const std::unique_ptr<Texture>m_enemy_graph;
	const std::unique_ptr<Texture>m_enemy_death_graph;


	//　音楽
	const std::unique_ptr<Media>m_stage_sound;
	const std::unique_ptr<Media>m_title_sound;
	std::vector<std::unique_ptr<Media>>m_title_button_sound;
	std::vector<std::unique_ptr<Media>>m_hit_sound;
	const std::unique_ptr<Media>m_start_sound;
	const std::unique_ptr<Media>m_finish_sound;
private:
	CResource();
};

