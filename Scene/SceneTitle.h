#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();
private:
	void DrawPadCursor();
	void DrawSelection();
private:
	//�摜�n���h��
	int m_hImagePlayer;
	int m_hImageMap;
	int m_charaImagePos;
	//�J�E���g
	int m_frameCount;
	int m_sceneChangeCount;

	Vec2 m_padPos;
	Vec2 m_imagePos;
};
