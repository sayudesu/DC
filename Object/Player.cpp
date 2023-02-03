#include "SceneMain.h"
#include "SceneResult.h"
#include "Player.h"
#include "Enemy.h"
#include <DxLib.h>
#include "Pad.h"
#include "game.h"

namespace
{
	//�v���C���[�̏������W
	constexpr float kPosX = 100.0f;//20.0f;
	constexpr float kPosY = 0.0f;//700.0f;
	//��������
	constexpr float kMoveSpeed = 7.0f;
	// �W�����v��
	constexpr float kJump = -15.0f;
	// �d��
	constexpr float kGravity = 1.0f;

	//�n�ʂ̍���Y��
	constexpr int kGround = 700;

	constexpr int kCharaImageLeftPos = -112; //���ړ�
	constexpr int kCharaImageRightPos = 112; //�E�ړ�

	//�A�j���[�V�����t���[����
	constexpr int kAnimationFrame = 3;

	////////////////////
	///*�n�ʁ@�Q���W*///
	////////////////////
	constexpr int kGroundSecondX = Game::kScreenWidth / 2;
	constexpr int kGroundSecondY = 520 - 10;
	constexpr int kGroundSecondBottomX = Game::kScreenWidth - 120;
	constexpr int kGroundSecondBottomY = kGroundSecondY + 20;

	///////////////////////
	///*2�K���痎������*///
	///////////////////////
	constexpr int kFallBoxX = 0;
	constexpr int kFallBoxY = 450;
	constexpr int kFallBoxBottomX = Game::kScreenWidth / 2 - 40;
	constexpr int kFallBoxBottomY = kFallBoxY + 80;

	////////////////////
	///*�͂����P���W*///
	////////////////////
	constexpr int kLadderX = Game::kScreenWidth - 100;
	constexpr int kLadderY = 500;
	constexpr int kLadderXBottom = Game::kScreenWidth - 90;
	constexpr int kLadderYBottom = Game::kScreenHeight - 70;

	////////////////////////
	///*�A�C�e���{�b�N�X*///
	///////////////////////
	constexpr int kBoxPosX = 200;
	constexpr int kBoxPosY = 550;
	constexpr int kBoxPosBottomX = 200 + 50;
	constexpr int kBoxPosBottomY = 550 + 50;

}
Player::Player() :
	m_hPlayer             (-1),
	m_hPlayerIdle         (-1),
	m_hPlayerLighting     (-1),
	m_hHealthBer          (-1),
	m_playerLeft		  (0),
	m_playerTop           (0),
	m_playerRight		  (0),
	m_playerBpttom        (0),
	m_charaImagePos		  (0),
	m_charaImageIdlePos   (0),
	m_charaImageAttackPos (0),
	m_charaImageDamagePos (0),
	m_charaImageJumpPos   (0),
	m_charaImageCrouching (0),
	m_count				  (0),
	m_boxPosX			  (0),
	m_boxPosY             (0),
	m_boxPosBottomX       (0),
	m_boxPosBottomY       (0),
	m_stagingBoxX         (0),
	m_stagingBoxY         (0),
	m_stagingBoxBottomX   (0),
	m_stagingBoxBottomY   (0),
	m_playerHealthBer     (0),
	m_playerHealthBerCount(0),
	m_playerHealthSizeX   (0),
	m_playerHealthSizeY   (0),
	m_boxDropCount        (0),
	m_frameCount          (0),
	m_hierarchy           (0),
	m_gravity(0.0f),
	m_isRunMoveLeft       (false),
	m_isRunMoveRight      (false),
	m_isIdleMove          (false),
	m_isAttackMove		  (false),
	m_isDamageMove		  (false),
	m_isJumpMove		  (false),
	m_isCrouchingMove     (false),
	m_isHealthBer         (false),
	m_isDead			  (false),
	m_isReset			  (false),
	m_isTitle			  (false),
	m_isGetSword          (false),
	m_isItemDrop          (false),
	m_isFloorOne          (false),
	m_isLadder            (false),
	m_isInvaliDown        (false),
	m_isCharaDirection    (false),
	m_isCharaIdleDirection(false),
	m_playerSize     (0.0f, 0.0f),
	m_pos            (0.0f, 0.0f),
	m_imagePos       (0.0f, 0.0f),
	m_imageBalancePos(0.0f, 0.0f),
	m_underPos       (0.0f, 0.0f),
	m_vec            (0.0f, 0.0f),
	m_pEnemy      (nullptr),
	m_pSceneResult(nullptr)
{
	m_charaImagePos = (1344 - kCharaImageRightPos);
	m_func = &Player::UpdateMove;
	m_pEnemy = new Enemy;
}
Player::~Player()
{
	delete m_pEnemy;
	delete m_pSceneResult;
}
//������
void Player::Init()
{

	m_hierarchy = 1;
	m_playerHealthBer = 100;

	m_boxDropCount = 120;

	m_boxPosX = kBoxPosX;
	m_boxPosY = kBoxPosY;
	m_boxPosBottomX = kBoxPosBottomX;
	m_boxPosBottomY = kBoxPosBottomY;

	m_pos.x = kPosX;
	m_pos.y = kPosY;

	m_underPos.x = m_pos.x + 50;
	m_underPos.y = m_pos.y + 100;

	m_gravity = kGravity;

	GetGraphSizeF(m_hPlayer, &m_playerSize.x, &m_playerSize.y);
}
void Player::End()
{

}
//�A�b�v�f�[�g����
void Player::Update()
{
	m_pEnemy->Update();

	(this->*m_func)();
}
//�`��
void Player::Draw()
{
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);

	//////////////////////////////////////
	//*�@�@�@�@�@�}�b�v�w�i�@�@�@�@�@�@*//
	//////////////////////////////////////
	DrawExtendGraph(0,0,  Game::kScreenWidth,Game::kScreenHeight,  m_hMapFirst , true);
	DrawExtendGraph(0 + GetRand(10), 0 + GetRand(10), Game::kScreenWidth + GetRand(10), Game::kScreenHeight + GetRand(10), m_hMapSecond, true);
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_hMapThird , true);
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_hMapFourth, true);

	//////////////////////////////////////
	//*�@�@�@�@�@�}�b�v�`�b�v�@�@�@�@�@*//
	//////////////////////////////////////

	//DrawRectRotaGraph(0, Game::kScreenHeight, 16, 224, 160, 32, 3, 0, m_hMapChip, true, true);
	DrawRectExtendGraph(
		kGroundSecondX, kGroundSecondY,
		kGroundSecondBottomX, kGroundSecondBottomY,
		16, 224, 160, 32,
		m_hMapChip, true);

	DrawRectExtendGraph(
		0, Game::kScreenHeight - 25, Game::kScreenWidth, Game::kScreenHeight + 10,
		16, 224, 160, 32,
		m_hMapChip, true);
	//////////////////////////////////////
	//*�n�ʂ͉����珇�Ԃɐ����Ă����܂�*//
	//////////////////////////////////////
	
	//�n��2
	DrawBox(kGroundSecondX, kGroundSecondY,
			kGroundSecondBottomX, kGroundSecondBottomY, 0x00ff00,false);

	//��q1
	DrawBox(kLadderX, kLadderY, kLadderXBottom, kLadderYBottom, 0xff0000, true);
	//     �@ left,  �@�@top,  �@�@ right,   �@�@�@bottom,
	 
	//�n�ʂP
	DrawBox(0, 700, Game::kScreenWidth + 1, kGround + 20 + 1, 0x00ff00, false);
	
	
	if(!m_isGetSword)
	{
		if (m_boxDropCount < 120)
		{
			m_stagingBoxX = GetRand(10), m_stagingBoxY = GetRand(10);
			m_stagingBoxBottomX = GetRand(10), m_stagingBoxBottomY = GetRand(10);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, GetRand(255));
		}
		else
		{
			m_stagingBoxX = 0;
			m_stagingBoxY = 0;
			m_stagingBoxBottomX = 0;
			m_stagingBoxBottomY = 0;
		}
		DrawBox(m_boxPosX + m_stagingBoxX, m_boxPosY + m_stagingBoxY, m_boxPosBottomX + m_stagingBoxBottomX, m_boxPosBottomY + m_stagingBoxBottomY, 0x00ff00, true);//�A�C�e���{�b�N�X
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	DrawLine(Game::kScreenWidth / 2, 520, Game::kScreenWidth - 120, 520, 0xffffff);//2
	DrawLine(0, kGround, Game::kScreenWidth, kGround, 0xffffff);//1

	//�̗̗͂ʕ\��
	if(!m_isHealthBer)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
		DrawBox(m_pos.x - 35, m_pos.y - 30, m_pos.x - 35 + 75, m_pos.y - 30 + 10, 0xff0000, true);
		DrawExtendGraph(m_pos.x - 35, m_pos.y - 30, m_playerHealthSizeX + m_pos.x - 35 + 75, m_playerHealthSizeY + m_pos.y - 30 + 10,m_hHealthBer,true);
		DrawBox(m_pos.x - 35, m_pos.y - 30, m_pos.x - 35 + 75, m_pos.y - 30 + 10, 0xffffff, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//�L�����N�^�[
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
	for (int i = 0; i < 4; i++)
	{
		DrawRotaGraph(m_pos.x - 3 + GetRand(5), m_pos.y + 20 + GetRand(5), 3, 0, m_hPlayerLighting, true, false);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (m_isIdleMove && !m_isAttackMove && !m_isDamageMove && !m_isJumpMove && !m_isCrouchingMove)//�������Ȃ�
	{

		DrawRectRotaGraph(static_cast<int>(m_imagePos.x) + static_cast<int>(m_imageBalancePos.x),
			static_cast<int>(m_imagePos.y) + static_cast<int>(m_imageBalancePos.y),
			m_charaImageIdlePos, 0, 80, 80, 2, 0, m_hPlayerIdle, true, m_isCharaIdleDirection);

	}
	else if (m_isRunMoveRight && !m_isAttackMove || m_isRunMoveLeft && !m_isAttackMove && !m_isDamageMove && !m_isJumpMove && !m_isCrouchingMove)//����
	{
		DrawRectRotaGraph(static_cast<int>(m_imagePos.x), static_cast<int>(m_imagePos.y),
			m_charaImagePos, 133, 112, 133, 2, 0, m_hPlayer, true, m_isCharaDirection);
	}
	if (m_isAttackMove && !m_isDamageMove && !m_isCrouchingMove)//���U��
	{
		DrawRectRotaGraph(static_cast<int>(m_imagePos.x) + 0,
			static_cast<int>(m_imagePos.y) + 0,
			m_charaImageAttackPos, 1197, 112, 133, 2, 0, m_hPlayer, true, m_isCharaDirection);
	}
	if (m_isDamageMove && !m_isCrouchingMove)//�U�����󂯂���
	{
		DrawRectRotaGraph(static_cast<int>(m_imagePos.x) + 0,
			static_cast<int>(m_imagePos.y) + 0,
			m_charaImageDamagePos, 1330, 112, 133, 2, 0, m_hPlayer, true, m_isCharaDirection);
	}
	if (m_isJumpMove && !m_isCrouchingMove)//�W�����v��������
	{
		DrawRectRotaGraph(static_cast<int>(m_imagePos.x) + 0,
			static_cast<int>(m_imagePos.y) + 0,
			m_charaImageJumpPos, 399, 112, 133, 2, 0, m_hPlayer, true, m_isCharaDirection);
	}

	if(m_isCrouchingMove)
	{
		DrawRectRotaGraph(static_cast<int>(m_imagePos.x) + 0,
			static_cast<int>(m_imagePos.y) + 0,
			m_charaImageCrouching, 532, 112, 133, 2, 0, m_hPlayer, true, m_isCharaDirection);
	}

	//���񂾏ꍇ�̃��j���[���
	if (m_isDead)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);//����
		DrawBox(350, 200, 300 + 600, 200 + 300, 0x0000ff, true);//�w�i
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawBox(350,200,300 + 600,200 + 300,0xffffff,false);//�g
		DrawString(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 100, "���Ȃ��͎��ɂ܂���", 0xff0000);
		DrawString(Game::kScreenWidth / 2 - 200, Game::kScreenHeight / 2 - 30, "�󂯓����", 0xffffff);
		DrawString(Game::kScreenWidth / 2 + 50, Game::kScreenHeight  / 2 - 30, "�󂯓���Ȃ�", 0xffffff);
		DrawString(Game::kScreenWidth / 2 - 200 + 35, Game::kScreenHeight / 2, "Y", 0xffffff);
		DrawString(Game::kScreenWidth / 2 + 50 + 40, Game::kScreenHeight  / 2, "N", 0xffffff);
	}


	DrawString(0, 0, "�Q�[���v���C", 0xffffff);


	////////////////////
	///*����̊m�F�p*///
	////////////////////
#if true	
	//�L�����N�^�[
	DrawBox(m_pos.x - 25, m_pos.y - 10, m_pos.x + 25, m_pos.y + 60, 0xff0000, false);
	DrawBox(m_playerLeft, m_playerTop, m_playerRight, m_playerBpttom, 0xffff00, false);
	//�Q�K���痎����͈�
	DrawBox(kFallBoxX, kFallBoxY, kFallBoxBottomX, kFallBoxBottomY, 0xf000f0, false);
	//printfDx("%f\n", m_pos.y);
	printfDx("%d\n", m_playerHealthBer);

#endif
}
//����
void Player::Operation()
{
	//���͔���
	Pad::update();

	m_isCrouchingMove = false;
	m_isRunMoveRight = false;//�E�ɓ����Ă��邩�ǂ���
	m_isRunMoveLeft = false;//���ɓ����Ă��邩�ǂ���
	m_isIdleMove = true;//�����Ă��邩�ǂ���

	//�ړ�
	if (CheckHitKey(KEY_INPUT_RIGHT) && !m_isAttackMove && !m_isDamageMove && !m_isCrouchingMove)//�E
	{
		m_pos.x += kMoveSpeed;
		m_underPos.x += kMoveSpeed;
		m_isCharaDirection = true;//�摜���]
		m_isRunMoveRight = true;
		m_isIdleMove = false;
		m_isCharaIdleDirection = false;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) && !m_isAttackMove && !m_isDamageMove && !m_isCrouchingMove)//��
	{
		m_pos.x -= kMoveSpeed;
		m_underPos.x -= kMoveSpeed;
		m_isCharaDirection = false;//�摜���]
		m_isRunMoveLeft = true;
		m_isIdleMove = false;
		m_isCharaIdleDirection = true;
	}

	//�A�b�v�_�E��
	if (CheckHitKey(KEY_INPUT_UP) && CheckHit() == 1 && !m_isAttackMove && !m_isDamageMove && !m_isCrouchingMove)//��q���
	{
		m_vec.y = 0.0f;
		m_pos.y -= kMoveSpeed;
		m_isIdleMove = false;
	
	} 
	if(m_isInvaliDown && !m_isAttackMove && !m_isDamageMove && !m_isCrouchingMove)
	{
		if (CheckHitKey(KEY_INPUT_DOWN) && CheckHit() == 1)//��q����
		{
			m_vec.y = 0.0f;
			m_pos.y += kMoveSpeed;
			m_isIdleMove = false;
		}
	}

	//�W�����v
	if (Pad::isTrigger(KEY_INPUT_UP) && CheckHit() == 0 && !m_isAttackMove && !m_isDamageMove)//��
	{
		if (FieldJudgement() == 1 ||
			FieldJudgement() == 2)//�n�ʂɂ����Ԃ̏ꍇ
		{
			printfDx("�W�����v\n");
			m_vec.y = kJump;//�W�����v�J�n
			m_isJumpMove = true;
			//m_isIdleMove = false;
		}
	}

	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_isCrouchingMove = true;
	}

	//�U��
	if(m_isGetSword && !m_isDamageMove && !m_isCrouchingMove)
	{
		if(CheckHitKey(KEY_INPUT_V))
		{
			m_isAttackMove = true;
		}
	}

	//�|�[�Y���j���[
	if (CheckHitKey(KEY_INPUT_P))
	{
		m_func = &Player::MenuStop;
	}
		
}
//�A�j���[�V����
void Player::Condition()
{	

	if (m_isCharaIdleDirection)
	{
		m_imageBalancePos.x = -20;
		m_imageBalancePos.y = 20;
	}
	else
	{
		m_imageBalancePos.x = 20;
		m_imageBalancePos.y = 20;
	}

	//�A�C�h�����
	if(m_isIdleMove)
	{
		m_frameCount++;
		if(m_frameCount >= kAnimationFrame)
		{
			m_charaImageIdlePos += 80;
			m_frameCount = 0;
		}
		if (m_charaImageIdlePos == 1440)
		{
			m_charaImageIdlePos = 0;
		}
	}
	
	//�E�Ɉړ��A�j���[�V����
	if(m_isRunMoveRight)
	{
		m_frameCount++;
		if (m_frameCount >= kAnimationFrame)
		{
			m_charaImagePos -= kCharaImageRightPos;
			m_frameCount = 0;
		}
		if (m_charaImagePos == 0)
		{
			m_charaImagePos = (1344 - kCharaImageRightPos);
		}
	}

	//���Ɉړ��A�j���[�V����
	if(m_isRunMoveLeft)
	{
		m_frameCount++;
		if (m_frameCount >= kAnimationFrame)
		{
			m_charaImagePos -= kCharaImageRightPos;
			m_frameCount = 0;
		}
		if (m_charaImagePos == 0)
		{
			m_charaImagePos = (1344 - kCharaImageRightPos);
		}
	}

	//�U�����󂯂��ꍇ
	if (m_isDamageMove)
	{
		m_frameCount++;
		if (m_frameCount >= kAnimationFrame)
		{
			m_charaImageDamagePos += kCharaImageRightPos;
			m_frameCount = 0;
		}
		if(m_charaImageDamagePos == kCharaImageRightPos * 7)
		{
			m_charaImageDamagePos = 0;
	
			m_isDamageMove = false;

		}
	}

	//�W�����v�����ꍇ
	if (m_isJumpMove)
	{
		m_frameCount++;
		if (m_frameCount >= kAnimationFrame)
		{
			m_charaImageJumpPos += kCharaImageRightPos;
			m_frameCount = 0;
		}
		if (m_charaImageJumpPos == kCharaImageRightPos * 12)
		{
			m_charaImageJumpPos = 0;

			if (FieldJudgement() == 1 || FieldJudgement() == 2)
			{
				m_isJumpMove = false;
			}
		}
	}

	if (m_isCrouchingMove)
	{
		m_frameCount++;
		if (m_frameCount >= kAnimationFrame)
		{
			m_charaImageCrouching += kCharaImageRightPos;
			m_frameCount = 0;
		}
		if (m_charaImageCrouching >= kCharaImageRightPos)
		{
			m_charaImageCrouching = kCharaImageRightPos;
	
		}
	}
	else
	{
		m_isCrouchingMove = false;
	}

	//�U���A�j���[�V�����i���j
	if (m_isAttackMove)
	{
		m_frameCount++;
		if (m_frameCount >= kAnimationFrame)
		{
			m_charaImageAttackPos += kCharaImageRightPos;
			m_frameCount = 0;
		}
		if (m_charaImageAttackPos >= 1344)
		{
			m_charaImageAttackPos = 0;
			m_isAttackMove = false;//�U�������Ă��邩�ǂ���
		}
	}
	else
	{
		m_charaImageAttackPos = 0;
	}

}
//�n�ʂƂ̔���
int Player::FieldJudgement()
{
	m_isInvaliDown = false;

	if (CheckHit() == 1)//��q�̔���
	{
		return 0;
	}

	////////////////////////////////////
	///*�����蔻����l�p�`�ɕύX�\��*///
	////////////////////////////////////
	/*	if(m_hierarchy == 1)
	{
		if(m_pos.y >= kGround - 60 - m_playerSize.y)//�n�ʂɒ��n
		{
			m_pos.y = kGround - 60 - m_playerSize.y;
			m_isInvaliDown = true;//�n�ʂɂ���ꍇ�W�����v�\

			return 1;
		}
	}
	*/

	//2�K�̔���
	if ((kGroundSecondBottomX > m_pos.x - 25) &&
		(kGroundSecondX       < m_pos.x + 25))
	{
		if ((kGroundSecondBottomY > m_pos.y) &&
			(kGroundSecondY       < m_pos.y + 60))
		{
			m_pos.y = 520 - 60 - m_playerSize.y;
			m_isInvaliDown = true;//���Ɉړ��ł��Ȃ�
			return 1;
		}
	}

	//1�K�̔���
	if ((Game::kScreenWidth + 1 > m_playerLeft) &&
		(0                     < m_playerRight))
	{
		if ((kGround + 20 + 1 > m_playerTop) &&
			(700              < m_playerBpttom))
		{

			m_pos.y = kGround - 50 - m_playerSize.y;
			m_isInvaliDown = true;//���Ɉړ��ł��Ȃ�
			return 1;

		}
	}

	return 0;
}
//�L�����N�^�[�Ƃ͂����̔���
int Player::CheckHit()
{

	if ((kLadderXBottom > m_playerLeft) &&
		(kLadderX < m_playerRight))
	{
		if ((kLadderYBottom > m_playerTop) &&
			(kLadderY < m_playerBpttom))
		{
			m_isFloorOne = true;
			m_isInvaliDown = true;
			m_count++;
			//1�t���[�������ő������i�\��
			if (m_count == 1)
			{
				//m_pos.x = (10 + kLadderX);
			}

			/*
			if (static_cast<int>(m_pos.y) <= 680)
			{
				m_hierarchy = 1;
			}
			
			if (static_cast<int>(m_pos.y) <= 580)
			{
				m_hierarchy = 2;
			}
			*/
			return 1;
		}
	}

	m_isFloorOne = false;
	m_count = 0;

	return 0;
}
//�A�C�e���{�b�N�X�̔���
void Player::BoxJudgement()
{
	if ((m_boxPosBottomX > m_playerLeft) &&
		((m_boxPosX < m_playerRight)))
	{
		if ((m_boxPosBottomY > m_playerTop) &&
			(m_boxPosY < m_playerBpttom))
		{
			//printfDx("�{�b�N�X����\n");
			m_isItemDrop = true;
			if (m_boxDropCount >= 120)
			{
				m_isGetSword = true;//�A�C�e���{�b�N�X��\��
				m_boxDropCount = 0;

			}

		}
	}

}
//���ɗ����锻��
void Player::CheckFall()
{
	if ((kFallBoxBottomX > m_pos.x - 25) &&
		(kFallBoxX < m_pos.x + 25))
	{
		if ((kFallBoxBottomY > m_pos.y) &&
			(kFallBoxY < m_pos.y + 60))
		{
			m_hierarchy = 1;
		}
	}
}
//�G�ƃv���C���[�̔���
bool Player::EnemyHit()
{
	if ((m_pEnemy->GetSizeBottom().x > m_playerLeft) &&
		(m_pEnemy->GetSize().x < m_playerRight))
	{
		if ((m_pEnemy->GetSizeBottom().y > m_playerTop) &&
			(m_pEnemy->GetSize().y < m_playerBpttom))
		{
			if (m_isGetSword)
			{

				m_boxPosX = m_pos.x;
				m_boxPosY = m_pos.y - 80;
				m_boxPosBottomX = m_boxPosX + 50;
				m_boxPosBottomY = m_boxPosY + 50;

				m_isGetSword = false;//�A�C�e���{�b�N�X�h���b�v
			}

			m_isDamageMove = true;//�_���[�W�A�j���[�V�����Đ�
			return true;
		}
	}
	return false;
}
//�v���C���[�̗̑͂��Ǘ�
void Player::HealthControl()
{
	m_playerHealthBerCount += 1;
	if (m_playerHealthBerCount == 1)
	{
		m_playerHealthBer -= 20;
		m_playerHealthSizeX -= 20;
	}

	if (m_playerHealthBer <= 0)
	{
		m_playerHealthBer = 1;
		printfDx("���S\n");
		m_playerHealthSizeX = 0;
		m_isHealthBer = true;
		//�|�[�Y���j���[

		m_func = &Player::DeathMenu;
		
	}
	
}
//�A�b�v�f�[�g����
void Player::UpdateMove()
{	
	clsDx();

	if(!FieldJudgement() == 1)
	{
		//�d��
		m_vec.y += m_gravity;	
	}
	else
	{
		m_vec.y = 0.0f;
	}

	m_playerLeft = m_pos.x - 15;
	m_playerTop = m_pos.y + 10;
	m_playerRight = m_pos.x + 10;
	m_playerBpttom = m_pos.y + 60;

	//�v���C���[�ʒu
	m_imagePos = m_pos;
	m_pos      += m_vec;
	m_underPos += m_vec;

	////////////////////
	////*�����蔻��*////
	///////////////////
	//�͂���
	CheckHit();
	//�n��
	FieldJudgement();
	//�A�C�e��
	BoxJudgement();
	if (!m_isGetSword)
	{
		m_boxDropCount++;
	}
	if (m_boxDropCount >= 120)
	{
		m_boxDropCount = 120;
	}
	//�G�Ƃ̓����蔻��
	EnemyHit();
	if(!m_isHealthBer)
	{
		if(EnemyHit())
		{
			//m_boxDropCount++;
			HealthControl();
		}
		else
		{
			m_playerHealthBerCount = 0;
		}
	}
	////////////////////////
	///*���ꂢ��Ȃ�����*///
	////////////////////////
	//����
//	CheckFall();
	//����
	Operation();
	//��ԁi�����j
	Condition();
}
//�|�[�Y���
void Player::MenuStop()
{
	printfDx("�|�[�Y��\n");
	printfDx("�~�Ϗ��u\n");
	if (CheckHitKey(KEY_INPUT_O))
	{
		m_func = &Player::UpdateMove;
	}
	m_isDead = true;
	if (CheckHitKey(KEY_INPUT_Y))
	{
		m_isReset = true;
	}
	if (CheckHitKey(KEY_INPUT_N))
	{
		m_isTitle = true;
	}
}
//���񂾏ꍇ��Menu
void Player::DeathMenu()
{
	m_isDead = true;
	if (CheckHitKey(KEY_INPUT_Y))
	{
		m_isReset = true;
	}
	if (CheckHitKey(KEY_INPUT_N))
	{
		m_isTitle = true;
	}
}