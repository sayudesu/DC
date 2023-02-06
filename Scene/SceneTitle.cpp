#include "SceneTitle.h"
#include "SceneMain.h"
#include "DxLib.h"
#include "game.h"

namespace
{

}

void SceneTitle::Init()
{

}
void SceneTitle::End()
{

}

SceneBase* SceneTitle::Update()
{


	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//���j���[��ʂɈړ�
	if (padState & PAD_INPUT_1)
	{
		return(new SceneMain);
	}


	return this;
}

void SceneTitle::Draw()
{
	DrawString(0,0, "�^�C�g��", 0xffffff);
	DrawString(0, 100, "Z�ŊJ�n", 0xffffff);
}