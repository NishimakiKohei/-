#pragma once
#include "../Character.hpp"

class CPlayer : public CCharacter
{
public:
	CPlayer(std::shared_ptr<AppEnv>app_env);

	//　最初の処理
	void Start(std::vector<std::shared_ptr<Object>>obj_list);

	//　オブジェくトの更新
	void UpdateOfObject(std::vector<std::shared_ptr<Object>>obj_list);

	//　更新
	void Update();

	//　描画
	void Draw();

	//　スコアを取得
	int GetScore(){ return m_score; }

	//　スコアの変更
	void TransformOfScore(int score){ m_score = score; }

	//　コンボ数を取得
	int GetCombo(){ return m_combo_num; }

private:
	int m_score;														//　スコア
	int m_combo_num;													//　コンボ

	//　コンボの更新
	void ComboUpdate();

	//　芋のコンボ更新
	void UpdateComboOfSweetpotato();

	//　神様のコンボ更新
	void UpdateComboOfHolyghost();

	//　虫のコンボ更新
	void UpdateComboOfEnemy();

	//　操作
	void Control();
};

