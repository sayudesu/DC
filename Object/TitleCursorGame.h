#pragma once
#include "TitleCursor.h"
class TitleCursorGame : TitleCursor
{
public:
	TitleCursorGame();
	~TitleCursorGame();
	void Init();
	void Update();
	void Draw();
private:
	void PosSet();
	void DrawPadCursor();
	void DrawSelection();
public:
	Vec2 GetCursor() { return m_padPos; }

private:

	int m_mouseX, m_mouseY;

	Vec2 m_padPos;
};

