#include <Dxlib.h>
#include "game.h"
#include "Pad.h"
#include "SelectMenu.h"
#include "TitleCursor.h"


SelectMenu::SelectMenu():
	m_frameCount(0),//���j���[��ʂ��J�������Ƀf�B���C������
	m_isMenu(false),//���j���[���J���Ă��邩�ǂ���
	m_pCursor(nullptr)
{
	m_pCursor = new TitleCursor;
}

SelectMenu::~SelectMenu()
{
	delete m_pCursor;
}

void SelectMenu::Init()
{

}

void SelectMenu::Update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	m_pCursor->GetMenu(m_isMenu);
	m_pCursor->Update();//�J�[�\���\��
	if (m_isMenu)//���j���[�\�����Ă���ꍇ
	{
		m_frameCount++;
		if (m_frameCount >= 30)
		{
			if (padState & PAD_INPUT_X)//���j���[�����
			{
				m_isMenu = false;//���j���[��ʂ��\��
				m_frameCount = 0;
			}
		}
	}
	else
	{
		m_frameCount++;
		if (m_frameCount >= 30)
		{
			if (padState & PAD_INPUT_X)//���j���[���J��
			{
				m_isMenu = true;
				m_frameCount = 0;
			}
		}
	}
}

void SelectMenu::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(500, 300, Game::kScreenWidth - 500, Game::kScreenHeight - 300, 0x00ffff, true);//��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(500, 300, Game::kScreenWidth - 500, Game::kScreenHeight - 300, 0xffffff, false);//�g�g��

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//�F�𔖂�����
//DrawBox(SceneSelect::kSelectLeft, SceneSelect::kSelectTop, SceneSelect::kSelectRight, SceneSelect::kSelectBottom, m_color1, true);
	DrawBox(SceneSelect::kSelectLeft2, SceneSelect::kSelectTop2, SceneSelect::kSelectRight2, SceneSelect::kSelectBottom2, 0xffffff, true);
	DrawBox(SceneSelect::kSelectLeft3, SceneSelect::kSelectTop3, SceneSelect::kSelectRight3, SceneSelect::kSelectBottom3, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�F��߂�

	m_pCursor->Draw();//�J�[�\���\��
}