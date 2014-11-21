#pragma once
#include "../../lib/vector.hpp"

//=======================================
//計算式
//=======================================
namespace Math{
	template<typename T>
	//　角度を取得
	T GetAngle(const Vec2f &vec_a, const Vec2f &vec_b, const Vec2f &origin, bool is_degree = false);

	//　距離を取得
	double GetDistance(const Vec2f &vec);
	
	//　内積を取得
	double GetScalarProduct(const Vec2f &vec_a, const Vec2f &vec_b);
	
	//　2点間の距離を取得
	double Get2Distance(const Vec2f &vec_a, const Vec2f &vec_b);
	
	//　2点間の距離を取得(float)
	float Get2Distancef(const Vec2f &vec_a, const Vec2f &vec_b);
	
	//　2点間の差(vec_a - vec_b)
	Vec2f GetDiff(const Vec2f &vec_a, const Vec2f &vec_b);
};

