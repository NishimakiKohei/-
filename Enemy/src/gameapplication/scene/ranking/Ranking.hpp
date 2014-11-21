#pragma once
#include "../SceneManager.hpp"
#include <memory>

class CRanking : public CScene{
public:
	CRanking(std::shared_ptr<AppEnv>app_env);

	//　更新
	Type Update();

	//　描画
	void Draw();
private:
	std::unique_ptr<Font>m_font;

	//　操作
	void Control();

};

