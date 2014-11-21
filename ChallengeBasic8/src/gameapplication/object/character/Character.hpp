#pragma once
#include "../Object.hpp"
#include "../../resource/Resource.hpp"

class CCharacter : public Object{
public:
	CCharacter(std::shared_ptr<AppEnv>m_app_env);

protected:
	Vec2f m_hit_pos;
	Vec2f m_hit_size;
	CResource& m_res;
	std::shared_ptr<AppEnv>m_app_env;									//　アプリイベントを入れる箱
	std::vector<std::shared_ptr<Object>>m_obj_list;						//　芋
};

