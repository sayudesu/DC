#pragma once
#include "Vec2.h"

class PlayerNew
{
public:
	PlayerNew();
	virtual ~PlayerNew();

	virtual void Init();
	virtual void End();

	virtual void Update();
	virtual void Draw();

public:

	void SetHandle         (int handle) { m_hPlayer         = handle; }
	void SetHandleIdle     (int handle) { m_hPlayerIdle     = handle; }
	void SetHandleLighting (int handle) { m_hPlayerLighting = handle; }
	void SetHandleHealthBer(int handle) { m_hHealthBer      = handle; }

	float GetPlayerLeft  () { return static_cast<float>(m_playerLeft  ); }
	float GetPlayerTop   () { return static_cast<float>(m_playerTop   ); }
	float GetPlayerRight () { return static_cast<float>(m_playerRight ); }
	float GetPlayerBottom() { return static_cast<float>(m_playerBottom); }

	//Vec2 GetPos() { return m_pos; }

	//void GetGravity (bool gravity)   { m_isGravity = gravity;   }//�n�ʂɂ��邩�ǂ���
	void GetPos     (float pos)      { m_getPos    = pos;       }//�n�ʂɂ���ꍇ�̍��W.y
	void GetLadder  (bool ladderHit) { m_isLadder  = ladderHit; }//��q�ɓ������Ă��邩�ǂ���
	void GetScaffold(bool fall)      { m_isFall    = fall;      }//�n�ʂɂ��邩�ǂ���

private:
	//����
	void Operation();
private:

	//�X�V���
	void UpdateMove();

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
	int m_hMapFifth;
	int m_hMapChip;
	int m_hMapChipSecond;
	//�v���C���[����p
	int m_playerLeft;
	int m_playerTop;
	int m_playerRight;
	int m_playerBottom;
	//�L�����N�^�[�摜�ʒu
	int m_charaImagePos;
	int m_charaImageIdlePos;
	int m_charaImageAttackPos;
	int m_charaImageDamagePos;
	int m_charaImageJumpPos;
	int m_charaImageCrouching;
	//�͂���
	int m_count;
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
	//�����p
	int m_tip;
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
	//���񂾏ꍇ
	bool m_isReset;
	bool m_isTitle;
	//�A�C�e������
	bool m_isGetSword;
	bool m_isItemDrop;
	//�U������
	bool m_isAttack;
	bool m_isEnemyDead;
	//�X�g�b�v
	bool m_isStopMove;
	//�K�i����
	bool m_isFloorOne;
	//��q����
	bool m_isLadder;
	//���Ɉړ��ł��Ȃ�
	bool m_isInvaliDown;
	//�L�����N�^�[�̌���
	bool m_isCharaDirection;
	bool m_isCharaIdleDirection;
	//�X�e�[�W�N���A����
	bool m_isStageClear;
	bool m_isMenu;
	//�Q�[���q���g
	bool m_isItemTip;
	bool m_isItemDropTip;
	bool m_isUpTip;

	bool m_isGravity;
	bool m_isFall;
	//�v���C���[�O���t�B�b�N�T�C�Y
	Vec2 m_playerSize;
	//�L�����N�^�[�̈ʒu
	Vec2 m_pos;
	//�摜�p�L�����N�^�[�ʒu����
	Vec2 m_imagePos;
	Vec2 m_imageBalancePos;
	Vec2 m_underPos;
	//�v���C���[�U���͈�
	Vec2 m_attackPos;
	Vec2 m_attackBottomPos;
	//����
	Vec2 m_vec;

	float m_getPos;

	void (PlayerNew::* m_func)();

};
