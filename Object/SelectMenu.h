#pragma once

class TitleCursor;

class SelectMenu
{
public:
	SelectMenu();
	virtual~SelectMenu();

	void Init();
	void Update();
	void Draw();

	bool m_isMenu;//���j���[���J���Ă��邩�ǂ���

private:
	int m_frameCount;//���j���[��ʂ��J�������Ƀf�B���C������
	TitleCursor* m_pCursor;
};

