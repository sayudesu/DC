#include "SceneMain.h"
#include "Player.h"
#include <DxLib.h>
#include "Pad.h"
#include "game.h"

namespace
{
	//�v���C���[�̏������W
	constexpr float kPosX = 20.0f;
	constexpr float kPosY = 700.0f;
	//��������
	constexpr float kMoveSpeed = 7.0f;
	// �W�����v��
	constexpr float kJump = -15.0f;
	// �d��
	constexpr float kGravity = 1.5f;

	//�n�ʂ̍���Y��
	constexpr int kGround = 750;

	constexpr int kCharaImageLeftPos = -112; //���ړ�

	constexpr int kCharaImageRightPos = 112; //�E�ړ�

	//constexpr int 

	////////////////////
	///*�n�ʁ@�Q���W*///
	////////////////////
	constexpr int kGroundSecondX = Game::kScreenWidth / 2;
	constexpr int kGroundSecondY = 600;
	constexpr int kGroundSecondBottomX = Game::kScreenWidth;
	constexpr int kGroundSecondBottomY = 600 + 20;

	////////////////////
	///*�͂����P���W*///
	////////////////////
	constexpr int kLadderX = Game::kScreenWidth - 120;
	constexpr int kLadderY = 580;
	constexpr int kLadderXBottom = Game::kScreenWidth - 90;
	constexpr int kLadderYBottom = Game::kScreenHeight - 70;
}

Player::Player() :
	m_hPlayer(-1),
	m_charaImagePos(0),
	m_frameCount(0),
	m_hierarchy(0),
	m_gravity(0.0f),
	m_isFloorOne(false),
	m_isLadder(false),
	m_isInvaliDown(false),
	m_isCharaDirection(false),
	m_playerSize(0.0f, 0.0f),
	m_pos(0.0, 0.0),
	m_underPos(0.0, 0.0),
	m_vec(0.0, 0.0)
{
	m_charaImagePos = (1344 - kCharaImageRightPos);
	m_func = &Player::UpdateMove;
}

Player::~Player()
{

}

void Player::Init()
{
	m_hierarchy = 1;

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

void Player::Update()
{
	(this->*m_func)();
}

void Player::Draw()
{

	//�L�����N�^�[
	DrawRectRotaGraph(m_pos.x, m_pos.y,m_charaImagePos, 133, 112, 133, 2, 0, m_hPlayer, true, m_isCharaDirection);

	//////////////////////////////////////
	//*�n�ʂ͉����珇�Ԃɐ����Ă����܂�*//
	//////////////////////////////////////
	
	//�n��2
	DrawBox(kGroundSecondX, kGroundSecondY, kGroundSecondBottomX, kGroundSecondBottomY, 0x00ff00,false);
	DrawLine(Game::kScreenWidth / 2, 600, Game::kScreenWidth, 600, 0xffffff);
	//��q1
	DrawBox(kLadderX, kLadderY, kLadderXBottom, kLadderYBottom, 0xff0000, true);
	//     �@ left,  �@�@top,  �@�@ right,   �@�@�@bottom,
	//�n�ʂP
	DrawBox(0,kGround, Game::kScreenWidth + 1, kGround + 20 + 1, 0x00ff00, false);
	DrawLine(0, kGround, Game::kScreenWidth, kGround, 0xffffff);
	DrawPixel(Game::kScreenWidth / 2 - 150, 500, 0xffffff);

	DrawString(0, 0, "�Q�[���v���C", 0xffffff);
}

void Player::Operation()
{
	//���͔���
	Pad::update();

	//�ړ�
	if (CheckHitKey(KEY_INPUT_RIGHT))//�E
	{
		m_pos.x += kMoveSpeed;
		m_underPos.x += kMoveSpeed;
		m_isCharaDirection = true;//�摜���]
	}
	if (CheckHitKey(KEY_INPUT_LEFT))//��
	{
		m_pos.x -= kMoveSpeed;
		m_underPos.x -= kMoveSpeed;
		m_isCharaDirection = false;//�摜���]
	}

	//�A�b�v�_�E��
	if (CheckHitKey(KEY_INPUT_UP) && CheckHit() == 1)//��q���
	{
		m_vec.y = 0.0f;
		m_pos.y -= kMoveSpeed;
	
	} 

	if(!m_isInvaliDown)
	{
		if (CheckHitKey(KEY_INPUT_DOWN) && CheckHit() == 1)//��q����
		{
			m_vec.y = 0.0f;
			m_pos.y += kMoveSpeed;
		
		}
	}

	//�W�����v
	if (Pad::isTrigger(KEY_INPUT_UP) && CheckHit() == 0)//��
	{
		if (FieldJudgement() == 1 || FieldJudgement() == 2)//�n�ʂɂ����Ԃ̏ꍇ
		{
			//printfDx("�W�����v\n");
			m_vec.y = kJump;//�W�����v�J�n
		}
	}

	//�|�[�Y���j���[
	if (CheckHitKey(KEY_INPUT_P))
	{
		m_func = &Player::MenuStop;
	}
		
}

void Player::Condition()
{
	//�E�Ɉړ��A�j���[�V����
	if(m_isCharaDirection)
	{
		m_frameCount++;
		if (m_frameCount == 3)
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
	if(!m_isCharaDirection)
	{
		m_frameCount++;
		if (m_frameCount == 3)
		{
			m_charaImagePos -= kCharaImageRightPos;
			m_frameCount = 0;
		}
		if (m_charaImagePos == 0)
		{
			m_charaImagePos = (1344 - kCharaImageRightPos);
		}
	}
}

int Player::FieldJudgement()
{
	m_isInvaliDown = false;

	if (CheckHit() == 1)//��q�̔���
	{
		return 0;
	}

	if(m_hierarchy == 1)
	{
		if(m_pos.y >= kGround - 60 - m_playerSize.y)//�n�ʂɒ��n
		{
			if(!m_isFloorOne)
			{
				m_pos.y = kGround - 60 - m_playerSize.y;
				m_isInvaliDown = true;//�n�ʂɂ���ꍇ�W�����v�\

			}
			return 1;
		}
	}
	
	//�Q�K�ɗ�����쓮����	
	if (m_hierarchy == 2)
	{
		if (m_pos.y >= 600 - 60 - m_playerSize.y)//�n��2
		{
			m_pos.y = 600 - 60 - m_playerSize.y;
			return 2;
		}
	}
}

//�L�����N�^�[�Ƃ͂����̔���
int Player::CheckHit()
{

	/// /////////////////////////////////////////////////////////////
	//�����C���_//////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	if ((kLadderXBottom > m_pos.x - 25) &&
		(kLadderX < m_pos.x + 25))
	{
		if ((kLadderYBottom > m_pos.y - 10) &&
			(kLadderY < m_pos.y + 60))
		{
			m_isFloorOne = true;
			printfDx("��q");
			if (static_cast<int>(m_pos.y) <= 580)
			{
				m_hierarchy = 2;
			}

			return 1;
		}
	}
	m_isFloorOne = false;
	return 0;
}

void Player::UpdateMove()
{	
	if(!m_isFloorOne)
	{
		//�d��
		m_vec.y += m_gravity;	
	}
	//�v���C���[�ʒu
	m_pos += m_vec;
	m_underPos += m_vec;
	
	////////////////////
	////*�����蔻��*////
	///////////////////
	
	//�͂���
	CheckHit();
	////�n��
	FieldJudgement();

	//����
	Operation();



	//////////////////////////
	/////*����̊m�F�p*///////
	//////////////////////////
#if true	

	if (CheckHit())
	{
		//printfDx("��q1\n");
	}
	else if (true)
	{
		//printfDx("��q0\n");
	}
	//�L�����̒��S
	DrawPixel(m_pos.x, m_pos.y, 0xffff00);
	//�L�����N�^�[
	DrawBox(m_pos.x - 25, m_pos.y - 10, m_pos.x + 25, m_pos.y + 60, 0xff0000, false);
	printfDx("%f\n", m_pos.y);
	
#endif
}

void Player::MenuStop()
{
	printfDx("�|�[�Y��\n");
	if (CheckHitKey(KEY_INPUT_O))
	{
		m_func = &Player::UpdateMove;
	}
}


