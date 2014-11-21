#pragma once
#pragma comment (lib, "freetype253MT.lib")
#pragma comment (lib, "ftgl.lib")

#include <FTGL/ftgl.h>
#include "../Uncopyable.hpp"
#include <map>
#include <string>
#include <memory>

class FontList : private Uncopyable{
public:
	FontList();

	//　フォントのパスを取得
	std::shared_ptr<FTPixmapFont> GetFontPath(std::wstring &font_name){
		auto it = m_font_list.find(font_name);
		if (it != m_font_list.end()){
			return it->second;
		}
		else{
			return std::make_shared<FTPixmapFont>("res/font/msgothic.ttc");
		}
	}

private:
	std::map <std::wstring, std::shared_ptr<FTPixmapFont> >m_font_list;
};

