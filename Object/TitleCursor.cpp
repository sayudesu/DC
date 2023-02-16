#include "TitleCursor.h"
#include "game.h"
#include <Dxlib.h>

TitleCursor::TitleCursor():
	m_padPos(0.0f,0.0f)
{
	m_padPos.x = Game::kScreenWidth / 2;
	m_padPos.y = Game::kScreenHeight / 2;
}

TitleCursor::~TitleCursor()
{
}

void TitleCursor::Init()
{
	
}

void TitleCursor::Update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (padState & PAD_INPUT_RIGHT)//�E
	{
		m_padPos.x += 10;
	}
	if (padState & PAD_INPUT_LEFT)//�E
	{
		m_padPos.x -= 10;
	}
	if (padState & PAD_INPUT_UP)//�E
	{
		m_padPos.y -= 10;
	}
	if (padState & PAD_INPUT_DOWN)//�E
	{
		m_padPos.y += 10;
	}
}

void TitleCursor::Draw()
{
	//�I��
	DrawSelection();
	//�p�b�h�̃J�[�\����\��
	DrawPadCursor();
}
void TitleCursor::DrawPadCursor()
{
	DrawCircle(m_padPos.x, m_padPos.y, 20, 0x00ffff, false);
	// �`��u�����h���[�h���A���t�@�u�����h�i�T�O���j�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawCircle(m_padPos.x, m_padPos.y, 19, 0xffff00, true);
	// �`��u�����h���[�h���m�[�u�����h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
void TitleCursor::DrawSelection()
{

}