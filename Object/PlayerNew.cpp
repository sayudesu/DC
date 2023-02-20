#include "SceneMain2.h"
#include "PlayerNew.h"
#include <DxLib.h>
#include "Pad.h"
#include "game.h"
#include "image.h"

//�萔
namespace
{
	constexpr int kmapSize = 250;

	constexpr double kPlayerSize = 1.4;
	//�v���C���[�̏������W
	constexpr float kPosX = 0.0f;
	constexpr float kPosY = static_cast<float>(Game::kScreenHeight) - 50.0f - 300.0f;//�f�o�b�N�p��-300�ړ�
	//��������
	constexpr float kMoveSpeed = 5.0f; //�����Ɖ������ق����ʔ����I�C���҂�
	// �W�����v��
	constexpr float kJump = -10.0f;
	// �d��
	constexpr float kGravity = 1.0f;

	//�n�ʂ̍���Y��
	constexpr int kGround = 700;

	constexpr int kCharaImageLeftPos = -112; //���ړ�
	constexpr int kCharaImageRightPos = 112; //�E�ړ�

	//�A�j���[�V�����t���[����
	constexpr int kAnimationFrame = 3;

}
//�R���X�g���N�^
PlayerNew::PlayerNew() :
	m_hPlayer(-1),
	m_hPlayerIdle(-1),
	m_hPlayerLighting(-1),
	m_hHealthBer(-1),
	m_hMapFirst(-1),
	m_hMapSecond(-1),
	m_hMapThird(-1),
	m_hMapFourth(-1),
	m_hMapFifth(-1),
	m_hMapChip(-1),
	m_hMapChipSecond(-1),
	m_hFxJump(-1),
	m_padInput(0),
	m_playerLeft(0),
	m_playerTop(0),
	m_playerRight(0),
	m_playerBottom(0),
	m_attackPlayerLeft(0),
	m_attackPlayerTop(0),
	m_attackPlayerRight(0),
	m_attackPlayerBottom(0),
	m_charaImagePos(0),
	m_charaImageIdlePos(0),
	m_charaImageAttackPos(0),
	m_charaImageDamagePos(0),
	m_charaImageJumpPos(0),
	m_charaImageCrouching(0),
	m_count(0),
	m_boxPosX(0),
	m_boxPosY(0),
	m_boxPosBottomX(0),
	m_boxPosBottomY(0),
	m_stagingBoxX(0),
	m_stagingBoxY(0),
	m_stagingBoxBottomX(0),
	m_stagingBoxBottomY(0),
	m_playerHealthBer(0),
	m_playerHealthBerCount(0),
	m_playerHealthSizeX(0),
	m_playerHealthSizeY(0),
	m_boxDropCount(0),
	m_frameCount(0),
	m_hierarchy(0),
	m_tip(0),
	m_gravity(0.0f),
	m_isRunMoveLeft(false),
	m_isRunMoveRight(false),
	m_isIdleMove(false),
	m_isAttackMove(false),
	m_isDamageMove(false),
	m_isJumpMove(false),
	m_isCrouchingMove(false),
	m_isHealthBer(false),
	m_isDead(false),
	m_isReset(false),
	m_isTitle(false),
	m_isGetSword(false),
	m_isAttack(false),
	m_isEnemyDead(false),
	m_isStopMove(false),
	m_isItemDrop(false),
	m_isFloorOne(false),
	m_isLadder(false),
	m_isInvaliDown(false),
	m_isCharaDirection(false),
	m_isCharaIdleDirection(false),
	m_isStageClear(false),
	m_isStageClearChangeScene(false),
	m_isMenu(false),
	m_isItemTip(false),
	m_isItemDropTip(false),
	m_isUpTip(false),
	m_isGravity(false),
	m_isFall(false),
	m_playerSize(0.0f, 0.0f),
	m_pos(0.0f, 0.0f),
	m_imagePos(0.0f, 0.0f),
	m_imageBalancePos(0.0f, 0.0f),
	m_underPos(0.0f, 0.0f),
	m_attackPos(0.0f, 0.0f),
	m_attackBottomPos(0.0f, 0.0f),
	m_vec(0.0f, 0.0f),
	m_isDamage(false),
	m_isDamageFallen(false),
	m_getPos(0.0f),
	m_isAttackHit(false),
	m_isDamageCharge(false),
	m_isRushBlink(false)

{
	m_charaImagePos = (1344 - kCharaImageRightPos);
	m_func = &PlayerNew::UpdateMove;

	DeleteSoundMem(m_hFxJump);

}
//�f�X�g���N�^
PlayerNew::~PlayerNew()
{

}
//������
void PlayerNew::Init()
{
	/*
	m_hierarchy = 1;
	m_playerHealthBer = 100;

	m_boxDropCount = 120;

	m_boxPosX = kBoxPosX;
	m_boxPosY = kBoxPosY;
	m_boxPosBottomX = m_boxPosX + kBoxPosBottomX;
	m_boxPosBottomY = m_boxPosY + kBoxPosBottomY;

	m_pos.x = kPosX;
	m_pos.y = kPosY;

	m_underPos.x = m_pos.x + 50;
	m_underPos.y = m_pos.y + 100;

	m_gravity = kGravity;
	
	m_isEnemyDead = true;
	m_isStopMove = true;
	m_isItemTip = true;
	m_isItemDropTip = true;
	m_isUpTip = true;

	GetGraphSizeF(m_hPlayer, &m_playerSize.x, &m_playerSize.y);
	*/
	// �Đ��`�����t�@�C������X�g���[���Đ�����A�ɐݒ�
//SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
	//m_hFxJump = LoadSoundMem(FX::kJump);
	// ���ʂ̐ݒ�
	//ChangeVolumeSoundMem(255, m_hFxJump);
}
//�������̊J��
void PlayerNew::End()
{

}
//�A�b�v�f�[�g����
void PlayerNew::Update()
{
	if (m_isStageClear)//�X�e�[�W�N���A���ǂ���
	{
		m_isStageClearChangeScene = true;
	}
	Draw();
	(this->*m_func)();
}
//�`��
void PlayerNew::Draw()
{
	DrawBox(m_playerLeft, m_playerTop, m_playerRight, m_playerBottom, 0xff0000, true);

	if (m_isAttack)
	{
		DrawBox(m_attackPlayerLeft, m_attackPlayerTop, m_attackPlayerRight, m_attackPlayerBottom, 0xffffff, true);
		//DrawBox(GetAttackPlayerLeft(), GeAttacktPlayerTop(), GetAttackPlayerRight(), GetAttackPlayerBottom(), 0xffffff, false);
	}
	m_isAttack = false;
}
//�v���C���[�̍s���͈�
void PlayerNew::PlayerPosSet()
{
	if (m_pos.x < 0.0f) m_pos.x = 1.0f;
	if (m_pos.x > Game::kScreenWidth ) m_pos.x = static_cast<float>(Game::kScreenWidth) - 1.0f;
	if (m_pos.y < 0.0f) m_pos.y = 1.0f;
	if (m_pos.y > Game::kScreenHeight) m_pos.y = static_cast<float>(Game::kScreenHeight) - 1.0f;
}
//����S��
void PlayerNew::Operation()
{
	OperationStandard();//��{����
	OperationAttack();//�U������
	OperationJump();//�W�����v����
	OperationLadder();//��q�ł̑���
}
//��{����
void PlayerNew::OperationStandard()
{
	//�ړ�
	if (CheckHitKey(KEY_INPUT_RIGHT)|| (m_padInput & PAD_INPUT_RIGHT))//�E
	{
		m_pos.x += kMoveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) || (m_padInput & PAD_INPUT_LEFT))//��
	{
		m_pos.x -= kMoveSpeed;
	}
}
//�U������
void PlayerNew::OperationAttack()
{
	//m_isAttack = false;//�U����~
	if (Pad::isTrigger(PAD_INPUT_1))//�U��
	{
		printfDx("�U��\n");
		//�v���C���[�̍U����

		m_isAttack = true;//�U���J�n
	}
}
//�W�����v����
void PlayerNew::OperationJump()
{
	//�n�ʂɂ���ꍇ&&��q�ɂ��Ȃ��ꍇ
	//�W�����v
	if (Pad::isTrigger(PAD_INPUT_2))//��
	{
		//PlaySoundMem(m_hFxJump, DX_PLAYTYPE_BACK);
		m_vec.y = 0.0f;
		printfDx("�W�����v\n");
		m_vec.y = kJump;//�W�����v�J�n
	}
}
//��q����
void PlayerNew::OperationLadder()
{
	if (CheckHitKey(KEY_INPUT_UP) || (m_padInput & PAD_INPUT_UP))
	{
		m_pos.y -= kMoveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) || (m_padInput & PAD_INPUT_DOWN))
	{
		m_pos.y += kMoveSpeed;
	}
}
//�A�b�v�f�[�g����
void PlayerNew::UpdateMove()
{

	//PlaySoundMem(m_hFxJump, DX_PLAYTYPE_BACK);

	Pad::update();//���͔���
	m_padInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);//�W���C�p�b�h�̓��͏�Ԃ𓾂�
	OperationStandard();//����::�ړ�
	
	PlayerPosSet();//�ړ��\�͈�

	OperationAttack();//�U��

	if (!m_isFall)//�n�ʂɓ������Ă��Ȃ�������
	{
		//�d��
		m_vec.y += kGravity;
	}
	if (m_isLadder)//��q�ɂ���ꍇ
	{
		OperationLadder();//����::��q�ړ�
		m_vec.y = 0.0f;
		m_vec.x = 0.0f;

	}
	else if (m_isFall)//�n�ʂɓ������Ă�����
	{
		m_vec.y = 0.0f;
		OperationJump();//����::�W�����v
		m_pos.y = m_getPos;//�v���C���[�̈ʒu���W

	}
	
	if (m_isStageClear)//�X�e�[�W�N���A���ǂ���
	{
		m_isStageClearChangeScene = true;
		DrawBox(Stage2::kGoalX, Stage2::kGoalY, Stage2::kGoalBottomX, Stage2::kGoalBottomY, GetColor(GetRand(255), GetRand(255), GetRand(255)), true);
	}

	if (m_isDamage||m_isDamageFallen||m_isDamageCharge)//�U���������������ǂ���
	{
		if (m_isDamage)
		{
			printfDx("Player���S\n");
		}
		if (m_isDamageFallen)
		{
			printfDx("PlayerFallen���S\n");
		}
		if (m_isDamageCharge && m_isRushBlink)//�����Ă���Ԃɓ�����Ǝ���
		{
			printfDx("PlayerChage���S\n");
		}
		//printfDx("���S\n");
		//m_func = &PlayerNew::UpdateDead;//���S�V�[���؂�ւ�
	}
	if (m_isAttackHit)//�U���������������ǂ���
	{
		printfDx("Enemy���S\n");
	}

	m_pos += m_vec;//�v���C���[�ʒu

	//�v���C���[�̍��W
	m_playerLeft = static_cast<int>(m_pos.x) + 10;
	m_playerTop = static_cast<int>(m_pos.y) + 10;
	m_playerRight = m_playerLeft + 40;
	m_playerBottom = m_playerTop + 40;

	if(m_isAttack)//�v���C���[���U���������͈̔�
	{
		m_attackPlayerLeft = m_playerLeft - 10;
		m_attackPlayerTop = m_playerTop - 10;
		m_attackPlayerRight = m_playerRight + 10;
		m_attackPlayerBottom = m_playerBottom + 10;
	}
	else
	{
		m_attackPlayerLeft   = - 10;
		m_attackPlayerTop    = - 10;
		m_attackPlayerRight  = + 10;
		m_attackPlayerBottom = + 10;
	}

}

void PlayerNew::UpdateDead()
{
	printfDx("���S���܂����B\n");
}
