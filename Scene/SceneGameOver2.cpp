#include <Dxlib.h>
#include "Image.h"
#include "game.h"
#include "Pad.h"
#include "SceneGameOver2.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneMain3.h"
#include "TitleCursorGame.h"
#include "GameSceneCollision.h"

SceneGameOver2::SceneGameOver2() :
	m_hSoundSelect(-1),//選択時のサウンド
	m_hSoundSelect2(-1),//選択時のサウンド
	m_hMusicBgm(-1),//BGM用ハンドル
	m_soundCount(0),//サウンド発生までのカウント
	m_soundCount2(0),
	m_color1(0),//選択画面の色
	m_color2(0),
	m_color3(0),
	m_pCursor(nullptr),//カーソル表示用
	m_pCursorCollision(nullptr)//カーソル当たり判定
{
	m_pCursor = new TitleCursorGame;
	m_pCursorCollision = new GameSceneCollision;
}

SceneGameOver2::~SceneGameOver2()
{
	delete m_pCursor;
	delete m_pCursorCollision;
	//サウンド削除
	DeleteSoundMem(m_hSoundSelect);
	DeleteSoundMem(m_hSoundSelect2);
}

void SceneGameOver2::Init()
{
	//サウンドを読み込み
	m_hSoundSelect = LoadSoundMem(Sound::kSelect);
	m_hSoundSelect2 = LoadSoundMem(Sound::kSelect2);

	m_hMusicBgm = LoadSoundMem(Sound::kBgmDead);
}

void SceneGameOver2::End()
{
	StopSoundFile();//再生中のサウンドを止める
	DeleteSoundMem(m_hMusicBgm);
}

SceneBase* SceneGameOver2::Update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Pad::update();
	m_pCursor->Update();//カーソルの更新処理
	m_pCursorCollision->Update();//カーソルと選択範囲の当たり判定

	//カーソルが当たっていない場合の文字背景の色
	m_color2 = Color::kWhite;
	m_color3 = Color::kWhite;

	if (m_pCursorCollision->CollsionStage1())//カーソルと選択範囲に当たっていたら
	{
		m_soundCount++;
		m_color2 = Color::kRed;//カーソルが当たっている場合の文字背景の色
		if (m_soundCount == 1)
		{
			PlaySoundMem(m_hSoundSelect2, DX_PLAYTYPE_BACK);//押している音を再生
		}
		if (padState & PAD_INPUT_2)//Xボタン
		{
			return(new SceneMain3);//同じステージを繰り返す
		}
	}
	else
	{
		m_soundCount = 0;
	}
	if (m_pCursorCollision->CollsionEnd())//カーソルと選択範囲に当たっていたら
	{
		m_soundCount2++;
		m_color3 = Color::kRed;//カーソルが当たっている場合の文字背景の色
		if (m_soundCount2 == 1)
		{
			PlaySoundMem(m_hSoundSelect2, DX_PLAYTYPE_BACK);//押している音を再生
		}
		if (padState & PAD_INPUT_2)//Xボタン
		{
			return(new SceneTitle);//タイトル画面に移動
		}
	}
	else
	{
		m_soundCount2 = 0;
	}

	//サウンド
	if (CheckSoundMem(m_hMusicBgm) == 0)//鳴っていなかったら
	{
		PlaySoundMem(m_hMusicBgm, DX_PLAYTYPE_BACK);//サウンドを再生
		ChangeVolumeSoundMem(100, m_hMusicBgm);//音量調整
	}

	if (Pad::isTrigger(PAD_INPUT_2))//Xボタン
	{
		PlaySoundMem(m_hSoundSelect, DX_PLAYTYPE_BACK);//押している音を再生
	}

	return this;
}

void SceneGameOver2::Draw()
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(500, 300, Game::kScreenWidth - 500, Game::kScreenHeight - 300, 0x00ffff, true);//中
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(500, 300, Game::kScreenWidth - 500, Game::kScreenHeight - 300, 0xffffff, false);//枠組み

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//色を薄くする
	//DrawBox(SceneSelect::kSelectLeft, SceneSelect::kSelectTop, SceneSelect::kSelectRight, SceneSelect::kSelectBottom, m_color1, true);
	DrawBox(SceneSelect::kSelectLeft2, SceneSelect::kSelectTop2, SceneSelect::kSelectRight2, SceneSelect::kSelectBottom2, m_color2, true);
	DrawBox(SceneSelect::kSelectLeft3, SceneSelect::kSelectTop3, SceneSelect::kSelectRight3, SceneSelect::kSelectBottom3, m_color3, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//色を戻す

	DrawString(SceneSelect::kSelectLeft + 75, SceneSelect::kSelectTop + 5, "You Died.", Color::kRed);
	DrawString(SceneSelect::kSelectLeft2 + 100, SceneSelect::kSelectTop2 + 5, "Retry", Color::kBlue);
	DrawString(SceneSelect::kSelectLeft3 + 75, SceneSelect::kSelectTop3 + 5, "Back to Title", Color::kBlue);

	m_pCursor->Draw();
}

