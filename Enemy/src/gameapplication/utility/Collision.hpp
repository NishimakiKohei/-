#pragma once
#include "../../lib/vector.hpp"

//=======================================
//当たり判定
//=======================================

namespace Collision{
	//　円と点の当たり判定
	bool CircleAndPoint(Vec2f& circle_pos, float radius, Vec2f& point_pos);

	//　円と円の当たり判定
	bool CircleAndCircle(Vec2f& a_pos, Vec2f& b_pos, float a_radius, float b_radius);

	//　四角と四角の当たり判定
	bool PlaneAndPlane(Vec2f& a_pos, Vec2f& a_size, Vec2f& b_pos, Vec2f& b_size);
};