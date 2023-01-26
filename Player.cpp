#include "SceneMain.h"
#include "Player.h"
#include <DxLib.h>
#include "Pad.h"
#include "game.h"

namespace
{
	//�v���C���[�̏������W
	constexpr float kPosX = 20.0f;
	constexpr float kPosY = 720.0f;
	//��������
	constexpr float kMoveSpeed = 7.0f;
	// �W�����v��
	constexpr float kJump = -15.0f;
	// �d��
	constexpr float kGravity = 1.5f;

	//�n�ʂ̍���Y��
	constexpr int kGround = 750;

	//�͂����P���W
	constexpr int kLadderX = Game::kScreenWidth - 120;
	constexpr int kLadderY = 500;
	constexpr int kLadderXBottom = Game::kScreenWidth - 80;
	constexpr int kLadderYBottom = Game::kScreenHeight - 50;
}

Player::Player() :
	m_hPlayer(-1),
	m_gravity(0.0f),
	m_isLadder(false),
	m_playerSize(0.0f, 0.0f),
	m_pos(0.0, 0.0),
	m_underPos(0.0, 0.0),
	m_vec(0.0, 0.0)
{
	m_func = &Player::UpdateMove;
}

Player::~Player()
{

}

void Player::Init()
{
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
	DrawString(0, 0, "�Q�[���v���C", 0xffffff);
	//�L�����N�^�[
	DrawRotaGraphF(m_pos.x,m_pos.y, 0.2, DX_PI / 2, m_hPlayer, true);

	//////////////////////////////////////
	//*�n�ʂ͉����珇�Ԃɐ����Ă����܂�*//
	//////////////////////////////////////
	
	//�n��2
	DrawLine(Game::kScreenWidth / 2, 500, Game::kScreenWidth, 500, 0xffffff);
	//��q�P����Q
	DrawLine(Game::kScreenWidth - 100, kGround, Game::kScreenWidth - 100, 500, 0xffffff);
	//�n��1
	DrawLine(0, kGround, Game::kScreenWidth, kGround, 0xffffff);
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
	}
	if (CheckHitKey(KEY_INPUT_LEFT))//��
	{
		m_pos.x -= kMoveSpeed;
		m_underPos.x -= kMoveSpeed;
	}
	//�A�b�v�_�E��
	if (CheckHit())
	{
		m_isLadder = true;
		m_vec.y = 0.0f;
		if (CheckHitKey(KEY_INPUT_UP))//��q���
		{
			m_pos.y -= kMoveSpeed;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))//��q����
		{
			m_pos.y += kMoveSpeed;
		}
	}
	else if (!CheckHit())//�W�����v
	{
		m_gravity = kGravity;//�d�͂�������

		//�W�����v
		if (Pad::isTrigger(KEY_INPUT_UP))//��
		{
			if (FieldJudgement() == 1)//�n�ʂɂ����Ԃ̏ꍇ
			{
				m_vec.y = kJump;//�W�����v�J�n
			}
		}
	}

	//�|�[�Y���j���[
	if (CheckHitKey(KEY_INPUT_P))
	{
		m_func = &Player::MenuStop;
	}
		
}
int Player::FieldJudgement()
{
	if (CheckHit())//��q�̔���
	{
		return 0;
	}
	else if(m_pos.y >= kGround - m_playerSize.y - 30)//�n�ʂɒ��n
	{
		m_pos.y = kGround - 30 - m_playerSize.y;
		
		printfDx("�n��1\n");
		return 1;
	}

	if (m_pos.y >= 500 - m_playerSize.y - 30 && m_isLadder)//�n��2
	{
		m_pos.y = 500 - 30 - m_playerSize.y;
		printfDx("�n��2\n");
		return 1;
	}
}

void Player::UpdateMove()
{	
	//�v���C���[�ʒu
	m_pos += m_vec;
	m_underPos += m_vec;

	//�d��
	m_vec.y += m_gravity;

	////////////////////
	////*�����蔻��*////
	///////////////////
	
	//�͂���
	CheckHit();
	//�n��
	FieldJudgement();

	//����
	Operation();

	//////////////////////////
	/////*����̊m�F�p*///////
	//////////////////////////
#if true	

	if (CheckHit())
	{
		printfDx("��q1\n");
	}
	else if (true)
	{
		printfDx("��q0\n");
	}
	//�L�����̒��S
	DrawPixel(m_pos.x, m_pos.y, 0xff0000);
	//�L�����N�^�[
	DrawBox(m_pos.x - 25, m_pos.y - 25, m_pos.x + 25, m_pos.y + 25, 0xff0000, true);
	//�͂���
	DrawBox(kLadderX, kLadderY, kLadderXBottom, kLadderYBottom, 0xff0000, true);
	//     �@ left,  �@�@top,  �@�@ right,   �@�@�@bottom,
#endif
}

void Player::MenuStop()
{
	printfDx("�|�[�Y��\n");
}

//�L�����N�^�[�Ƃ͂����̔���
bool Player::CheckHit()
{
	if ((kLadderXBottom > m_pos.x - 25) &&
		(kLadderX < m_pos.x + 25))
	{
		if ((kLadderYBottom > m_pos.y - 25) &&
			(kLadderY < m_pos.y + 25))
		{
			return true;
		}
	}

	return false;
}
