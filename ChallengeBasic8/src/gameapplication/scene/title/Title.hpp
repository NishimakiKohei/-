#pragma once
#include "../SceneManager.hpp"
#include "../../resource/Resource.hpp"
#include <memory>
#include <vector>
#include <array>
#include <unordered_map>
#include <functional>

//========================================
//タイトルクラス
//========================================
class CTitle : public CScene{
public:
	CTitle(std::shared_ptr<AppEnv>app_env);

	//　更新
	Type Update();

	//　描画
	void Draw();

private:

	//　文字データ
	struct StringData{
		StringData(Vec2f &pos, float size, std::unique_ptr<Font> font) :
			pos_(pos),
			size_(size),
			font_(std::move(font)){};
		Vec2f pos_;
		float size_;
		std::unique_ptr<Font> font_;
	};


	//　遷移できるシーン
	enum class Scene{
		STAGE,
		RULE,
		RANKING,
		NUM
	};

	int const STR_SELECT_HEIGHT;											//　選択項目の文字のY座標
	std::array<std::unique_ptr<StringData>, 3>m_title_select_str;			//　選択項目の文字のデータ
	std::unique_ptr<Font>m_title_str;										//　タイトル文字のデータ
	Scene m_now_select;														//　現在選んでいる選択項目
	std::unordered_map<Scene, Type>m_transition_list;		//　遷移できるシーンリスト
	CResource &m_res;														//　リソース
	std::map<Scene, std::function<void()>>m_select_effect_list;					//　選択項目によるエフェクトリスト


	//===============================================================================================================================================
	
	
	//　操作
	void Control();

	//　文字の初期化
	void StringInit();

	//　回転のエフェクト
	void RotationEffect();

	//　遷移リストの追加
	void AddTransitionList();

	//　選んでる項目によるエフェクトリストの追加
	void AddSelectEffectList();

	//　選んでる項目によってフォントを変更
	void FontDrawOfSelectStage();
	void FontDrawOfSelectRule();
	void FontDrawOfSelectRanking();
};

