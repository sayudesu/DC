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

private:
	//�O���t�B�b�N�n���h��
	int m_handle;

	//�G�l�~�[�̈ʒu
	Vec2 m_pos;
	Vec2 m_vec;
	//�G�l�~�[�̃T�C�Y
	Vec2 m_size;
	Vec2 m_sizeBottom;
};

