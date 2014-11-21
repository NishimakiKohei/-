#pragma once
#include "../Character.hpp"
#include "../../../utility/Font.hpp"
#include <chrono>

class CHolyGhost : public CCharacter
{
public:
	CHolyGhost(std::shared_ptr<AppEnv>app_env, std::chrono::seconds& time);

	//　最初の処理
	void Start(std::vector<std::shared_ptr<Object>>obj_list);

	//　更新
	void Update();

	//　描画
	void Draw();

	//　スワイプされたかを取得
	bool GetisSwipe(){ return m_isswipe; }

private:
	const int ADD_SCORE;
	const int DIFF_SCORE;
	const std::chrono::seconds ADD_TIME;
	const std::chrono::seconds DIFF_TIME;
	bool m_istap;
	bool m_isswipe;
	bool isRemove;
	std::chrono::seconds& m_time;
	std::unique_ptr<Font>m_score_graph;
	Vec2f m_score_pos;

	//　当たった時の処理
	void isHit(Vec2f& pos);

	//　タップしたときの処理
	void UpdateOfTap();

	//　スワイプしたときの処理
	void UpdateOfSwaipe();

	//　タップしたときのスコア表示
	void DrawOfTapScore();

	//　スコア更新
	void UpdateOfScore();

	//　芋の描画
	void DrawSWeetPotato();

	//　削除
	void Remove();

	//　スワイプしたときのスコア表示
	void DrawOfSwipeScore();

	//　スコアの表示
	void DrawOfScore();

	//　神様のの描画
	void HolyGhostDraw();
};

