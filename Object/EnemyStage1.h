#pragma once
#include "Vec2.h"

class EnemyStage1
{
public:
	EnemyStage1();
	~EnemyStage1();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	
	void BarrelMove();//�M�̓���

	void fireBallMove();//�M�̓���

	void npcPos();//�G�̃L�����擾
public:

	int  GetLeft()   { return m_posLeft;   }
	int  GetTop()    { return m_posTop;    }
	int  GetRight()  { return m_posRight;  }
	int  GetBottom() { return m_posBottom; }
	//�M
	int  GetBarrelLeft  () { return m_barrelLeft;   }
	int  GetBarrelTop   () { return m_barrelTop;    }
	int  GetBarrelRight () { return m_barrelRight;  }
	int  GetBarrelBottom() { return m_barrelBottom; }
	

public:

	void GetHitFall(int fall) { m_fall = fall; }

	void GetPos(float posY) { m_getPos = posY; }

	void GetEnemyLadder(int num) { m_ladderNum = num; }

private:
	int m_posLeft;
	int m_posTop;
	int m_posRight;
	int m_posBottom;

	int m_barrelLeft;
	int m_barrelTop;
	int m_barrelRight;
	int m_barrelBottom;

	int m_fall;//�n�ʂƂ̔���

	int m_ladderNum;

	float m_getPos;//y���Œ���W

	bool m_isFirstMove;//��������

	bool m_isCourse;

	Vec2 m_pos;
	Vec2 m_barrelPos;//�M
	Vec2 m_vec;


};

