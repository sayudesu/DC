#pragma once
#include "SceneBase.h"

class DrawMapStage2;
class PlayerNew;
class Collision3;
class SelectMenu;

class SceneMain4 : public SceneBase
{
public:
	SceneMain4();
	virtual~SceneMain4();

	virtual void Init();
	virtual void End();
	virtual SceneBase* Update() override;
	virtual void Draw();
private:
	void FadeIn();//�t�F�C�h�C��
	void FadeOut();//�t�F�C�h�A�E�g
private:
	//�v���C���[�摜
	int m_hPlayer;
	int m_hPlayerIdle;
	int m_hPlayerLighting;
	int m_hPlayerHealthBer;
	//�G�l�~�[�摜
	int m_hEnemyFireBall;

	int m_hMusicBgm;

	float m_fadeValue;//��ʂ̖��邳����

	bool m_isFadeIn;//�t�F�C�h�C���������ǂ���
	bool m_isFadeOut;//�t�F�C�h�A�E�g�������ǂ���

	bool m_isSceneResult;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	bool m_isSceneRetry;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	bool m_isSceneTitle;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	bool m_isSceneDead;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	bool m_isGameClear;

	DrawMapStage2* m_pStage;
	PlayerNew* m_pPlayer;
	Collision3* m_pCollision;
	SelectMenu* m_pMenu;
};



