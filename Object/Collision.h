#pragma once

class PlayerMapMove;
class Enemy;
class Collision
{
public:
	Collision();
	virtual ~Collision();

	virtual void Init();
	virtual void End();

	virtual void Update();
	virtual void Draw();
public:
	//�G�ƃv���C���[�̒ʏ�q�b�g����
	bool PlayerEnemyHit(int firstLeft, int firstTop, int firstRight, int firstBottom,
		int SecondLeft, int SecondTop, int SecondRight, int SecondBottom);
private:
	PlayerMapMove* m_pPlayer;
	Enemy* m_pEnemy;
};

