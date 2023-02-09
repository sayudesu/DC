#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include <Dxlib.h>

SceneGameOver::SceneGameOver()
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
}

void SceneGameOver::End()
{
}

SceneBase* SceneGameOver::Update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//���j���[��ʂɈړ�
	if (padState & PAD_INPUT_1)
	{
		return(new SceneTitle);
	}
	return this;
}

void SceneGameOver::Draw()
{
	DrawString(10, 0, "�Q�[���I�[�o�[", 0xffffff);
	DrawString(10, 100, "Z�Ń^�C�g����ʂɈړ�", 0xffffff);
}
