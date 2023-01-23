#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();


	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;
	virtual void draw();

private:
	void UpdateMove();
private:
	//�L�����N�^�[�̈ʒu
	Vec2 m_pos;
	Vec2 m_underPos;
	//����
	Vec2 m_vec;

	//update���������o�֐��|�C���^
	void (SceneMain::* m_func)();
};
