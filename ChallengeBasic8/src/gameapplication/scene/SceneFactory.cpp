#include "SceneFactory.h"
#include "title\Title.hpp"
#include "stage\Stage.hpp"
#include "rule\Rule.hpp"
#include "result\Result.hpp"
#include "ranking\Ranking.hpp"

CSceneFactory::CSceneFactory(std::shared_ptr<AppEnv>app_env)
{
	m_scene_create_list.emplace(CScene::Type::TITLE, [=]{m_scene = std::make_unique<CTitle>(app_env); });
	m_scene_create_list.emplace(CScene::Type::STAGE, [=]{m_scene = std::make_unique<CStage>(app_env); });
	m_scene_create_list.emplace(CScene::Type::RULE, [=]{m_scene = std::make_unique<CRule>(app_env); });
	m_scene_create_list.emplace(CScene::Type::RESULT, [=]{m_scene = std::make_unique<CResult>(app_env); });
	m_scene_create_list.emplace(CScene::Type::RANKING, [=]{m_scene = std::make_unique<CRanking>(app_env); });
}

//Å@ÉVÅ[ÉìÇéÊìæ
std::unique_ptr<CScene> CSceneFactory::GetScene(CScene::Type type){
	(m_scene_create_list.find(type)->second)();
	return std::move(m_scene);
}