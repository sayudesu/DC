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
	//���
	void Condition();
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
	//�L�����N�^�[�摜�ʒu
	int m_charaImagePos;
	//�t���[���J�E���g
	int m_frameCount;
	//���݉��K�ɂ��邩
	int m_hierarchy;
	//�d��
	float m_gravity;
	//�K�i����
	bool m_isFloorOne;
	//��q����
	bool m_isLadder;
	//���Ɉړ��ł��Ȃ�
	bool m_isInvaliDown;
	//�L�����N�^�[�̌���
	bool m_isCharaDirection;
	//�v���C���[�O���t�B�b�N�T�C�Y
	Vec2 m_playerSize;
	//�L�����N�^�[�̈ʒu
	Vec2 m_pos;
	Vec2 m_underPos;
	//����
	Vec2 m_vec;
	
	void (Player::* m_func)();
};

