#include <Dxlib.h>
#include "Fireworks.h"
#include "Image.h"
#include "game.h"

Fireworks::Fireworks() :
	m_hFireworks(), m_hFireworksRocket(),//花火用画像ハンドル
	m_fireworksImagePosX(), m_fireworksImagePosY(),//花火描画位置
	m_fireworksImageRocketLeft(0), m_fireworksImageRocketTop(0),//花火画像位置
	m_fireworksImageRocketRight(0), m_fireworksImageRocketBottom(0),
	m_fireworksImageLeft(), m_fireworksImageTop(0),//花火画像位置
	m_fireworksImageRight(0), m_fireworksImageBottom(0),
	m_frameCount(), m_delayCount(),
	m_isFireRocket(), m_isFire()
{
	//初期化
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
		//m_delayCount[i]++;//複数花火の場合はディレイを入れる
		if (m_frameCount[i] == Staging::kFireworksAnimatioFramenCount)//2フレームに1回更新
		{
			m_frameCount[i] = 0;

			if (m_fireworksImagePosY[i] >= 500)//破裂場所位置
			{
				m_fireworksImagePosY[i] -= Staging::kFireworksRocketSpeed;//上に座標を移動
			}
			else//破裂位置に到達した場合
			{
				m_isFire[i] = true;//花火を表示
				m_isFireRocket[i] = false;//打ち上げを非表示
				//m_fireworksImageLeft = 96;
			}

		} 
		
		if (m_isFire[i])
		{
			//printfDx("%d", m_frameCount[i]);
			//花火
			if (m_fireworksImageLeft[i] <= 5766)m_fireworksImageLeft[i] += 93;//アニメーションを再生
			else//花火アニメーションが終わったら
			{
				//座標初期値

				m_fireworksImagePosX[i] = GetRand(Game::kScreenWidth);//花火位置を変更
				m_fireworksImagePosY[i] = Game::kScreenHeight;//一番下に移動
				m_isFire[i] = false;//散った花火は非表示
				m_isFireRocket[i] = true;//打ち上げを表示
				m_fireworksImageLeft[i] = 96;

			}

		}

		if (m_fireworksImageRocketLeft <= 280)m_fireworksImageRocketLeft += 7;//花火ロケット
		else
		{
			m_fireworksImageRocketLeft = 7;//画像をの位置を初期値に戻す
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
				3, DX_PI * 2, m_hFireworksRocket[0], true, false);//画像を描画
		}
	
		if (m_isFire[i])
		{
			DrawRectRotaGraph(m_fireworksImagePosX[i] + 30, m_fireworksImagePosY[i] - 30,
				m_fireworksImageLeft[i], m_fireworksImageTop, m_fireworksImageRight, m_fireworksImageBottom,
				5, DX_PI * 2, m_hFireworks[3], true, false);//画像を描画
		}
	}
}
