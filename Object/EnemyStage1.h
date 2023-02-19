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

	void falleMove();//�ǂ����񓮂�

	void npcPos();//�G�̃L�������W�擾

public:

	//�t�@�C�A�[�{�[��
	int  GetLeft()   { return m_posLeft;   }
	int  GetTop()    { return m_posTop;    }
	int  GetRight()  { return m_posRight;  }
	int  GetBottom() { return m_posBottom; }
	//�M
	int  GetBarrelLeft  () { return m_barrelLeft;   }
	int  GetBarrelTop   () { return m_barrelTop;    }
	int  GetBarrelRight () { return m_barrelRight;  }
	int  GetBarrelBottom() { return m_barrelBottom; }
	//�ǂ�����
	int  GetFallenLeft  () { return m_fallenLeft;   }
	int  GetFallenTop   () { return m_fallenTop;    }
	int  GetFallenRight () { return m_fallenRight;  }
	int  GetFallenBottom() { return m_fallenBottom; }
	//�ǂ�����͈�
	int  GetFallenRangeLeft  () { return m_fallenRangeLeft;   }
	int  GetFallenRangeTop   () { return m_fallenRangeTop;    }
	int  GetFallenRangeRight () { return m_fallenRangeRight;  }
	int  GetFallenRangeBottom() { return m_fallenRangeBottom; }
	
public:

	void GetHitFall(int fall  ) { m_fall = fall; }
	void GetPos    (float posY) { m_getPos = posY; }

	void GetHitFireBallFall(int fall  ) { m_fallFireBall = fall; }
	void GetFireBallPos    (float posY) { m_getFireBallPos = posY; }

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

	int m_fallenLeft;
	int m_fallenTop;
	int m_fallenRight;
	int m_fallenBottom;

	int m_fallenRangeLeft;
	int m_fallenRangeTop;
	int m_fallenRangeRight;
	int m_fallenRangeBottom;

	int m_fall;//�n�ʂƂ̔���
	int m_fallFireBall;//�n�ʂƂ̔���

	int m_ladderNum;
	float m_getPos;//y���Œ���W
	int m_getFireBallPos;//y���Œ���W

	bool m_isFirstMove;//��������

	bool m_isCourse;//��������
	bool m_isFireBallCourse;//��������

	Vec2 m_pos;//�t�@�C�A�[�{�[��
	Vec2 m_barrelPos;//�M
	Vec2 m_fallenPos;//�h�b�X���I�Ȃ��
	Vec2 m_vec;


};

