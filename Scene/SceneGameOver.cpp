#include <Dxlib.h>
#include "game.h"
#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneMain2.h"
#include "TitleCursorGame.h"
#include "GameSceneCollision.h"

SceneGameOver::SceneGameOver():
	m_color1(0),//�I����ʂ̐F
	m_color2(0),
	m_color3(0),
	m_pCursor(nullptr),//�J�[�\���\���p
	m_pCursorCollision(nullptr)//�J�[�\�������蔻��
{
	m_pCursor = new TitleCursorGame;
	m_pCursorCollision = new GameSceneCollision;
}

SceneGameOver::~SceneGameOver()
{
	delete m_pCursor;
	delete m_pCursorCollision;
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

	m_pCursor->Update();//�J�[�\���̍X�V����
	m_pCursorCollision->Update();//�J�[�\���ƑI��͈͂̓����蔻��

	//�J�[�\�����������Ă��Ȃ��ꍇ�̕����w�i�̐F
	m_color2 = Color::kWhite;
	m_color3 = Color::kWhite;

	if (m_pCursorCollision->CollsionStage1())//�J�[�\���ƑI��͈͂ɓ������Ă�����
	{
		m_color2 = Color::kRed;//�J�[�\�����������Ă���ꍇ�̕����w�i�̐F
		if (padState & PAD_INPUT_2)//X�{�^��
		{
			return(new SceneMain2);//�����X�e�[�W���J��Ԃ�
		}
	}
	if (m_pCursorCollision->CollsionEnd())//�J�[�\���ƑI��͈͂ɓ������Ă�����
	{
		m_color3 = Color::kRed;//�J�[�\�����������Ă���ꍇ�̕����w�i�̐F
		if (padState & PAD_INPUT_2)//X�{�^��
		{
			return(new SceneTitle);//�^�C�g����ʂɈړ�
		}
	}

	return this;
}

void SceneGameOver::Draw()
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(500, 300, Game::kScreenWidth - 500, Game::kScreenHeight - 300, 0x00ffff, true);//��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(500, 300, Game::kScreenWidth - 500, Game::kScreenHeight - 300, 0xffffff, false);//�g�g��

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//�F�𔖂�����
	//DrawBox(SceneSelect::kSelectLeft, SceneSelect::kSelectTop, SceneSelect::kSelectRight, SceneSelect::kSelectBottom, m_color1, true);
	DrawBox(SceneSelect::kSelectLeft2, SceneSelect::kSelectTop2, SceneSelect::kSelectRight2, SceneSelect::kSelectBottom2, m_color2, true);
	DrawBox(SceneSelect::kSelectLeft3, SceneSelect::kSelectTop3, SceneSelect::kSelectRight3, SceneSelect::kSelectBottom3, m_color3, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�F��߂�

	DrawString(SceneSelect::kSelectLeft + 75, SceneSelect::kSelectTop + 5, "You Died.", Color::kRed);
	DrawString(SceneSelect::kSelectLeft2 + 100, SceneSelect::kSelectTop2 + 5, "Retry", Color::kBlue);
	DrawString(SceneSelect::kSelectLeft3 + 75, SceneSelect::kSelectTop3 + 5, "Back to Title", Color::kBlue);

	m_pCursor->Draw();
}
