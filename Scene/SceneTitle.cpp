#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneMain2.h"
#include "SceneMain3.h"
#include "SceneResult.h"
#include "TitleCursor.h"
#include "TitleCollision.h"
#include <DxLib.h>
#include "game.h"
#include "Image.h"
#include <Pad.h>

namespace
{
	constexpr int kAnimationFrame = 3;
	constexpr int kCharaImageRightPos = 112; //�E�ړ�

	constexpr int kColorWhite = 0x000000;//���F
	constexpr int kColorRed = 0xff0000;//�ԐF

}

SceneTitle::SceneTitle():
	m_hImagePlayer(-1),
	m_hImageMap(-1),
	m_charaImagePos(0),
	m_hMusicBgm1(-1),
	m_hButtonUi(-1),
	m_hSoundSelect(-1),
	m_hSoundSelect2(-1),
	m_colorA(0),
	m_colorX(0),
	m_frameCount(0),
	m_soundCount1(0),
	m_soundCount2(0),
	m_soundCount3(0),
	m_sceneChangeCountDemo(0),
	m_sceneChangeCountStage1(0),
	m_sceneChangeCountEnd(0),
	m_buttonALeft(0),
	m_buttonATop(0),
	m_buttonARigth(0),
	m_buttonABottom(0),
	m_buttonXLeft(0),
	m_buttonXTop(0),
	m_buttonXRigth(0),
	m_buttonXBottom(0),
	m_imagePos(0.0f,0.0f),
	m_isSceneFocus1(false),
	m_isSceneFocus2(false),
	m_isSceneFocus3(false),
	m_pCursor(nullptr),
	m_pCollsion(nullptr)
{
	m_pCursor = new TitleCursor;
	m_pCollsion = new TitleCollision;
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_hImagePlayer);
	DeleteGraph(m_hImageMap);
	DeleteGraph(m_hButtonUi);

	DeleteSoundMem(m_hMusicBgm1);
	DeleteSoundMem(m_hSoundSelect);
	DeleteSoundMem(m_hSoundSelect2);
}

void SceneTitle::Init()
{
	m_hImagePlayer = LoadGraph(Image::kPlayerImage);
	m_hImageMap    = LoadGraph(Image::kMapFirst);
	m_hButtonUi = LoadGraph(UI::kButton);
	m_hMusicBgm1 = LoadSoundMem(FX::kBgm1);
	m_hSoundSelect = LoadSoundMem(FX::kSelect);
	m_hSoundSelect2 = LoadSoundMem(FX::kSelect2);
	PlaySoundMem(m_hMusicBgm1, DX_SOUNDTYPE_STREAMSTYLE);
	// ���ʂ̐ݒ�
	ChangeVolumeSoundMem(255 / 3, m_hMusicBgm1);

	m_imagePos.x   = Game::kScreenWidth / 2;
	m_imagePos.y   = Game::kScreenHeight / 2 - 250;

	//A�{�^�������Ă��Ȃ���ԁi�摜�j
	m_buttonALeft = 16 + 16 + 16;
	m_buttonATop = 16 + 16;
	m_buttonARigth = 16;
	m_buttonABottom = 16 ;

	//X�{�^�������Ă��Ȃ���ԁi�摜�j
	m_buttonXLeft = 16 + 16 + 16;
	m_buttonXTop = 16 + 16 + 16;
	m_buttonXRigth = 16;
	m_buttonXBottom = 16;

	m_colorA = kColorWhite;
	m_colorX = kColorWhite;
	//m_charaImagePos = (1344 );
}
void SceneTitle::End()
{
	delete m_pCollsion;
	delete m_pCursor;
}

SceneBase* SceneTitle::Update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_pCursor->Update();
	m_pCollsion->Update();
	Pad::update();
	if (padState & PAD_INPUT_1)
	{
		if (Pad::isTrigger(PAD_INPUT_1))//A�{�^���������ꍇ
		{
			PlaySoundMem(m_hSoundSelect, DX_PLAYTYPE_BACK);//�����Ă��鉹���Đ�
			m_buttonALeft = 16 + 16 + 16 + 16 + 16;//�摜�\���ʒu��ύX
			m_colorA = kColorRed;//�����̐F��ύX
		}
	}
	else
	{
		m_buttonALeft = 16 + 16 + 16;//�摜�\���ʒu��ύX
		m_colorA = kColorWhite;//�����̐F��ύX
	}
	if (padState & PAD_INPUT_2)
	{
		if (Pad::isTrigger(PAD_INPUT_2))//X�{�^���������ꍇ
		{
			PlaySoundMem(m_hSoundSelect, DX_PLAYTYPE_BACK);//�����Ă��鉹���Đ�
			m_buttonXLeft = 16 + 16 + 16 + 16 + 16;//�摜�\���ʒu��ύX
			m_colorX = kColorRed;//�����̐F��ύX
		}
	}
	else
	{
		m_buttonXLeft = 16 + 16 + 16;//�摜�\���ʒu��ύX
		m_colorX = kColorWhite;//�����̐F��ύX
	}

	if (m_pCollsion->CollsionDemo())//�V�[���؂�ւ�::�`���[�g���A��
	{
		m_soundCount1++;
		if (m_soundCount1 == 1)
		{
			PlaySoundMem(m_hSoundSelect2, DX_PLAYTYPE_BACK);//�����Ă��鉹���Đ�
		}
		m_isSceneFocus1 = true;//�t�H�[�J�X�����킹���ꍇ
		if (padState & PAD_INPUT_2)
		{
			m_sceneChangeCountDemo += 5;//����������
			if (m_sceneChangeCountDemo == 300)//����������
			{
				m_sceneChangeCountDemo = 0;
				return(new SceneMain);//�V�[���؂�ւ�
				//return(new SceneResult);//�V�[���؂�ւ�
			}
		}
		else
		{
			m_sceneChangeCountDemo = 0;//����������߂��烁�[�^�[�����Z�b�g
		}
	}
	else
	{
		m_soundCount1 = 0;
		m_isSceneFocus1 = false;//�t�H�[�J�X���O�����ꍇ
		m_sceneChangeCountDemo = 0;//���[�^�[�����Z�b�g
	}

	if (m_pCollsion->CollsionStage1())//�V�[���؂�ւ�::�Q�[���v���C
	{
		m_soundCount2++;
		if (m_soundCount2 == 1)
		{
			PlaySoundMem(m_hSoundSelect2, DX_PLAYTYPE_BACK);//�����Ă��鉹���Đ�
		}
		m_isSceneFocus2 = true;//�t�H�[�J�X�����킹���ꍇ
		if (padState & PAD_INPUT_2)
		{
			m_sceneChangeCountStage1 += 5;//����������
			if (m_sceneChangeCountStage1 == 300)//����������
			{
				m_sceneChangeCountStage1 = 0;
				return(new SceneMain2);//�V�[���؂�ւ�
				return(new SceneMain3);//�V�[���؂�ւ�
			}
		}
		else
		{
			m_sceneChangeCountStage1 = 0;//����������߂��烁�[�^�[�����Z�b�g
		}
	}
	else
	{
		m_soundCount2 = 0;
		m_isSceneFocus2 = false;//�t�H�[�J�X���O�����ꍇ
		m_sceneChangeCountStage1 = 0;//���[�^�[�����Z�b�g
	}

	if (m_pCollsion->CollsionEnd())//�V�[���؂�ւ�::�f�X�N�g�b�v�ɖ߂�
	{
		m_soundCount3++;
		if (m_soundCount3 == 1)
		{
			PlaySoundMem(m_hSoundSelect2, DX_PLAYTYPE_BACK);//�����Ă��鉹���Đ�
		}
		m_isSceneFocus3 = true;//�t�H�[�J�X�����킹���ꍇ
		if (padState & PAD_INPUT_2)
		{
			m_sceneChangeCountEnd += 5;//����������
			if (m_sceneChangeCountEnd == 300)//����������
			{
				m_sceneChangeCountEnd = 0;
				DxLib_End();//�Q�[���I��
			}
		}
		else
		{
			m_sceneChangeCountEnd = 0;//����������߂��烁�[�^�[�����Z�b�g
		}
	}
	else
	{
		m_soundCount3 = 0;
		m_isSceneFocus3 = false;//�t�H�[�J�X���O�����ꍇ
		m_sceneChangeCountEnd = 0;//���[�^�[�����Z�b�g
	}


	//�E�Ɉړ��A�j���[�V����
	m_frameCount++;
	if (m_frameCount >= kAnimationFrame)
	{
		m_charaImagePos += kCharaImageRightPos;
		m_frameCount = 0;
	}
	if (m_charaImagePos == 1344)
	{
		m_charaImagePos = 0;
	}

	return this;
}

void SceneTitle::Draw()
{
	DrawExtendGraph(0 + 100, 0 + 100,Game::kScreenWidth  - 100, Game::kScreenHeight - 100,m_hImageMap,true);
	DrawRectRotaGraph(m_imagePos.x, m_imagePos.y,
		m_charaImagePos, 133, 112, 133, 18, 0, m_hImagePlayer, true, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);//����
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x0000ff, true);//�w�i
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//�F�𔖂�����
	//�`���[�g���A��
	DrawBox(TitleMenu::kSelection1X, TitleMenu::kSelection1Y, TitleMenu::kSelectionBottom1X, TitleMenu::kSelectionBottom1Y, 0xffffff, true);
	DrawBox(TitleMenu::kSelection1X, TitleMenu::kSelection1Y, TitleMenu::kSelectionBottom1X + m_sceneChangeCountDemo - 300
		, TitleMenu::kSelectionBottom1Y, 0xff0000, true);
	//�X�e�[�W1
	DrawBox(TitleMenu::kSelection2X, TitleMenu::kSelection2Y, TitleMenu::kSelectionBottom2X, TitleMenu::kSelectionBottom2Y, 0xffffff, true);
	DrawBox(TitleMenu::kSelection2X, TitleMenu::kSelection2Y, TitleMenu::kSelectionBottom2X + m_sceneChangeCountStage1 - 300
		, TitleMenu::kSelectionBottom2Y, 0xff0000, true);
	//�f�X�N�g�b�v�ɖ߂�
	DrawBox(TitleMenu::kSelection3X, TitleMenu::kSelection3Y, TitleMenu::kSelectionBottom3X, TitleMenu::kSelectionBottom3Y, 0xffffff, true);
	DrawBox(TitleMenu::kSelection3X, TitleMenu::kSelection3Y, TitleMenu::kSelectionBottom3X + m_sceneChangeCountEnd - 300
		, TitleMenu::kSelectionBottom3Y, 0xff0000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�F��߂�

	//�g�g�݁i�F�j
	DrawBox(TitleMenu::kSelection1X - 1, TitleMenu::kSelection1Y - 1, TitleMenu::kSelectionBottom1X + 1, TitleMenu::kSelectionBottom1Y + 1, 0x0000ff, false);
	DrawBox(TitleMenu::kSelection2X -1, TitleMenu::kSelection2Y - 1, TitleMenu::kSelectionBottom2X + 1, TitleMenu::kSelectionBottom2Y + 1, 0x0000ff, false);
	DrawBox(TitleMenu::kSelection3X - 1, TitleMenu::kSelection3Y - 1, TitleMenu::kSelectionBottom3X + 1, TitleMenu::kSelectionBottom3Y + 1, 0x0000ff, false);

	if (m_isSceneFocus1)//�t�H�[�J�X�����킹�������̘g�̐F��؂�ւ���i�ԐF�ɂ���j
	{
		DrawBox(TitleMenu::kSelection1X - 1, TitleMenu::kSelection1Y - 1, TitleMenu::kSelectionBottom1X + 1, TitleMenu::kSelectionBottom1Y + 1, 0xff00ff, false);
	}
	if (m_isSceneFocus2)
	{

		DrawBox(TitleMenu::kSelection2X - 1, TitleMenu::kSelection2Y - 1, TitleMenu::kSelectionBottom2X + 1, TitleMenu::kSelectionBottom2Y + 1, 0xff00ff, false);
	}
	if (m_isSceneFocus3)
	{
		DrawBox(TitleMenu::kSelection3X - 1, TitleMenu::kSelection3Y - 1, TitleMenu::kSelectionBottom3X + 1, TitleMenu::kSelectionBottom3Y + 1, 0xff00ff, false);
	}

	//����
	DrawString(TitleMenu::kSelection1X + 100, TitleMenu::kSelection1Y + 5 , "Tutorial", 0x0000ff);
	DrawString(TitleMenu::kSelection2X + 100, TitleMenu::kSelection2Y + 5, "GameStart", 0x0000ff);
	DrawString(TitleMenu::kSelection3X + 125, TitleMenu::kSelection3Y + 15, "Quit", 0x0000ff);
	SetFontSize(64);//�����T�C�Y�ύX
	DrawString(Game::kScreenWidth /2 - 250 + 5, Game::kScreenHeight / 2 - 150 + 5 , "Avoidance-Jump", 0x00000);//�^�C�g��
	DrawString(Game::kScreenWidth /2 - 250, Game::kScreenHeight/2 - 150, "Avoidance-Jump", 0xffff00);//�^�C�g��
	SetFontSize(17);//�����T�C�X�ύX

	//X
	DrawRectRotaGraph(200,200,
		m_buttonALeft, m_buttonATop, m_buttonARigth, m_buttonABottom, 5, 0, m_hButtonUi, true, false);
	DrawString(200 + 50, 200, "isAttack", m_colorA);
	//A
	DrawRectRotaGraph(230, 300,
		m_buttonXLeft, m_buttonXTop, m_buttonXRigth, m_buttonXBottom, 5, 0, m_hButtonUi, true, false);
	DrawString(230 + 50, 290, "isJump & Check", m_colorX);
	//�J�[�\���̈ʒu��`��
	m_pCursor->Draw();
}






