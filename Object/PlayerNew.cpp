#include "SceneMain2.h"
#include "PlayerNew.h"
#include "PlayerAnimation.h"
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
	constexpr float kMoveSpeed = 5.0f;
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
	m_hPlayer(-1),//�摜
	m_hPlayerIdle(-1),//�������Ă��Ȃ����
	m_hPlayerLighting(-1),
	m_hHealthBer(-1),
	m_hAttack(-1),//�T�E���h
	m_hFxJump(-1),
	m_hLadder(-1),
	m_hRun(-1),
	m_hDead(-1),
	m_CountRunSound(-1),
	m_CountLadderSound(-1),
	m_hMapFirst(-1),
	m_hMapSecond(-1),
	m_hMapThird(-1),
	m_hMapFourth(-1),
	m_hMapFifth(-1),
	m_hMapChip(-1),
	m_hMapChipSecond(-1),
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
	m_isLadderNow(false),
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
	m_charaImagePos = 0;
	m_func = &PlayerNew::UpdateMove;
	m_pos.x = kPosX;
	m_pos.y = kPosY;

	m_hFxJump = LoadSoundMem(FX::kJump);//�W�����v�T�E���h�ǂݍ���
	m_hRun    = LoadSoundMem(FX::kRun);//�U���T�E���h�ǂݍ���
	m_hAttack = LoadSoundMem(FX::kAttack);//�U���T�E���h�ǂݍ���
	m_hDead   = LoadSoundMem(FX::kDead);//�U���T�E���h�ǂݍ���
	m_hLadder = LoadSoundMem(FX::kLadder);

}
//�f�X�g���N�^
PlayerNew::~PlayerNew()
{
	//�T�E���h�������J��
	DeleteSoundMem(m_hFxJump);
	DeleteSoundMem(m_hRun);
	DeleteSoundMem(m_hLadder);
	DeleteSoundMem(m_hAttack);
	DeleteSoundMem(m_hDead);
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
	//Draw();
	(this->*m_func)();
}
//�`��
void PlayerNew::Draw()
{
	DrawBox(m_playerLeft, m_playerTop, m_playerRight, m_playerBottom, 0xaaaaaa, true);

	//�A�C�h�����
	//int a = LoadGraph(Image::kPlayerImageIdle);
	//int b = LoadGraph(Image::kPlayerImage);
	////DrawRectRotaGraph(m_playerLeft + 35, m_playerTop + 10, m_charaImageIdlePos, 0, 80, 80,1.5, 0, a, true, false);
	//DrawRectRotaGraph(m_playerLeft + 15, m_playerTop - 5, m_charaImagePos, 133, 112, 133, 1.5, 0, b, true, true);
	//DrawFormatString(100, 100, 0xffffff, "%d", m_charaImagePos);
	//��112
	//�c133
	// 
	//DrawGraph(m_playerLeft, m_playerTop, a, true);



	if (m_isAttack)
	{
		DrawBox(m_attackPlayerLeft, m_attackPlayerTop, m_attackPlayerRight, m_attackPlayerBottom, 0xffffff, true);
	}

	m_isAttack = false;
}
void PlayerNew::Animation()
{
	m_boxDropCount++;

	//if (m_boxDropCount >= 3)//�摜�����炷
	//{
	//	m_charaImageIdlePos += 80;
	//	m_boxDropCount = 0;
	//}

	//if (m_charaImageIdlePos >= 1440)//�摜���E�܂ŕ\�����ꂽ�獶�ɖ߂�
	//{
	//	m_charaImageIdlePos = 0;
	//}

	if (m_boxDropCount >= 3)//�摜�����炷
	{
		m_charaImagePos += 112;
		m_boxDropCount = 0;
	}

	if (m_charaImagePos >= 1344)//�摜���E�܂ŕ\�����ꂽ�獶�ɖ߂�
	{
		m_charaImagePos = 0;
	}

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
		
		m_CountRunSound++;
		if (m_CountRunSound >= 13)//13�t���[���Ɉ�x�����������Đ�
		{
			PlaySoundMem(m_hRun, DX_PLAYTYPE_BACK);
			m_CountRunSound = 0;
		}
		m_pos.x += kMoveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) || (m_padInput & PAD_INPUT_LEFT))//��
	{
		m_CountRunSound++;
		if (m_CountRunSound >= 13)//13�t���[���Ɉ�x�����������Đ�
		{
			PlaySoundMem(m_hRun, DX_PLAYTYPE_BACK);
			m_CountRunSound = 0;
		}
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
		PlaySoundMem(m_hAttack, DX_PLAYTYPE_BACK);
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
		PlaySoundMem(m_hFxJump, DX_PLAYTYPE_BACK);
		m_vec.y = 0.0f;
		m_vec.y = kJump;//�W�����v�J�n
	}
}
//��q����
void PlayerNew::OperationLadder()
{

	if (CheckHitKey(KEY_INPUT_UP) || (m_padInput & PAD_INPUT_UP))
	{
		m_isLadderNow = true;//�v���C���[����q�ɐG��
		m_CountLadderSound++;
		if (m_CountLadderSound >= 13)
		{
			PlaySoundMem(m_hLadder, DX_PLAYTYPE_BACK);
			m_CountLadderSound = 0;
		}
		m_pos.y -= kMoveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) || (m_padInput & PAD_INPUT_DOWN))
	{
		m_isLadderNow = true;//�v���C���[����q�ɐG��
		m_CountLadderSound++;
		if (m_CountLadderSound >= 13)
		{
			PlaySoundMem(m_hLadder, DX_PLAYTYPE_BACK);
			m_CountLadderSound = 0;
		}
		m_pos.y += kMoveSpeed;
	}
	if (m_isLadderNow)//�v���C���[����q�ɐG���Ă���ꍇ
	{
		m_vec.x = 0.0f;//�x�N�g�������Z�b�g
		m_vec.y = 0.0f;
	}
}
//�A�b�v�f�[�g����
void PlayerNew::UpdateMove()
{
	Animation();//�A�j���[�V����
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
	}
	else if (m_isFall)//�n�ʂɓ������Ă�����
	{
		m_vec.y = 0.0f;
		OperationJump();//����::�W�����v
		m_pos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_isLadderNow = false;//�v���C���[�͒�q�ɐG���Ă��Ȃ����

	}

	//Animation();//�L�����N�^�[�̃A�j���[�V����
	
	if (m_isStageClear)//�X�e�[�W�N���A���ǂ���
	{
		m_isStageClearChangeScene = true;//�N���A
		DrawBox(Stage2::kGoalX, Stage2::kGoalY,Stage2::kGoalBottomX, Stage2::kGoalBottomY, GetColor(GetRand(255), GetRand(255), GetRand(255)), true);
	}

	if (m_isDamage||m_isDamageFallen||m_isDamageCharge)//�U���������������ǂ���
	{
		//PlaySoundMem(m_hDead, DX_PLAYTYPE_NORMAL);//���񂾏ꍇ�̃T�E���h�Đ�

		if(CheckSoundMem(m_hDead) == 0)//���łȂ��Ȃ�����
		{
			if (m_isDamage)//�΂̋ʓG
			{
				printfDx("Player���S\n");
				m_func = &PlayerNew::UpdateDead;//���S�V�[���؂�ւ�
			}
			if (m_isDamageFallen)//�������m�G
			{
				printfDx("PlayerFallen���S\n");
				m_func = &PlayerNew::UpdateDead;//���S�V�[���؂�ւ�
			}
			if (m_isDamageCharge && m_isRushBlink)//�����Ă���Ԃɓ�����Ǝ��ʓG
			{
				printfDx("PlayerChage���S\n");
				m_func = &PlayerNew::UpdateDead;//���S�V�[���؂�ւ�
			}
		}
		//printfDx("���S\n");
	}
	if (m_isAttackHit)//�U���������������ǂ���
	{
		printfDx("Enemy���S\n");
	}

	m_pos += m_vec;//�v���C���[�ʒu

	//�v���C���[�̍��W
	m_playerLeft = static_cast<int>(m_pos.x);
	m_playerTop = static_cast<int>(m_pos.y);
	m_playerRight = m_playerLeft + 40;
	m_playerBottom = m_playerTop + 40;

	if(m_isAttack)//�v���C���[���U���������͈̔�
	{
		m_attackPlayerLeft = m_playerLeft - 10;
		m_attackPlayerTop = m_playerTop - 10;
		m_attackPlayerRight = m_playerRight + 10;
		m_attackPlayerBottom = m_playerBottom + 10;
	}
	else//�U�����Ă��Ȃ��ꍇ�͈̔�
	{
		m_attackPlayerLeft   = - 10;
		m_attackPlayerTop    = - 10;
		m_attackPlayerRight  = + 10;
		m_attackPlayerBottom = + 10;
	}

}

void PlayerNew::UpdateDead()
{
	m_isDead = true;//���S
}
