#include "PlayerAnimation.h"
#include <Dxlib.h>

PlayerAnimation::PlayerAnimation():
	m_hPlayer(-1),//�v���C���[�摜
	m_hPlayerIdle(-1),//�v���C���[�摜�i�A�C�h����ԁj
	m_posY(0),
	m_pos(0.0f, 0.0f)
{
}

PlayerAnimation::~PlayerAnimation()
{
}

void PlayerAnimation::Update()
{
	//printfDx("%f\n", m_pos.x);
	printfDx("%d\n", m_posY);
	m_pos.y = m_posY;


}

void PlayerAnimation::Draw()
{
	//�������Ă��Ȃ����
	DrawRectRotaGraph(m_pos.x, m_pos.y,
		0, 0, 112, 133,
		1.5, 0, m_hPlayerIdle, true, true);

	//��112
	//�c133
}
