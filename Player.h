#pragma once
#include "Vec2.h"

class Player
{
public:
	Player();
	virtual ~Player();


	virtual void Init();
	virtual void End();

	virtual void Update();
	virtual void Draw();

	void setHandle(int handle) { m_hPlayer = handle; }

private:

	void UpdateMove();

private:

	//�O���t�B�b�N�n���h��
	int m_hPlayer;
	//�L�����N�^�[�̈ʒu
	Vec2 m_pos;
	Vec2 m_underPos;
	//����
	Vec2 m_vec;

	void (Player::* m_func)();
};

