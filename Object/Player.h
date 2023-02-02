#pragma once
#include "Vec2.h"

class SceneResult;
class Enemy;
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
	void SetHandle         (int handle) { m_hPlayer         = handle; }
	void SetHandleIdle     (int handle) { m_hPlayerIdle     = handle; }
	void SetHandleLighting (int handle) { m_hPlayerLighting = handle; }
	void SetHandleHealthBer(int handle) { m_hHealthBer      = handle; }

	void SetHandleMapFirst (int handle) { m_hMapFirst = handle; }
	void SetHandleMapSecond(int handle) { m_hMapSecond = handle; }
	void SetHandleMapThird (int handle) { m_hMapThird = handle; }
	void SetHandleMapFourth(int handle) { m_hMapFourth = handle; }

	void SetHnadleMapChip(int handle) { m_hMapChip = handle; }

private:

	//����
	void Operation();
	//���
	void Condition();
	//�n�ʔ���
	int FieldJudgement();
	//��q����
	int CheckHit();
	//�A�C�e���{�b�N�X����
	void BoxJudgement();
	//��������
	void CheckFall();
	//�G�Ƃ̓����蔻��
	bool EnemyHit();
	//HP�Ǘ�
	void HealthControl();

private:
	//�X�V���
	void UpdateMove();
	//�|�[�Y���
	void MenuStop();

	//���񂾏ꍇ
	void DeathMenu();

private:

	//�O���t�B�b�N�n���h��
	int m_hPlayer;
	int m_hPlayerIdle;
	int m_hPlayerLighting;
	int m_hHealthBer;
	//�}�b�v�p�O���t�B�b�N�n���h��
	int m_hMapFirst;
	int m_hMapSecond;
	int m_hMapThird;
	int m_hMapFourth;
	int m_hMapChip;
	//�L�����N�^�[�摜�ʒu
	int m_charaImagePos;
	int m_charaImageIdlePos;
	int m_charaImageAttackPos;
	int m_charaImageDamagePos;
	int m_charaImageJumpPos;
	int m_charaImageCrouching;
	//�A�C�e���{�b�N�X�T�C�Y�ʒu
	int m_boxPosX;
	int m_boxPosY;
	int m_boxPosBottomX;
	int m_boxPosBottomY;
	//�A�C�e���{�b�N�X�̉��o
	int m_stagingBoxX;
	int m_stagingBoxY;
	int m_stagingBoxBottomX;
	int m_stagingBoxBottomY;
	//�v���C���[�̗�
	int m_playerHealthBer;
	int m_playerHealthBerCount;
	int m_playerHealthSizeX;
	int m_playerHealthSizeY;
	//�A�C�e���{�b�N�X�h���b�v
	int m_boxDropCount;
	//�t���[���J�E���g
	int m_frameCount;
	//���݉��K�ɂ��邩
	int m_hierarchy;
	//�d��
	float m_gravity;
	//�A�j���[�V����
	bool m_isRunMoveLeft;
	bool m_isRunMoveRight;
	bool m_isIdleMove;
	bool m_isAttackMove;
	bool m_isDamageMove;
	bool m_isJumpMove;
	bool m_isCrouchingMove;
	//HP
	bool m_isHealthBer;
	bool m_isDead;
	//�A�C�e������
	bool m_isGetSword;
	bool m_isItemDrop;
	//�K�i����
	bool m_isFloorOne;
	//��q����
	bool m_isLadder;
	//���Ɉړ��ł��Ȃ�
	bool m_isInvaliDown;
	//�L�����N�^�[�̌���
	bool m_isCharaDirection;
	bool m_isCharaIdleDirection;
	//�v���C���[�O���t�B�b�N�T�C�Y
	Vec2 m_playerSize;
	//�L�����N�^�[�̈ʒu
	Vec2 m_pos;
	//�摜�p�L�����N�^�[�ʒu����
	Vec2 m_imagePos;
	Vec2 m_imageBalancePos;
	Vec2 m_underPos;
	//����
	Vec2 m_vec;
	
	void (Player::* m_func)();
	Enemy* m_pEnemy;
	SceneResult* m_pSceneResult;
};

