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

public:

	//�摜
	void SetHandle(int handle) { m_hPlayer = handle; }

private:

	//����
	void Operation();
	//�n�ʔ���
	int FieldJudgement();
	//��q����
	int CheckHit();

private:

	void UpdateMove();

	void MenuStop();

private:

	//�O���t�B�b�N�n���h��
	int m_hPlayer;
	//�d��
	float m_gravity;
	//�K�i����
	bool m_isFloorOne;
	//��q����
	bool m_isLadder;
	//�v���C���[�O���t�B�b�N�T�C�Y
	Vec2 m_playerSize;
	//�L�����N�^�[�̈ʒu
	Vec2 m_pos;
	Vec2 m_underPos;
	//����
	Vec2 m_vec;
	
	void (Player::* m_func)();
};

