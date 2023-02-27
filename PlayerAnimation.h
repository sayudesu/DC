#pragma once
#include "Vec2.h"

class PlayerAnimation
{
public:

	PlayerAnimation();
	 virtual~PlayerAnimation();

	 void Update();
	 void Draw();

public:

	//�摜
	void SetHandle(int handle) { m_hPlayer = handle; }//�v���C���[�摜
	void SetHandleIdle(int handle) { m_hPlayerIdle = handle; }//�v���C���[�摜(�A�C�h�����)

	void GetPosLeft(int pos) { m_pos.x = pos; }//�v���C���[�̈ʒu���W���擾
	void GetPosTop(int pos) { m_pos.y = pos; }//�v���C���[�̈ʒu���W���擾
	void GetPosY(int y) { m_posY = y; }//�v���C���[��Y�ʒu���W���擾

private:

	int m_hPlayer;//�v���C���[�摜
	int m_hPlayerIdle;//�v���C���[�摜�i�A�C�h����ԁj
	
	int m_posY;

	Vec2 m_pos;

};

