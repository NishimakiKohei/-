#pragma once
#include "../Object.hpp"
#include "../../resource/Resource.hpp"

class CImplant : public Object{
public:
	CImplant(std::shared_ptr<AppEnv>app_env, std::shared_ptr<Object> object);

	//　当たったときの処理
	void isHit(Vec2f& pos);

	//　スワイプされたかを取得
	bool GetisSwipe(){ return m_isswipe; }

protected:
	Vec2f m_hit_pos;							//　当たり判定用のポジション
	Vec2f m_hit_size;							//　当たり判定用のサイズ
	CResource& m_res;							//　リソースの箱
	bool m_istap;								//　タップされたか
	bool m_isswipe;								//　スワイプされたか
	bool isRemove;								//　削除するか
	std::shared_ptr<AppEnv> m_app_env;			//　アプリイベントの箱
	std::shared_ptr<Object> m_player;			//　プレイヤーを入れる箱
};

