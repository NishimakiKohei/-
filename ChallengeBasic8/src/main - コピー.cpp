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
float touch;

Object enemy[ENEMY_NUM];

void hit(Vec2f &pos, Vec2f &size,Vec2f &enemy,AppEnv  &app_env ){
	//touchはPushとPressのフラグ用変数

	/*pos_x = mouse_pos.x();
	pos_y = mouse_pos.y();*/

	if (pos.x > enemy.x){
		if (pos.x < size.x){
			if (pos.y>enemy.y){
				if (pos.y < size.y){		
					if (app_env.isPushButton(Mouse::LEFT)){
						touch = 0;
					}
					if (app_env.isPressButton(Mouse::LEFT)){
						touch = 0.5;
					}
				}
			}
		}
	}
}

void Draw(int &enemy_x,int &enemy_y,int &size_x,int &size_y,int start_tx,int start_ty,Texture &texture){
	drawTextureBox(enemy_x,enemy_y,size_x,size_y,start_tx,start_ty,size_x,size_y,texture,Color(1,1,1));
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

  while (1) {
    // アプリウインドウが閉じられたらプログラムを終了
    if (!app_env.isOpen()) return 0;

	//Random random;

	Vec2f mouse_pos = app_env.mousePosition();

	touch = 1;

    // 描画準備
    app_env.setupDraw();

	Init();

	hit(mouse_pos, enemy[0].size, enemy[0].pos, app_env);

    //
    // 描画処理はここでおこなう
    // 
	//drawTextureBox(0, 0, 50, 50, 0, 0,50,50 ,mushi_graph,Color(1,1,1));

	//Draw(enemy[0].pos.x, enemy[0].pos.y, enemy[0].size.x, enemy[0].size.y, 0, 0, mushi_graph);

	//drawBox(0, 0, 50, 50, 5, Color(touch, touch, touch));
    
    
    // 画面更新
    app_env.update();
  }
  
  // アプリ終了
}
