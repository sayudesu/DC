#pragma once
#include "game.h"
//#define _DEBUG 

namespace Game
{
//#ifdef _DEBUG	
	// �E�C���h�E���[�h�ݒ�
	constexpr bool kWindowMode = true;
	/*
#else
	constexpr bool kWindowMode = false;
#endif
*/
	// �}�E�X�J�[�\���\��
	constexpr bool kMouseMode = true;
	// �E�C���h�E��
	const char* const kTitleText = "�Q�[���i���쒆�j";
	//�t�H���g��
	//const char* const kFontName = "HG�s����";
	//const char* const kFontName = "Data/Font/GAGAGAGA FREE";
	constexpr int kFontSize = 64;
	// �E�C���h�E�T�C�Y
	/*constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;*/
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	// �J���[���[�h
	constexpr int kColorDepth = 32;		// 32 or 16
};

namespace Stage2
{
	//���̉���
	constexpr int BoxWidth = 150;
	//���̍���
	constexpr int BoxHeight = 20;
	//�i��
	constexpr int BoxStep = 5;
	constexpr int BoxStep2 = 12;

	//��K
	constexpr int Box1X = 0;                                   //��
	constexpr int Box1Y = Game::kScreenHeight - 60;            //��
	constexpr int BoxBottom1X = Box1X + Game::kScreenWidth / 2;//�E
	constexpr int BoxBottom1Y = Box1Y + BoxHeight;             //��

	//��K��i��
	constexpr int Box2X = BoxBottom1X;
	constexpr int Box2Y = Box1Y - BoxStep;
	constexpr int BoxBottom2X = Box2X + BoxWidth;
	constexpr int BoxBottom2Y = Box2Y + BoxHeight;

	//��K��i��
	constexpr int Box3X = BoxBottom2X;
	constexpr int Box3Y = Box2Y - BoxStep;
	constexpr int BoxBottom3X = Box3X + BoxWidth;
	constexpr int BoxBottom3Y = Box3Y + BoxHeight;

	//��K�O�i��
	constexpr int Box4X = BoxBottom3X;
	constexpr int Box4Y = Box3Y - BoxStep;
	constexpr int BoxBottom4X = Box4X + BoxWidth;
	constexpr int BoxBottom4Y = Box4Y + BoxHeight;

	//��K�l�i��
	constexpr int Box5X = BoxBottom4X;
	constexpr int Box5Y = Box4Y - BoxStep;
	constexpr int BoxBottom5X = Box5X + BoxWidth;
	constexpr int BoxBottom5Y = Box5Y + BoxHeight;

	//��K�ܒi��
	constexpr int Box6X = BoxBottom5X;
	constexpr int Box6Y = Box5Y - BoxStep;
	constexpr int BoxBottom6X = Box6X + BoxWidth;
	constexpr int BoxBottom6Y = Box6Y + BoxHeight;

	//��K�Z�i��
	constexpr int Box7X = BoxBottom6X;
	constexpr int Box7Y = Box6Y - BoxStep;
	constexpr int BoxBottom7X = Box7X + BoxWidth;
	constexpr int BoxBottom7Y = Box7Y + BoxHeight;

	//��K���i��
	constexpr int Box8X = BoxBottom7X;
	constexpr int Box8Y = Box7Y - BoxStep;
	constexpr int BoxBottom8X = Box8X + BoxWidth;
	constexpr int BoxBottom8Y = Box8Y + BoxHeight;

	//��K
	constexpr int Box1Xs = Game::kScreenWidth / 2 + 200;
	constexpr int Box1Ys = Box8Y - 200;
	constexpr int BoxBottom1Xs = Game::kScreenWidth - 100;
	constexpr int BoxBottom1Ys = Box1Ys + BoxHeight;
	//��K�E�����i��
	constexpr int Box2Xs = Box1Xs - BoxWidth;
	constexpr int Box2Ys = Box1Ys + BoxStep2;
	constexpr int BoxBottom2Xs = Box1Xs;
	constexpr int BoxBottom2Ys = Box2Ys - BoxHeight;
	//��K�E�����i��
	constexpr int Box3Xs = Box2Xs - BoxWidth;
	constexpr int Box3Ys = Box2Ys - BoxStep2;
	constexpr int BoxBottom3Xs = Box2Xs;
	constexpr int BoxBottom3Ys = Box3Ys - BoxHeight;
	//��K�E����O�i��
	constexpr int Box4Xs = Box3Xs - BoxWidth;
	constexpr int Box4Ys = Box3Ys - BoxStep2;
	constexpr int BoxBottom4Xs = Box3Xs;
	constexpr int BoxBottom4Ys = Box4Ys - BoxHeight;
	//��K�E����l�i��
	constexpr int Box5Xs = Box4Xs - BoxWidth;
	constexpr int Box5Ys = Box4Ys - BoxStep2;
	constexpr int BoxBottom5Xs = Box4Xs;
	constexpr int BoxBottom5Ys = Box5Ys - BoxHeight;
	//��K�E����ܒi��
	constexpr int Box6Xs = Box5Xs - BoxWidth;
	constexpr int Box6Ys = Box5Ys - BoxStep2;
	constexpr int BoxBottom6Xs = Box5Xs;
	constexpr int BoxBottom6Ys = Box6Ys - BoxHeight;
	//��K�E����Z�i��
	constexpr int Box7Xs = Box6Xs - BoxWidth;
	constexpr int Box7Ys = Box6Ys - BoxStep2;
	constexpr int BoxBottom7Xs = Box6Xs;
	constexpr int BoxBottom7Ys = Box7Ys - BoxHeight;
	//��K�E���玵�i��
	constexpr int Box8Xs = Box7Xs - BoxWidth;
	constexpr int Box8Ys = Box7Ys - BoxStep2;
	constexpr int BoxBottom8Xs = Box7Xs;
	constexpr int BoxBottom8Ys = Box8Ys - BoxHeight;


	//��q
	constexpr int Ladder1X = Game::kScreenWidth - 150;
	constexpr int Ladder1Y = Game::kScreenHeight - 300;
	constexpr int LadderBottom1X = Ladder1X + 10;
	constexpr int LadderBottom1Y = Ladder1Y + 150;
}