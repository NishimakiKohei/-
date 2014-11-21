#pragma once
#include "../Character.hpp"
#include "../../../resource/Resource.hpp"
#include "../../../utility/Font.hpp"

class CEnemy : public CCharacter{
public:
	CEnemy(std::shared_ptr<AppEnv>app_env, std::vector<std::shared_ptr<Object>>obj_list);

	//�@�X�V
	void Update();

	//�@�`��
	void Draw();

	bool GetisSwipe(){ return m_isswipe; }

private:
	int touch;
	int count;
	int press_count;
	int push_count;
	int flag;
	int move_flag;
	bool m_isswipe;
	bool m_istap;
	bool isRemove;
	const int ADD_SCORE;
	const int DIFF_SCORE;
	std::unique_ptr<Font>m_score_graph;
	Vec2f m_score_pos;

	std::vector<std::shared_ptr<Object>>m_obj_list;
	CResource& m_res;
	int hit(Vec2f& point_pos);

	//�@�X�R�A�̕\��
	void DrawOfScore();

	//�@�^�b�v�����Ƃ��̃X�R�A�\��
	void DrawOfTapScore();

	//�@�X���C�v�����Ƃ��̃X�R�A�\��
	void DrawOfSwipeScore();

	void UpdateOfScore();

	void Remove();
};

