#include "SceneMain.h"
#include "Player.h"
#include <DxLib.h>
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

}

Player::Player() :
	m_hPlayer(-1),
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
int Player::FieldJudgement()
{
	//�n�ʂƂ̓����蔻��
	//bool isField = false;
	//�n�ʂP
	if (m_pos.y >= kGround - 30 - m_playerSize.y)
	{
		m_pos.y = kGround - 30 - m_playerSize.y;
		isField = true;
		return 1;
	}

	if (m_pos.x >= Game::kScreenWidth - 125 &&
		m_pos.x <= Game::kScreenWidth - 75 )
	{
		printfDx("����\n");
		isField = false;
	}
	else
	{
		clsDx();
	}

	//return isField;
}

void Player::UpdateMove()
{
	//�v���C���[�ʒu
	m_pos += m_vec;
	m_underPos += m_vec;

	//�d��
	m_vec.y += kGravity;

	FieldJudgement();

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_pos.x += kMoveSpeed;
		m_underPos.x += kMoveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_pos.x -= kMoveSpeed;
		m_underPos.x -= kMoveSpeed;
	}

	if (CheckHitKey(KEY_INPUT_UP))
	{
		if (FieldJudgement())//�n�ʂɂ����Ԃ̏ꍇ
		{
			m_vec.y = kJump;//�W�����v�J�n
		}
		else
		{
			m_pos.y = 500 - 30;
		}
	}
}
