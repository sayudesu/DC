#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include <DxLib.h>
#include "game.h"

namespace
{
	constexpr float kPosX = 20.0f;
	constexpr float kPosY = 650.0f;
	//��������
	constexpr float kMoveSpeed = 7.0f;
	// �W�����v��
	constexpr float kJump = -30.0f;
	// �d��
	constexpr float kGravity = 1.5f;
}

SceneMain::SceneMain():
	m_pos(0.0,0.0),
	m_underPos(0.0, 0.0),
	m_vec(0.0,0.0)
{
	m_func = &SceneMain::UpdateMove;
}

SceneMain::~SceneMain()
{

}

void SceneMain::init()
{
	m_pos.x = kPosX;
	m_pos.y = kPosY;

	m_underPos.x = m_pos.x + 50;
	m_underPos.y = m_pos.y + 100;
}
void SceneMain::end()
{

}

SceneBase* SceneMain::update()
{
	(this->*m_func)();
	return this;
}

void SceneMain::draw()
{
	DrawString(0, 0, "�Q�[���v���C", 0xffffff);

	//�L�����N�^�[
	DrawBox(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		static_cast<int>(m_underPos.x), static_cast<int>(m_underPos.y),0xffffff,true);

	//�n��
	DrawLine(0, 750,Game::kScreenWidth / 2, 750,0xffffff);
}

void SceneMain::UpdateMove()
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
		m_pos.x +=kMoveSpeed;
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
			m_vec.y = kJump;	// �W�����v�J�n
		}
	}

	//�d��
	//m_vec.y += kGravity;
#endif
}
