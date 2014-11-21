#include "Resource.hpp"



CResource::CResource():
m_title_graph(std::make_unique<Texture>("res/graph/title_graph.png")),
m_stage_graph(std::make_unique<Texture>("res/graph/stage_graph.png")),
m_player_graph(std::make_unique<Texture>("res/graph/player/player.png")),
m_holyghost_graph(std::make_unique<Texture>("res/graph/holyghost/holyghost.png")),
m_sweetpotato_graph(std::make_unique<Texture>("res/graph/item/sweet_potato.png")),
m_stage_sound(std::make_unique<Media>("res/sound/stage_bg.wav")),
m_title_sound(std::make_unique<Media>("res/sound/title_bg.wav")),
m_start_sound(std::make_unique<Media>("res/sound/start.wav")),
m_finish_sound(std::make_unique<Media>("res/sound/finish.wav")),
m_enemy_graph(std::make_unique<Texture>("res/graph/enemy/enemy.png")),
m_enemy_death_graph(std::make_unique<Texture>("res/graph/enemy/death.png"))
{
	m_title_button_sound.emplace_back(std::make_unique<Media>("res/sound/title_button01.wav"));
	m_title_button_sound.emplace_back(std::make_unique<Media>("res/sound/title_button02.wav"));
	m_hit_sound.emplace_back(std::make_unique<Media>("res/sound/hit01.wav"));
	m_hit_sound.emplace_back(std::make_unique<Media>("res/sound/hit02.wav"));

}
