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
	bool HitObject();//�I�u�W�F�N�g�Ƃ̓����蔻��
	void Draw();
public:
	bool GetGravity() { return m_isGravity; }

	float GetPos() { return m_posY; }
private:
	bool m_isGravity;

	float m_posY;

	PlayerNew* m_pPlayer;
	DrawMapStage2* m_pMap;
};

