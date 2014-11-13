//
// アプリ雛形
// ※ファイル分割対応版
//

#include "lib/defines.hpp"
// ↑これは必ず最初にincludeする

#include "lib/random.hpp"

#include "lib/appEnv.hpp"
// ↑必要なヘッダファイルは適時インクルードする


struct Object{
	int hp;
	Vec2f pos;
	Vec2f size;

};

const int ENEMY_NUM = 10;

int pos_x, pos_y;
int touch;
int count=0;
int press_count = 0;
int push_count = 0;
int flag = 0;
int move_flag = 1;

Object enemy[ENEMY_NUM];

//int hit(Vec2f pos, Vec2f size,Vec2f box_pos,AppEnv  &app_env ){
//	//touchはPushとPressのフラグ用変数
//
//	/*pos_x = mouse_pos.x();
//	pos_y = mouse_pos.y();*/
//
//	if (pos.x() > box_pos.x()){
//		if (pos.x() < box_pos.x()+size.x()){
//			if (pos.y()>box_pos.y()){
//				if (pos.y() < box_pos.x()+size.y()){
//
//					if (app_env.isPushButton(Mouse::LEFT)){
//						return 1;
//					}
//					else if (app_env.isPressButton(Mouse::LEFT)){
//						return 2;
//					}
//				}
//			}
//		}
//	}
//	return 0;
//}

enum Window {
	WIDTH = 1320,
	HEIGHT = 720
};


int hit(Vec2f& point_pos,Vec2f& box_pos,Vec2f& box_size,AppEnv& app_env){
	if (box_pos.x() < point_pos.x() && point_pos.x() < box_pos.x() + box_size.x()){
		if (box_pos.y() < point_pos.y() && point_pos.y() < box_pos.y() + box_size.y()){
			if (app_env.isPushButton(Mouse::LEFT)){
				return 1;
			}
			else if (app_env.isPressButton(Mouse::LEFT)){
				return 2;
			}
		}
	}
	return 0;
}




void Draw(Vec2f box_pos, Vec2f size, int start_tx, int start_ty, Texture& texture){
	drawTextureBox(box_pos.x(), box_pos.y(), size.x(), size.y(), start_tx, start_ty, size.y(), size.y(), texture, Color(1, 1, 1));
	//drawBox(box_pos.x(), box_pos.y(), size.x(), size.y(),5,Color(1, 1, 1));
}

//void test(int a,Random& random){
//	if (a == 1){
//		enemy[0].pos.x() = random.fromFirstToLast(-WIDTH / 2, WIDTH / 2);
//		enemy[0].pos.y() = random.fromFirstToLast(-HEIGHT / 2, HEIGHT / 2);
//	}
//	if (a == 2){
//		for (int i = 0; i < ENEMY_NUM; i++){
//			enemy[0].pos.x() += random.fromFirstToLast(-1, 1);
//			enemy[0].pos.y() += random.fromFirstToLast(-1, 1);
//		}
//	}
//}

void Init(){
	for (int i = 0; i < ENEMY_NUM; i++){
		enemy[i].hp = 1;
		enemy[i].pos = Vec2f (0,0);
		enemy[i].size = Vec2f(128,128);
	}

	/*for (auto &Enemy:enemy){
		Enemy.hp = 1;
		Enemy.pos = Vec2f(0, 0);
		Enemy.size = Vec2f(50, 50);
	}*/
}


// アプリのウインドウサイズ




// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
                 false, false);

  Texture mushi_graph("res/064742.png");
  Texture mushi_blood("res/nc.png");
  Init();

  Random random;
  random.setSeed(count);
  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;

	count += 1;

	Vec2f mouse_pos = app_env.mousePosition();
			
	if (flag == 0&&count % 200==0)move_flag *= -1;
	if(flag == 0&&move_flag==1)enemy[0].pos.x() += 0.5;
	if (flag == 0 &&move_flag == -1)enemy[0].pos.x() -= 0.5;
	if (enemy[0].pos.x() <= -WIDTH / 2)move_flag = 1;
	if (enemy[0].pos.x() >= WIDTH / 2 + 128)move_flag = -1;
	
	
    // 描画準備
    app_env.setupDraw();

    //
    // 描画処理はここでおこなう
    // 
	if (hit(mouse_pos, enemy[0].pos, enemy[0].size, app_env) == 1){
		flag = 1;
	}
		if (flag == 1){
			push_count += 1;			
				Draw(enemy[0].pos, enemy[0].size, 0, 0, mushi_blood);
				if (push_count == 40){
					enemy[0].pos.x() = random.fromFirstToLast(-WIDTH / 2, WIDTH / 2 - 128);
					enemy[0].pos.y() = random.fromFirstToLast(-HEIGHT / 2, HEIGHT / 2 - 128);
					push_count = 0;
					flag = 0;
				}
			}
		
	
	

	if (flag==0&&hit(mouse_pos, enemy[0].pos, enemy[0].size, app_env) == 2){
		flag = 2;
	}
	if (flag==2){
		press_count += 1;
			if (press_count % 3 == 0){
				enemy[0].pos.x() += random.fromFirstToLast(-5, 5);
				enemy[0].pos.y() += random.fromFirstToLast(-5, 5);
			}
			if (press_count==60){
				enemy[0].pos.x() = random.fromFirstToLast(-WIDTH / 2, WIDTH / 2 - 128);
				enemy[0].pos.y() = random.fromFirstToLast(-HEIGHT / 2, HEIGHT / 2 - 128);
				press_count = 0;
				flag = 0;
			}
		}
		
	
	  if(flag==0||flag==2)Draw(enemy[0].pos, enemy[0].size, 0, 0, mushi_graph);
		
	//drawBox(0, 0, 50, 50, 5, color256(touch, touch, touch));
    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
