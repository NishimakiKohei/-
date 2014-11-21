#include "Font.hpp"

Font::Font(unsigned int font_size, std::wstring font_name)
{

	m_font = m_font_list.GetFontPath(font_name);
	m_font->FaceSize(font_size);
}

//@•`‰æ
void Font::Draw(int pos_x, int pos_y,Color &color){
	if (!m_font)return;
	color.setToGl();
	glRasterPos2f(pos_x, pos_y);
	m_font->Render(m_str.c_str());
}

void Font::Draw(std::wstring str, int pos_x, int pos_y, Color &color){
	if (!m_font)return;
	color.setToGl();
	glRasterPos2f(pos_x, pos_y);
	m_font->Render(str.c_str());
}

void Font::Draw(std::string str, int pos_x, int pos_y, Color &color){
	if (!m_font)return;
	color.setToGl();
	glRasterPos2f(pos_x, pos_y);
	m_font->Render(str.c_str());
}

//@İ’è‚µ‚½’†‰›‚É•`‰æ
void Font::DrawCenter(int pos_x, int pos_y, Color &color,int div){
	if (!m_font)return;
	color.setToGl();
	glRasterPos2f(pos_x - (m_font->LineHeight()*m_str.size() / div), pos_y - m_font->LineHeight() / div);
	m_font->Render(m_str.c_str());
}

//@İ’è‚µ‚½’†‰›‚É•`‰æ
void Font::DrawCenter(std::wstring str, int pos_x, int pos_y, Color &color, int div){
	if (!m_font)return;
	color.setToGl();
	glRasterPos2f(pos_x - (m_font->LineHeight()*str.size() / div), pos_y - m_font->LineHeight() / div);
	m_font->Render(str.c_str());
}

//@İ’è‚µ‚½’†‰›‚É•`‰æ
void Font::DrawCenter(std::string str, int pos_x, int pos_y, Color &color, int div){
	if (!m_font)return;
	color.setToGl();
	glRasterPos2f(pos_x - (m_font->LineHeight()*str.size() / div), pos_y - m_font->LineHeight() / div);
	m_font->Render(str.c_str());
}