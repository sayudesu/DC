#include "DxLib.h"
#include "game.h"
#include "Scene/SceneManager.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetWindowSizeChangeEnableFlag(true);
	SetAlwaysRunFlag(true);
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	//マウスカーソル表示
	SetMouseDispFlag(Game::kMouseMode);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	//フォント変更
	ChangeFont(Game::kFontName);
	//CreateFontToHandle(Game::kFontName,64,-1,-1);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
	//フルスクリーンかどうか
	bool isScreenSize = false;
	bool isTrigger = false;//ボタン確認
	// 最初のシーンの初期化
	SceneManager scene;
	scene.Init();

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();

		// 画面のクリア
		ClearDrawScreen();

		/*
		//フルスクリーン設定
		if (CheckHitKey(KEY_INPUT_LALT))
		{
			if (CheckHitKey(KEY_INPUT_RETURN))
			{
				if (!isTrigger)
				{
					isScreenSize = !isScreenSize;
					ChangeWindowMode(isScreenSize);
				}
				isScreenSize = true;
			}
			else
			{
				isScreenSize = false;
			}
		}
		*/

		//更新処理
		scene.Update();

		//表示処理
		scene.Draw();

#if false
		auto fps = GetFPS();// Frame Per Second
		auto drawcall = GetDrawCallCount();// 描画命令数
		DrawFormatString(200, 200, 0xffffff, "FPS=%2.2f", fps);
		DrawFormatString(200, 230, 0xffffff, "DC=%d", drawcall);
#endif

		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	//メモリの解放
	scene.End();
	//DeleteFontToHandle(font);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}