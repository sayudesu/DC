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
	bool HitGoal();//�S�[���Ƃ̔���
	bool HitEnemy();//�v���C���[�ƓG�̓����蔻��
//�n��
public:
	float GetPos() { return m_posY; }
private:

	float m_posY;//�v���C���[��Y���W

	float m_landingPos;//���n�ʒu

	PlayerNew* m_pPlayer;
	DrawMapStage2* m_pMap;
	EnemyStage1* m_pEnemy;
};

