#include <Dxlib.h>
#include "Fireworks.h"
#include "Image.h"
#include "game.h"

Fireworks::Fireworks() :
	m_hFireworks(), m_hFireworksRocket(),//�ԉΗp�摜�n���h��
	m_fireworksImagePosX(), m_fireworksImagePosY(),//�ԉΕ`��ʒu
	m_fireworksImageRocketLeft(0), m_fireworksImageRocketTop(0),//�ԉΉ摜�ʒu
	m_fireworksImageRocketRight(0), m_fireworksImageRocketBottom(0),
	m_fireworksImageLeft(0), m_fireworksImageTop(0),//�ԉΉ摜�ʒu
	m_fireworksImageRight(0), m_fireworksImageBottom(0),
	m_frameCount(0),
	m_isFireRocket(false), m_isFire(false)
{
	m_hFireworks[9] = { };
	m_hFireworksRocket[2] = {};

	m_fireworksImagePosX[0] = GetRand(Game::kScreenWidth - 300) + 300;
	m_fireworksImagePosY[0] = Game::kScreenHeight;

	m_fireworksImagePosX[1] = GetRand(Game::kScreenWidth - 300) + 300;
	m_fireworksImagePosY[1] = Game::kScreenHeight;

	m_fireworksImageRocketRight = 7;
	m_fireworksImageRocketBottom = 51;

	m_fireworksImageRight = 96;
	m_fireworksImageBottom = 100;

	m_isFireRocket = true;

	m_hFireworksRocket[0] = LoadGraph(Image::RocketBlue);
	m_hFireworksRocket[1] = LoadGraph(Image::RocketOrange);

	m_hFireworks[0] = LoadGraph(Image::LongOrange);
	m_hFireworks[1] = LoadGraph(Image::LongGreen);
	m_hFireworks[2] = LoadGraph(Image::LongBlue);
	m_hFireworks[3] = LoadGraph(Image::DefaultOrange);
	m_hFireworks[4] = LoadGraph(Image::DefaultGreen);
	m_hFireworks[5] = LoadGraph(Image::DefaultBlue);
	m_hFireworks[6] = LoadGraph(Image::CrystalsOrange);
	m_hFireworks[7] = LoadGraph(Image::CrystalsGreen);
	m_hFireworks[8] = LoadGraph(Image::CrystalsBlue);
}

Fireworks::~Fireworks()
{
	for (int i = 0; i <= 11; i++)
	{
		DeleteGraph(m_hFireworks[i]);
	}
}

void Fireworks::Init()
{
}

void Fireworks::End()
{
}

void Fireworks::Update()
{

	m_frameCount++;

	if (m_frameCount == 2)
	{
		m_frameCount = 0;

		for (int i = 0; i <= 1; i++)
		{
			if (m_fireworksImagePosY[i] >= 500)//�j��ꏊ
			{
				m_fireworksImagePosY[i] -= 15;
			}
			else
			{
				//m_fireworksImagePosY = Game::kScreenHeight;//�����l�ɖ߂�
				m_isFire = true;//�ԉ΂�\��
				m_isFireRocket = false;//�ł��グ���\��
			}
		}
	}
	if (m_isFire)
	{
		if (m_fireworksImageLeft <= 5766)m_fireworksImageLeft += 93;//�ԉ�
		else
		{
			for (int  i = 0; i <= 1; i++)
			{
				m_fireworksImagePosX[i] = GetRand(Game::kScreenWidth - 300) + 300;//�ԉΈʒu��ύX
			}
			m_fireworksImageLeft = 96;
		}

	}

	if (m_fireworksImageRocketLeft <= 280)m_fireworksImageRocketLeft += 7;//�ԉ΃��P�b�g
	else
	{
		m_fireworksImageRocketLeft = 7;
	}
	
	
}

void Fireworks::Draw()
{
	for (int i = 0; i <= 2; i++)
	{
		if (m_isFireRocket)
		{
			DrawRectRotaGraph(m_fireworksImagePosX[i], m_fireworksImagePosY[i],
				m_fireworksImageRocketLeft, m_fireworksImageRocketTop, m_fireworksImageRocketRight, m_fireworksImageRocketBottom,
				3, DX_PI * 2, m_hFireworksRocket[0], true, false);//�摜��`��
		}
	
		if (m_isFire)
		{
			DrawRectRotaGraph(m_fireworksImagePosX[i] + 30, m_fireworksImagePosY[i] - 30,
				m_fireworksImageLeft, m_fireworksImageTop, m_fireworksImageRight, m_fireworksImageBottom,
				5, DX_PI * 2, m_hFireworks[3], true, false);//�摜��`��
		}
	}
}
