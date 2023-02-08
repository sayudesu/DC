#pragma once
#include "Vec2.h"

class Enemy
{
public:
	Enemy();
	virtual~Enemy();

	virtual void Init();
	virtual void End();
	virtual void Update();
	virtual void Draw();

	void SetHandle(int handle);

	Vec2 GetSize() { return m_size; }
	Vec2 GetSizeBottom() { return m_sizeBottom; }

	Vec2 GetSizeHit() { return m_sizeHit; }
	Vec2 GetSizeBottomHit() { return m_sizeBottomHit; }

private:
	//�G�A�C
	void EyeEnemy();
	//�G�ˌ�
	void ShotEnemy();
	void ShotEnemyDraw();
	//���
	void Condition();


private:
	//�O���t�B�b�N�n���h��
	int m_handle;
	int m_eyeImagePos;
	//�A�j���[�V�����t���[���J�E���g
	int m_frameCount;
	//�G�l�~�[�̌��Ă������
	bool m_direction;
	//�����Ă��邩
	bool m_isRunMove;
	//�G�l�~�[�̈ʒu
	Vec2 m_pos;
	Vec2 m_vec;
	//�G�l�~�[�̃T�C�Y
	Vec2 m_size;
	Vec2 m_sizeBottom;
	//�G�l�~�[�U���󂯔͈�
	Vec2 m_sizeHit;
	Vec2 m_sizeBottomHit;
	//�V���b�g�G�l�~�[�ʒu
	Vec2 m_shotEnemyPos;
	Vec2 m_shotEnemyBottomPos;

};

