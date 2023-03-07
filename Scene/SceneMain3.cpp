#include "SceneMain3.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "SceneGameOver2.h"
#include "DrawMapStage2.h"
#include "PlayerNew.h"
#include "Collision2.h"
#include "SelectMenu.h"
#include "game.h"
#include "Image.h"
#include <Dxlib.h>

SceneMain3::SceneMain3():
	m_hPlayer(-1),
	m_hPlayerIdle(-1),
	m_hPlayerLighting(-1),
	m_hPlayerHealthBer(-1),
	m_hEnemyFireBall(-1),
	m_hMusicBgm1(-1),
	m_pStage(nullptr),
	m_pPlayer(nullptr),
	m_pCollision(nullptr),
	m_pMenu(nullptr)
{
	m_pStage     = new DrawMapStage2;
	m_pPlayer    = new PlayerNew;
	m_pCollision = new Collision2;
	m_pMenu      = new SelectMenu;
}

SceneMain3::~SceneMain3()
{
	delete m_pStage;
	delete m_pPlayer;
	delete m_pCollision;
	delete m_pMenu;
}

void SceneMain3::Init()
{
	
	m_pCollision->Init();
	m_pStage->Init();

	m_hMusicBgm1 = LoadSoundMem(FX::kBgm2);

	// ���ʂ̐ݒ�
	ChangeVolumeSoundMem(255 / 3 , m_hMusicBgm1);

	m_hPlayerLighting = LoadGraph(Image::kPlayerLighting);
	m_hPlayerHealthBer = LoadGraph(Image::kPlayerHealthBer);
	//�G�l�~�[�摜
	m_hEnemyFireBall = LoadGraph(Image::kEnemyFireBall);

	//�v���C���[�摜
	m_pPlayer->SetHandle(m_hPlayer);
	m_pPlayer->SetHandleIdle(m_hPlayerIdle);
}

void SceneMain3::End()
{
	m_pPlayer->End();
	m_pStage->End();

	//m_pEnemy->End();
	//�v���C���[�摜
	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hPlayerIdle);
	//�G�l�~�[�摜
	DeleteGraph(m_hEnemyFireBall);

	DeleteSoundMem(m_hMusicBgm1);
}

SceneBase* SceneMain3::Update()
{
	if (!m_pMenu->m_isMenu)//���j���[���J���Ė���������
	{
		m_pCollision->Update();
	}

	m_pMenu->Update();//���j���[�̏�Ԃ��X�V���Ȃ���m�F

	if (m_pCollision->m_isStageClear)//�X�e�[�W���N���A�����ꍇ
	{
		return(new SceneResult);
	}

	if (m_pCollision->m_isDeadSceneChange)//�G��g���b�v�ɓ������Ď��񂾏ꍇ
	{
		printfDx("�G��g���b�v�ɓ������Ď���");
		return(new SceneGameOver2);
	}

	if (CheckHitKey(KEY_INPUT_Z))
	{
		return(new SceneTitle);
	}
	return this;
}

void SceneMain3::Draw()
{
	m_pStage->Draw();//�X�e�[�W��`��
	//�v���C���[�A�G�l�~�[��\��
	m_pCollision->Draw();

	if (m_pMenu->m_isMenu)
	{
		m_pMenu->Draw();

	}
}