#pragma once
#include "SceneBase.h"

class DrawMapStage1;
class PlayerNew;
class Collision;
class SelectMenu;
class TitleCursorGame;
class GameSceneCollision;

class SceneMain2 : public SceneBase
{
public:
	SceneMain2();
	virtual~SceneMain2();

	virtual void Init();
	virtual void End();
	virtual SceneBase* Update() override;
	virtual void Draw();
private:
	void GameClear();//�Q�[�����N���A�����ꍇ
private:
	void FadeIn();//�t�F�C�h�C��
	void FadeOut();//�t�F�C�h�A�E�g
private:

	//�v���C���[�摜
	int m_hPlayer;
	int m_hPlayerIdle;
	int m_hPlayerLighting;
	int m_hPlayerHealthBer;
	//�T�E���h�n���h��
	int m_hSoundSelect;//�{�^�����������ꍇ�̃T�E���h
	int m_hSoundSelect2;
	int m_soundCount;//�T�E���h�Đ��܂ł̃J�E���g
	int m_soundCount2;
	int m_soundCount3;
	int m_color1;//�I����ʂ̐F
	int m_color2;
	int m_color3;

	float m_fadeValue;//��ʂ̖��邳����

	bool m_isFadeIn;//�t�F�C�h�C���������ǂ���
	bool m_isFadeOut;//�t�F�C�h�A�E�g�������ǂ���

	bool m_isSceneStage;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	bool m_isSceneRetry;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	bool m_isSceneTitle;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	bool m_isSceneDead;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�


	int m_hMusicBgm1;

	bool m_isGameClear;

	DrawMapStage1* m_pStage;
	PlayerNew* m_pPlayer;
	Collision* m_pCollision;
	SelectMenu* m_pMenu;
	TitleCursorGame* m_pCursor;
	GameSceneCollision* m_pCursorCollision;
};



