#include "Collision.hpp"

namespace Collision{

	//　円と点の当たり判定
	bool CircleAndPoint(Vec2f& circle_pos, float radius, Vec2f& point_pos){
		float vec_x = circle_pos.x() - point_pos.x();
		float vec_y = circle_pos.y() - point_pos.y();
		if (vec_x * vec_x + vec_y * vec_y <= radius * radius){
			return true;
		}
		else{
			return false;
		}
	}

	//　円と円の当たり判定
	bool CircleAndCircle(Vec2f& a_pos, Vec2f& b_pos, float a_radius, float b_radius){
		float vecx = (a_pos.x() - b_pos.x());
		float vecy = (a_pos.y() - b_pos.y());
		float r = (a_radius + b_radius);
		if (vecx*vecx + vecy*vecy < r*r){
			return true;
		}
		else{
			return false;
		}
	}

	//　四角と四角の当たり判定
	bool PlaneAndPlane(Vec2f& a_pos, Vec2f& a_size, Vec2f& b_pos, Vec2f& b_size)
	{
		float x0 = a_pos.x();
		float y0 = a_pos.y();
		float x1 = a_pos.x() + a_size.x();
		float y1 = a_pos.y() + a_size.y();


		float x2 = b_pos.x();
		float y2 = b_pos.y();
		float x3 = b_pos.x() + b_size.x();
		float y3 = b_pos.y() + b_size.y();


		//	二つの矩形が何かしらの形で重なっているか？ 
		if (x0 < x3 && x2 < x1 && y0 < y3 && y2 < y1)
		{
			//	重なっていた 
			return true;
		}


		//	重なってなかった 
		return false;

	}

}