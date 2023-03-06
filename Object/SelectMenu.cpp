#include "SelectMenu.h"
#include "TitleCursor.h"
#include "game.h"
#include <Dxlib.h>


SelectMenu::SelectMenu():
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

	if (m_isMenu)//���j���[�\�����Ă���ꍇ
	{
		m_pCursor->Update();//�J�[�\���\��

		if (CheckHitKey(KEY_INPUT_O))//���j���[�����
		{
			m_isMenu = false;//���j���[��ʂ��\��
		}
	}
	if (CheckHitKey(KEY_INPUT_P))//���j���[���J��
	{
		m_isMenu = true;
	}

}

void SelectMenu::Draw()
{
	DrawBox(500, 300, Game::kScreenWidth - 500, Game::kScreenHeight - 300, 0x00ffff, true);//��
	DrawBox(500, 300, Game::kScreenWidth - 500, Game::kScreenHeight - 300, 0xffffff,false);//�g�g��
	m_pCursor->Draw();//�J�[�\���\��
}
