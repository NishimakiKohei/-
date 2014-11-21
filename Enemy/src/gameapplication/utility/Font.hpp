#pragma once
#include "FontList.hpp"
#include "../../lib/graph.hpp"
#include <string>
#include <memory>

class Font{
public:
	Font(unsigned int font_size, std::wstring font_name = L"MS　ゴシック");

	//　描画
	void Draw(int pos_x, int pos_y, Color &color);

	void Draw(std::wstring str, int pos_x, int pos_y, Color &color);

	void Draw(std::string str, int pos_x, int pos_y, Color &color);

	//　設定した中央に表示
	void DrawCenter(int pos_x, int pos_y, Color &color, int div = 2);

	void DrawCenter(std::wstring str, int pos_x, int pos_y, Color &color,int div = 2);

	void DrawCenter(std::string str, int pos_x, int pos_y, Color &color, int div = 2);

	//　関数オブジェクト
	Font &operator()(std::wstring str){
		m_str = str;
		m_str.shrink_to_fit();
		return *this;
	}

	//　1文字のサイズを取得
	float GetSize(){ return m_font->LineHeight(); }

	//　フォントのサイズを変換
	void TransformOfSize(unsigned int font_size){ m_font->FaceSize(font_size); }

private:
	FontList m_font_list;
	std::shared_ptr<FTPixmapFont> m_font;
	std::wstring m_str;
};