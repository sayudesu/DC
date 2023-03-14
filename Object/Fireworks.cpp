#include <Dxlib.h>
#include "Fireworks.h"
#include "Image.h"
#include "game.h"

Fireworks::Fireworks() :
	m_hFireworks(), m_hFireworksRocket(),//�ԉΗp�摜�n���h��
	m_fireworksImagePosX(), m_fireworksImagePosY(),//�ԉΕ`��ʒu
	m_fireworksImageRocketLeft(0), m_fireworksImageRocketTop(0),//�ԉΉ摜�ʒu
	m_fireworksImageRocketRight(0), m_fireworksImageRocketBottom(0),
	m_fireworksImageLeft(), m_fireworksImageTop(0),//�ԉΉ摜�ʒu
	m_fireworksImageRight(0), m_fireworksImageBottom(0),
	m_frameCount(), m_delayCount(),
	m_isFireRocket(), m_isFire()
{
	//������
	for (int i = 0; i < Staging::kFireworksNum; i++)
	{
		m_fireworksImagePosX[i] = GetRand(Game::kScreenWidth);
		m_fireworksImagePosY[i] = Game::kScreenHeight;
		m_fireworksImageLeft[i] = 96;
		m_frameCount[i] = 0;
		m_isFireRocket[i] = true;
		m_isFire[i] = false;
	}

	//
	m_fireworksImageRocketRight = 7;
	m_fireworksImageRocketBottom = 51;
	//
	m_fireworksImageRight = 96;
	m_fireworksImageBottom = 100;


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
	for (int i = 0; i < 9; i++)
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
	

	for (int i = 0; i < Staging::kFireworksNum; i++)
	{
		m_frameCount[i]++;
		//m_delayCount[i]++;//�����ԉ΂̏ꍇ�̓f�B���C������
		if (m_frameCount[i] == Staging::kFireworksAnimatioFramenCount)//2�t���[����1��X�V
		{
			m_frameCount[i] = 0;

			if (m_fireworksImagePosY[i] >= 500)//�j��ꏊ�ʒu
			{
				m_fireworksImagePosY[i] -= Staging::kFireworksRocketSpeed;//��ɍ��W���ړ�
			}
			else//�j��ʒu�ɓ��B�����ꍇ
			{
				m_isFire[i] = true;//�ԉ΂�\��
				m_isFireRocket[i] = false;//�ł��グ���\��
				//m_fireworksImageLeft = 96;
			}

		} 
		
		if (m_isFire[i])
		{
			//printfDx("%d", m_frameCount[i]);
			//�ԉ�
			if (m_fireworksImageLeft[i] <= 5766)m_fireworksImageLeft[i] += 93;//�A�j���[�V�������Đ�
			else//�ԉ΃A�j���[�V�������I�������
			{
				//���W�����l

				m_fireworksImagePosX[i] = GetRand(Game::kScreenWidth);//�ԉΈʒu��ύX
				m_fireworksImagePosY[i] = Game::kScreenHeight;//��ԉ��Ɉړ�
				m_isFire[i] = false;//�U�����ԉ΂͔�\��
				m_isFireRocket[i] = true;//�ł��グ��\��
				m_fireworksImageLeft[i] = 96;

			}

		}

		if (m_fireworksImageRocketLeft <= 280)m_fireworksImageRocketLeft += 7;//�ԉ΃��P�b�g
		else
		{
			m_fireworksImageRocketLeft = 7;//�摜���̈ʒu�������l�ɖ߂�
		}
	}

}

void Fireworks::Draw()
{
	for (int i = 0; i < Staging::kFireworksNum; i++)
	{
		if (m_isFireRocket[i])
		{
			DrawRectRotaGraph(m_fireworksImagePosX[i], m_fireworksImagePosY[i],
				m_fireworksImageRocketLeft, m_fireworksImageRocketTop, m_fireworksImageRocketRight, m_fireworksImageRocketBottom,
				3, DX_PI * 2, m_hFireworksRocket[0], true, false);//�摜��`��
		}
	
		if (m_isFire[i])
		{
			DrawRectRotaGraph(m_fireworksImagePosX[i] + 30, m_fireworksImagePosY[i] - 30,
				m_fireworksImageLeft[i], m_fireworksImageTop, m_fireworksImageRight, m_fireworksImageBottom,
				5, DX_PI * 2, m_hFireworks[3], true, false);//�摜��`��
		}
	}
}