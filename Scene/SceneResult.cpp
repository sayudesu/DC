#include "SceneResult.h"
#include "SceneTitle.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	constexpr int kW = 192;
	constexpr int kH = 192;
}

SceneResult::SceneResult():
	handle(-1),
	left(0),
	top(0),
	rigth(kW),
	bottom(kH),
	frameCount(0),
	changeY(false),
	m_pos(0.0f, 0.0f)//���S.x.y
{
	m_pos.x = 200.0f;
	m_pos.y = 200.0f;
}

void SceneResult::Init()
{
	handle = LoadGraph("Data/pipo-mapeffect017_192.png");
}

void SceneResult::End()
{

}

SceneBase* SceneResult::Update()
{
	printfDx("%d\n", left);
	
	frameCount++;

	//10�t���[�����Ƃɉ摜���E��192�h�b�g�ړ����Ă���
	if (frameCount == 3)
	{
		frameCount = 0;//�t���[���J�E���g���Z�b�g
		left += kW;//192�v���X
	}
	if (left == 960)//�摜�̉E�܂ňړ�����ƍ��Ƀ��Z�b�g
	{
		left = 0;
		changeY = true;//�摜������192�ړ�
	}
	if (changeY)//�摜������192�h�b�g�ړ�
	{
		top += kH;
		changeY = false;
	}
	if (top ==768)
	{
		top = 0;
	}
	
	return(new SceneTitle);
	return this;
}

void SceneResult::Draw()
{

	DrawRectRotaGraph(m_pos.x, m_pos.y,
		left, top, rigth, bottom, 1, 0, handle, true, false);
}