#pragma once

//#define _DEBUG 

namespace Game
{
//#ifdef _DEBUG	
	// ウインドウモード設定
	constexpr bool kWindowMode = true;
	/*
#else
	constexpr bool kWindowMode = false;
#endif
*/
	// マウスカーソル表示
	constexpr bool kMouseMode = true;
	// ウインドウ名
	const char* const kTitleText = "ゲーム（制作中）";
	//フォント名
	//const char* const kFontName = "HG行書体";
	//const char* const kFontName = "Data/Font/GAGAGAGA FREE";
	constexpr int kFontSize = 64;
	// ウインドウサイズ
	/*constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;*/
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	// カラーモード
	constexpr int kColorDepth = 32;		// 32 or 16
};

namespace Stage2
{
	//箱の横幅
	constexpr int BoxWidth = 150;
	//箱の高さ
	constexpr int BoxHeight = 20;
	//段差
	constexpr int BoxStep = 5;

	//一階
	constexpr int Box1X = 0;                                   //左
	constexpr int Box1Y = Game::kScreenHeight - 60;            //上
	constexpr int BoxBottom1X = Box1X + Game::kScreenWidth / 2;//右
	constexpr int BoxBottom1Y = Box1Y + BoxHeight;             //下

	//一階一段差
	constexpr int Box2X = BoxBottom1X;
	constexpr int Box2Y = Box1Y - BoxStep;
	constexpr int BoxBottom2X = Box2X + BoxWidth;
	constexpr int BoxBottom2Y = Box2Y + BoxHeight;

	//一階二段差
	constexpr int Box3X = BoxBottom2X;
	constexpr int Box3Y = Box2Y - BoxStep;
	constexpr int BoxBottom3X = Box3X + BoxWidth;
	constexpr int BoxBottom3Y = Box3Y + BoxHeight;

	//一階三段差
	constexpr int Box4X = BoxBottom3X;
	constexpr int Box4Y = Box3Y - BoxStep;
	constexpr int BoxBottom4X = Box4X + BoxWidth;
	constexpr int BoxBottom4Y = Box4Y + BoxHeight;

	//一階四段差
	constexpr int Box5X = BoxBottom4X;
	constexpr int Box5Y = Box4Y - BoxStep;
	constexpr int BoxBottom5X = Box5X + BoxWidth;
	constexpr int BoxBottom5Y = Box5Y + BoxHeight;

	//一階五段差
	constexpr int Box6X = BoxBottom5X;
	constexpr int Box6Y = Box5Y - BoxStep;
	constexpr int BoxBottom6X = Box6X + BoxWidth;
	constexpr int BoxBottom6Y = Box6Y + BoxHeight;

	//一階六段差
	constexpr int Box7X = BoxBottom6X;
	constexpr int Box7Y = Box6Y - BoxStep;
	constexpr int BoxBottom7X = Box7X + BoxWidth;
	constexpr int BoxBottom7Y = Box7Y + BoxHeight;

	//一階七段差
	constexpr int Box8X = BoxBottom7X;
	constexpr int Box8Y = Box7Y - BoxStep;
	constexpr int BoxBottom8X = Box8X + BoxWidth;
	constexpr int BoxBottom8Y = Box8Y + BoxHeight;
}