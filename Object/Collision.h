#pragma once
#include "Vec2.h"

class PlayerNew;
class DrawMapStage2;
class EnemyStage1;
class Collision
{
public:
	Collision();
	~Collision();

	void Init();
	void Update();
	void Draw();

//�����蔻��
public:
	bool HitObject();//�n�ʂƂ̓����蔻��
	bool HItLadder();//��q�Ƃ̓����蔻��
	bool HitPlayer();//�v���C���[�ƓG�̓����蔻��
	bool HitGoal();//�S�[���Ƃ̔���

    int HitEnemyObject();//�G�ƒn�ʂƂ̓����蔻��
	int HItEnemyLadder();//��q�ƃG�l�~�[�̓����蔻��

	int HitEnemyFireBall();//�����ƒn�ʂ̓����蔻��
	bool HitEnemy();//�v���C���[�ƓG�̓����蔻��

	int HitFallenRange();//������G�͈̔�
	bool HitFallen();//�������ƃv���C���[�̔���

	bool HitCharge();//�ǐՂ���G�ƃv���C���[�̔���
//�n��
public:
	float GetPos () { return m_posY; }
	void GetGoal(bool stageClear) { m_isStageClear = stageClear; }
	bool m_isStageClear;
	//void  GetGoal2() { m_pPlayer->GetGameClear(); }
private:

	float m_posY;//�v���C���[��Y���W
	float m_enemyPosY;//�v���C���[��Y���W
	int m_enemyFireBallPosY;//�v���C���[��Y���W

	float m_landingPos;//���n�ʒu

	bool m_isPlayerPos;


	PlayerNew* m_pPlayer;
	DrawMapStage2* m_pMap;
	EnemyStage1* m_pEnemy;
};

