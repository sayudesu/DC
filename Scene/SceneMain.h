#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <vector>


class PlayerMapMove;
//class Player;
class Enemy;

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();


	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();
private:
	void FadeIn();
	void FadeOut();
public:
	bool Check(int firstLeft,int firstTop,int firstRight,int firstBottom,
		int SecondLeft, int SecondTop, int SecondRight, int SecondBottom);
private:
	//MakeScreen�e�X�g
	int m_test;

	int m_hPlayer;
	int m_hPlayerIdle;
	int m_hPlayerLighting;
	int m_hPlayerHealthBer;
	int m_hEnemy;

	int m_hMapFirst;
	int m_hMapSecond;
	int m_hMapThird;
	int m_hMapFourth;
	int m_hMapFifth;
	int m_hMapChip;
	int m_hMapChipSecond;

	float m_fadeValue;//���邳�����p

	bool m_isFadeIn;//�t�F�C�h�C���������ǂ���
	bool m_isFadeOut;//�t�F�C�h�A�E�g�������ǂ���

	bool m_isSceneStage;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	bool m_isSceneEnd;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�

	PlayerMapMove* m_pPlayer;
	Enemy* m_pEnemy;

};
