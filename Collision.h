#pragma once

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
private:
	bool m_isGravity;
	PlayerNew* m_pPlayer;
	DrawMapStage2* m_pMap;
};

