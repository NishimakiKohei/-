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

Object enemy[ENEMY_NUM];

int hit(Vec2f pos, Vec2f size,Vec2f box_pos,AppEnv  &app_env ){
	//touchはPushとPressのフラグ用変数

	/*pos_x = mouse_pos.x();
	pos_y = mouse_pos.y();*/

	if (pos.x() > box_pos.x()){
		if (pos.x() < size.x()){
			if (pos.y()>box_pos.y()){
				if (pos.y() < size.y()){	

					if (app_env.isPushButton(Mouse::LEFT)){
						return 1;
					}

					if (app_env.isPressButton(Mouse::LEFT)){
						return 2;
					}

				}
			}
		}
	}
}

void Draw(Vec2f box_pos, Vec2f size, int start_tx, int start_ty, Texture &texture){
	drawTextureBox(box_pos.x(), box_pos.y(), size.x(), size.y(), start_tx, start_ty, size.y(), size.y(), texture, Color(1, 1, 1));
}

void Init(){
	for (int i = 0; i < ENEMY_NUM; i++){
		enemy[i].hp = 1;
		enemy[i].pos = Vec2f(0, 0);
		enemy[i].size = Vec2f(50, 50);
	}

	/*for (auto &Enemy:enemy){
		Enemy.hp = 1;
		Enemy.pos = Vec2f(0, 0);
		Enemy.size = Vec2f(50, 50);
	}*/
}


// アプリのウインドウサイズ
enum Window {
  WIDTH  = 1320,
  HEIGHT = 720
};

Texture mushi_graph("res/064742.png");




// 
// メインプログラム
// 
int main() {
  // アプリウインドウの準備
  AppEnv app_env(Window::WIDTH, Window::HEIGHT,
                 false, false);

  Init();

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;

	//Random random;

	Vec2f mouse_pos = app_env.mousePosition();

	touch = 255;

	switch (hit(mouse_pos, enemy[0].size, enemy[0].pos, app_env)){
	case 1:touch = 0;
	case 2:touch = 100;
	}

	

    // 描画準備
    app_env.setupDraw();

	//hit(mouse_pos, enemy[0].size, enemy[0].pos, app_env);

    //
    // 描画処理はここでおこなう
    // 
	//drawTextureBox(0, 0, 50, 50, 0, 0,50,50 ,mushi_graph,Color(1,1,1));

	Draw(enemy[0].pos, enemy[0].size, 0, 0, mushi_graph);

	//drawBox(0, 0, 50, 50, 5, color256(touch, touch, touch));
    
    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
