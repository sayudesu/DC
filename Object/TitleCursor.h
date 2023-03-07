#pragma once
#include "Vec2.h"

class SceneTitle;

class TitleCursor
{
public:
	TitleCursor();
	~TitleCursor();
	void Init();
	void Update();
	void Draw();
private:
	void PosSet();
	void DrawPadCursor();
	void DrawSelection();
public:
	void GetMenu(bool menu) { m_isMenu = menu; }//���j���[�̏��
	Vec2 GetCursor() { return m_padPos; }

private:
	bool m_isMenu;//���j���[�����J���Ă��邩�ǂ���
	Vec2 m_padPos;
};

