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
	
	void BarrelMove();//樽の動き

	void fireBallMove();//樽の動き

	void npcPos();//敵のキャラ取得
public:

	int  GetLeft()   { return m_posLeft;   }
	int  GetTop()    { return m_posTop;    }
	int  GetRight()  { return m_posRight;  }
	int  GetBottom() { return m_posBottom; }
	//樽
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

	int m_fall;//地面との判定

	int m_ladderNum;

	float m_getPos;//y軸固定座標

	bool m_isFirstMove;//初動動作

	bool m_isCourse;

	Vec2 m_pos;
	Vec2 m_barrelPos;//樽
	Vec2 m_vec;


};

