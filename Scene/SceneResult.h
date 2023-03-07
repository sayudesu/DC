#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class TitleCursorGame;//カーソルクラス
class GameSceneCollision;//カーソル判定

class SceneResult : public SceneBase
{
public:
	SceneResult();

	virtual ~SceneResult() {}

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();
private:
	int m_color1;//選択画面の色
	int m_color2;
	int m_color3;

	TitleCursorGame* m_pCursor;
	GameSceneCollision* m_pCursorCollision;
};

