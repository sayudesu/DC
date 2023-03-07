#include "SceneMain2.h"
#include "SceneMain3.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "SceneGameOver.h"
#include "DrawMapStage1.h"
#include "PlayerNew.h"
#include "Collision.h"
#include "SelectMenu.h"
#include "TitleCursorGame.h"
#include "GameSceneCollision.h"
#include "game.h"
#include "Image.h"
#include <Dxlib.h>
#include "Pad.h"

SceneMain2::SceneMain2():
	m_hPlayer(-1),
	m_hPlayerIdle(-1),
	m_hPlayerLighting(-1),
	m_hPlayerHealthBer(-1),
	m_hMusicBgm1(-1),
	m_hSoundSelect(-1),//�{�^���������ꍇ�̃T�E���h
	m_hSoundSelect2(-1),//�{�^���������ꍇ�̃T�E���h
	m_soundCount(-1),//�T�E���h�Đ��܂ł̃J�E���g
	m_soundCount2(-1),//�T�E���h�Đ��܂ł̃J�E���g
	m_soundCount3(-1),
	m_color1(0),//�I����ʂ̐F
	m_color2(0),
	m_color3(0),
	m_fadeValue(0.0f),
	m_isFadeIn(false),//�t�F�C�h�C���������ǂ���
	m_isFadeOut(false),//�t�F�C�h�A�E�g�������ǂ���
	m_isSceneStage(false),//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	m_isSceneRetry(false),
	m_isSceneTitle(false),//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	m_isGameClear(false),//�Q�[�����N���A�����ꍇ
	m_isSceneDead(false),//���񂾂�V�[���؂�ւ�
	m_pStage(nullptr),
	m_pPlayer(nullptr),
	m_pCollision(nullptr),
	m_pMenu(nullptr),
	m_pCursor(nullptr),
	m_pCursorCollision(nullptr)
{

	m_pStage     = new DrawMapStage1;
	m_pPlayer    = new PlayerNew;
	m_pCollision = new Collision;
	m_pMenu      = new SelectMenu;
	m_pCursor    = new TitleCursorGame;
	m_pCursorCollision = new GameSceneCollision;
}

SceneMain2::~SceneMain2()
{
	delete m_pStage;
	delete m_pPlayer;
	delete m_pCollision;
	delete m_pMenu;
	delete m_pCursorCollision;

	//�T�E���h�폜
	DeleteSoundMem(m_hSoundSelect);
	DeleteSoundMem(m_hSoundSelect2);
}

void SceneMain2::Init()
{
	//m_pPlayer->Init();
	m_pCollision->Init();
	m_pStage->Init();
	//m_pEnemy->Init();

	// �Đ��`�����t�@�C������X�g���[���Đ�����A�ɐݒ�
	//SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
	m_hMusicBgm1 = LoadSoundMem(FX::kBgm2);
	m_hSoundSelect = LoadSoundMem(FX::kSelect);//�{�^���������ꍇ�̃T�E���h��ǂݍ���
	m_hSoundSelect2 = LoadSoundMem(FX::kSelect2);//�{�^���������ꍇ�̃T�E���h��ǂݍ���
	ChangeVolumeSoundMem(255 / 3 , m_hMusicBgm1);

	//�v���C���[�摜
	//m_hPlayer = LoadGraph(Image::kPlayerImage);
	//m_hPlayerIdle = LoadGraph(Image::kPlayerImageIdle);
	m_hPlayerLighting = LoadGraph(Image::kPlayerLighting);
	m_hPlayerHealthBer = LoadGraph(Image::kPlayerHealthBer);

	//�v���C���[�摜
	m_pPlayer->SetHandle(m_hPlayer);
	m_pPlayer->SetHandleIdle(m_hPlayerIdle);

	m_fadeValue = 255.0f;

}

void SceneMain2::End()
{
	m_pPlayer->End();
	m_pStage->End();

	//m_pEnemy->End();
	//�v���C���[�摜
	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hPlayerIdle);

	DeleteSoundMem(m_hMusicBgm1);
}

SceneBase* SceneMain2::Update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (!m_isFadeIn)FadeIn();//�t�F�C�h�C��
	
	if (m_isFadeIn)//��ʂ��ő�l���邭�Ȃ�����
	{
		if (!m_isGameClear)//�N���A���Ă��Ȃ��ꍇ�͏�������
		{
			if (!m_pMenu->m_isMenu)
			{
				m_pCollision->Update();
			}
		}

		m_pMenu->Update();


		if (m_pCollision->m_isStageClear)//�X�e�[�W���N���A�����ꍇ
		{
			m_isGameClear = true;
			//return(new SceneMain3);
		}

		if (m_pCollision->m_isDeadSceneChange)//�G��g���b�v�ɓ������Ď��񂾏ꍇ
		{
			//printfDx("�G��g���b�v�ɓ������Ď���");
			m_isSceneDead = true;//����
		}

		if (m_isGameClear)//�Q�[�����N���A������
		{
			m_pCursor->Update();//�J�[�\���̍X�V����
			m_pCursorCollision->Update();//�J�[�\���ƑI��͈͂̓����蔻��

			//�J�[�\�����������Ă��Ȃ��ꍇ�̕����w�i�̐F
			m_color1 = Color::kWhite;
			m_color2 = Color::kWhite;
			m_color3 = Color::kWhite;

			if (m_pCursorCollision->CollsionDemo())//�J�[�\���ƑI��͈͂ɓ������Ă�����
			{
				m_soundCount++;//�T�E���h�Đ��܂ł̃J�E���g
				if (m_soundCount == 1)
				{
					PlaySoundMem(m_hSoundSelect2, DX_PLAYTYPE_BACK);//�����Ă��鉹���Đ�
				}
				m_color1 = Color::kRed;//�J�[�\�����������Ă���ꍇ�̕����w�i�̐F
				if (padState & PAD_INPUT_2)//X�{�^��
				{
					m_isSceneStage = true;
				}
			}
			else//�J�[�\�����I��͈͊O��������
			{
				m_soundCount = 0;//�T�E���h�J�E���g�����Z�b�g
			}
			if (m_pCursorCollision->CollsionStage1())//�J�[�\���ƑI��͈͂ɓ������Ă�����
			{
				m_soundCount2++;//�T�E���h�Đ��܂ł̃J�E���g
				m_color2 = Color::kRed;//�J�[�\�����������Ă���ꍇ�̕����w�i�̐F
				if (m_soundCount2 == 1)
				{
					PlaySoundMem(m_hSoundSelect2, DX_PLAYTYPE_BACK);//�����Ă��鉹���Đ�
				}
				if (padState & PAD_INPUT_2)//X�{�^��
				{
					m_isSceneRetry = true;
				}
			}
			else//�J�[�\�����I��͈͊O��������
			{
				m_soundCount2 = 0;//�T�E���h�J�E���g�����Z�b�g
			}
			if (m_pCursorCollision->CollsionEnd())//�J�[�\���ƑI��͈͂ɓ������Ă�����
			{
				m_soundCount3++;//�T�E���h�Đ��܂ł̃J�E���g
				m_color3 = Color::kRed;//�J�[�\�����������Ă���ꍇ�̕����w�i�̐F
				if (m_soundCount3 == 1)
				{
					PlaySoundMem(m_hSoundSelect2, DX_PLAYTYPE_BACK);//�����Ă��鉹���Đ�
				}
				if (padState & PAD_INPUT_2)//X�{�^��
				{
					m_isSceneTitle = true;
				}
			}
			else//�J�[�\�����I��͈͊O��������
			{
				m_soundCount3 = 0;//�T�E���h�J�E���g�����Z�b�g
			}
			Pad::update();
			if (Pad::isTrigger(PAD_INPUT_2))//X�{�^��
			{
				PlaySoundMem(m_hSoundSelect, DX_PLAYTYPE_BACK);//�����Ă��鉹���Đ�
			}
		}
	}


	if (m_isSceneTitle)//�I����������
	{
		FadeOut();
		if (m_isFadeOut)
		{
			return(new SceneTitle);//�^�C�g����ʂɈړ�
		}
	}
	else if (m_isSceneStage)
	{
		FadeOut();
		if (m_isFadeOut)
		{
			return(new SceneMain3);//�V�����X�e�[�W�Ɉړ�
		}
	}
	else if (m_isSceneRetry)
	{
		FadeOut();
		if (m_isFadeOut) 
		{
			return(new SceneMain2);//�����X�e�[�W���J��Ԃ�
		}
	}
	else if (m_isSceneDead)//���񂾏ꍇ�̃V�[���؂�ւ�
	{
		FadeOut();
		if (m_isFadeOut)
		{
			return(new SceneGameOver);
		}
	}

	if (CheckHitKey(KEY_INPUT_Z))//�ً}���^�C�g���ɖ߂�
	{
		return(new SceneTitle);
	}
	return this;
}

void SceneMain2::Draw()
{
	m_pStage->Draw();//�X�e�[�W��`��
	//�v���C���[�A�G�l�~�[��\��
	m_pCollision->Draw();
	if (m_pMenu->m_isMenu)
	{
		m_pMenu->Draw();

	}
	if (m_isGameClear)//�Q�[�����N���A�����ꍇ
	{
		GameClear();//�ǂ̉�ʂɈړ����邩�m�F
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeValue);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	/*
	//���H�p�X�N���[���n���h�����Z�b�g����
	SetDrawScreen(m_hTempScreen);

	m_pStage->Draw();//�X�e�[�W��`��

	//�v���C���[�A�G�l�~�[��\��
	m_pCollision->Draw();

	m_timer = GetRand(1000);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, m_hTempScreen, false);

	if (m_timer == 500)
	{
		GraphFilter(m_hTempScreen, DX_GRAPH_FILTER_GAUSS, 16, 1400);

		SetDrawBlendMode(DX_BLENDMODE_ADD, 192);

		DrawGraph(m_timer, 0, m_hTempScreen, false);
		GraphFilter(m_hTempScreen, DX_GRAPH_FILTER_GAUSS, 32, 1400);
		DrawGraph(m_timer, 0, m_hTempScreen, false);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	*/
}

//�N���A�������̑I����ʕ\��
void SceneMain2::GameClear()
{
	//�w�i
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(500, 300, Game::kScreenWidth - 500, Game::kScreenHeight - 300, 0x00ffff, true);//��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(500, 300, Game::kScreenWidth - 500, Game::kScreenHeight - 300, 0xffffff, false);//�g�g��
	//�����w�i
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//�F�𔖂�����
	DrawBox(SceneSelect::kSelectLeft,SceneSelect::kSelectTop,SceneSelect::kSelectRight,SceneSelect::kSelectBottom, m_color1, true);
	DrawBox(SceneSelect::kSelectLeft2, SceneSelect::kSelectTop2, SceneSelect::kSelectRight2, SceneSelect::kSelectBottom2, m_color2, true);
	DrawBox(SceneSelect::kSelectLeft3, SceneSelect::kSelectTop3, SceneSelect::kSelectRight3, SceneSelect::kSelectBottom3, m_color3, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�F��߂�
	//����
	DrawString(SceneSelect::kSelectLeft + 75, SceneSelect::kSelectTop    + 5 , "Next Sgage", 0x0000ff);
	DrawString(SceneSelect::kSelectLeft2 + 100, SceneSelect::kSelectTop2 + 5,  "Retry", 0x0000ff);
	DrawString(SceneSelect::kSelectLeft3 + 75, SceneSelect::kSelectTop3  + 5,  "Back to Title", 0x0000ff);

	m_pCursor->Draw();
}

void SceneMain2::FadeIn()
{
	m_fadeValue -= Scene::kFadeSpeed;
	if (m_fadeValue <= 0)
	{
		m_isFadeIn = true;//��ʂ��ő�ɖ��邭
	}
}

void SceneMain2::FadeOut()
{
	m_fadeValue += Scene::kFadeSpeed;
	if (m_fadeValue >= 255)
	{
		m_isFadeOut = true;//��ʂ��ő�ɈÂ�
	}
}