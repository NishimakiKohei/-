#include "Implant.hpp"
#include "../../utility/Collision.hpp"

CImplant::CImplant(std::shared_ptr<AppEnv>app_env, std::shared_ptr<Object> object) :
m_res(CResource::GetInstance()),
m_istap(false),
m_isswipe(false),
isRemove(false),
m_app_env(app_env),
m_player(object)
{
}

void CImplant::isHit(Vec2f& pos){
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