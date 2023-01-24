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
	constexpr float kJump = -30.0f;
	// �d��
	constexpr float kGravity = 1.5f;
}

Player::Player() :
	m_hPlayer(-1),
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
	//�n��
	DrawLine(0, 750, Game::kScreenWidth / 2, 750, 0xffffff);
}

void Player::UpdateMove()
{
	m_pos += m_vec;
	m_underPos += m_vec;

#if true	
	//�n�ʂƂ̓����蔻��
	bool isField = false;
	if (m_underPos.y == 750)
	{
		m_pos.y = 650.0f;
		//m_pos.y = 750 - m_underPos.y;
		isField = true;
	}
#endif

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

#if true		
	if (CheckHitKey(KEY_INPUT_UP))
	{
		if (isField)//�n�ʂɂ����Ԃ̏ꍇ
		{
			m_vec.y = kJump;//�W�����v�J�n
		}
	}

	//�d��
	//m_vec.y += kGravity;
#endif
}
