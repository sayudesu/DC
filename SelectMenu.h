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

	TitleCursor* m_pCursor;
};

