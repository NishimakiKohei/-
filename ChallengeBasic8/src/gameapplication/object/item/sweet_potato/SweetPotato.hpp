#pragma once
#include "../Implant.hpp"
#include "../../../utility/Font.hpp"
class CSweetPotato : public CImplant{
public:
	CSweetPotato(std::shared_ptr<AppEnv>app_env, std::shared_ptr<Object> object);

	//　最初の処理
	void Start();
	//　更新
	void Update();

	//　描画
	void Draw();

private:
	const int ADD_TAP_SCORE;
	const int ADD_SWIPE_SCORE;
	std::unique_ptr<Font>m_score_graph;
	Vec2f m_score_pos;
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

};

