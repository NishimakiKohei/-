#pragma once
#include "../Uncopyable.hpp"
#include "../../lib/vector.hpp"
#include <vector>
#include <memory>
#include <list>

//========================================
//オブジェクトクラス(基底クラス)
//========================================

class Object : private Uncopyable{
public:
	Object() = default;
	virtual ~Object() = default;

	//　更新
	virtual void Update() = 0;
	//　描画
	virtual void Draw() = 0;
	
	//　削除するか
	bool isRemove(){
		if (!m_is_active){
			return true;
		}
		else {
			return false;
		}
	}

	//　座標を取得
	Vec2f GetPos(){
		return m_pos;
	}

	//　座標を取得
	Vec2f GetSize(){
		return m_size;
	}

	//　アクティブか取得
	bool GetisActive(){ return m_is_active; }
	
	enum class Type{
		SweetPotato,
		HolyGhost,
		Enemy
	};

	//　タイプの取得
	Type GetType(){ return m_type; }

protected:
	int m_alpha;
	float m_alphaf;

	Vec2f m_pos;
	Vec2f m_size;
	Vec2f m_vec;
	Type m_type;
	//	アクティブな状態か
	bool m_is_active = true;
};

typedef std::vector<std::unique_ptr<Object>> ArrayVec;
typedef std::vector<std::shared_ptr<Object>> ArrayList;