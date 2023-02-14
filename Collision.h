#pragma once
#include "Vec2.h"

class PlayerNew;
class DrawMapStage2;
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

//�n��
public:
	bool GetGravity() { return m_isGravity; }

	float GetPos() { return m_posY; }
private:
	bool m_isGravity;

	float m_posY;

	float m_landingPos;//���n�ʒu

	PlayerNew* m_pPlayer;
	DrawMapStage2* m_pMap;
};

