#include "Character.hpp"


CCharacter::CCharacter(std::shared_ptr<AppEnv>app_env) :
m_res(CResource::GetInstance()),
m_app_env(app_env)
{
}