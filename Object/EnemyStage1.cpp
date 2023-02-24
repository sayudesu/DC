#include "EnemyStage1.h"
#include "SceneMain2.h"
#include "game.h"
#include <DxLib.h>

namespace Enemy
{

	//�{�X�̈ʒu
	constexpr int kBossPosLeft = Game::kScreenWidth - 300;
	constexpr int kBossPosTop = 200;
	constexpr int kBossPosRight = kBossPosLeft + 100;
	constexpr int kBossPosBottom = kBossPosTop + 100;

	constexpr float kBarrelSpeed = 8.0f;


}

EnemyStage1::EnemyStage1():
	m_posLeft(0),
	m_posTop(0),
	m_posRight(0),
	m_posBottom(0),
	m_barrelLeft(0),
	m_barrelTop(0),
	m_barrelRight(0),
	m_barrelBottom(0),
	m_fallenLeft(0),
	m_fallenTop(0),
	m_fallenRight(0),
	m_fallenBottom(0),
	m_fallen2Left(0),
	m_fallen2Top(0),
	m_fallen2Right(0),
	m_fallen2Bottom(0),
	m_fallenRangeLeft(0),
	m_fallenRangeTop(0),
	m_fallenRangeRight(0),
	m_fallenRangeBottom(0),
	m_fallenRange2Left(0),
	m_fallenRange2Top(0),
	m_fallenRange2Right(0),
	m_fallenRange2Bottom(0),
	m_chargeLeft(0),
	m_chargeTop(0),
	m_chargeRight(0),
	m_chargeBottom(0),
	m_barrelSpeed(0),
	m_fall(0),
	m_fallFireBall(0),
	m_fallenRange(0),
	m_fallenRange2(0),
	m_fallenCount(0),
	m_fallenCount2(0),
	m_ladderNum(0),
	m_rushCount(0),
	m_fallenUpSpeed(0.0f),
	m_fallenUpSpeed2(0.0f),
	m_getPos(0.0f),
	m_rad(0.0f),
	m_chargeSpeed(0.0f),
	m_length(0.0f),
	m_getFireBallPos(0),
	m_isFirstMove(false),
	m_isCourse(false),
	m_isFireBallCourse(false),
	m_isFallenDrop(false),
	m_isCanFallen(false),
	m_isFallenDrop2(false),
	m_isCanFallen2(false),
	m_isFallenUp(false),
	m_isFallenUp2(false),
	m_isRush(false),
	m_isRushBlink(false),
	m_pos(0.0f, 0.0f),
	m_barrelPos(0.0f,0.0f),//�M
	m_fallenPos(0.0f, 0.0f),//�h�b�X���I�ȓz
	m_fallen2Pos(0.0f, 0.0f),//�h�b�X���I�ȓz
	m_chargePos(0.0f, 0.0f),//�`���[�W����G
	m_vec(0.0f,0.0f),
	m_playerPos(0.0f, 0.0f),
	m_playerSavePos(0.0f, 0.0f)
{
	m_isFirstMove = true;//��������
	m_isCanFallen = true;
	m_isCanFallen2 = true;
	//�t�@�C�A�{�[�������ʒu
	m_pos.x = Game::kScreenWidth - 400;
	m_pos.y = Game::kScreenHeight - 400;
	//�M�����ʒu
	m_barrelPos.x = Enemy::kBossPosLeft;
	m_barrelPos.y = Enemy::kBossPosTop;
	//�ǂ�����
	m_fallenPos.x = Stage2::kBox2Xt;
	m_fallenPos.y = Stage2::kBoxBottom8Yf;
	//�ǂ�����2
	m_fallen2Pos.x = Stage2::kBox4Xt;
	m_fallen2Pos.y = Stage2::kBoxBottom8Yf;
	//�`���[�W����G
	m_chargePos.x = Stage2::kBox1Xf;
	m_chargePos.y = Stage2::kBox1Yf - 50;

	m_chargeSpeed = 10.0f;

}

EnemyStage1::~EnemyStage1()
{

}

void EnemyStage1::Init()
{
}

void EnemyStage1::End()
{
}

void EnemyStage1::Update()
{
	BarrelMove();//�M�̓���
	fireBallMove();//�t�@�C�A�{�[���̓���
	falleMove();//�h�b�X������
	npcPos();//�G�̃T�C�Y�擾
	ChargeMove();//�`���[�W�G�l�~�[�̓���
}
//�`��
void EnemyStage1::Draw()
{
	//�G�l�~�[
	DrawBox(m_posLeft, m_posTop, m_posRight, m_posBottom, 0xff0000, true);
	//�{�X
	DrawBox(Enemy::kBossPosLeft, Enemy::kBossPosTop,
		Enemy::kBossPosRight, Enemy::kBossPosBottom, 0xffff00, true);
	//�M
	DrawBox(m_barrelLeft, m_barrelTop, m_barrelRight, m_barrelBottom, 0xffff00, true);
	//�ǂ�����
	DrawBox(m_fallenLeft, m_fallenTop, m_fallenRight, m_fallenBottom, 0xffff00, true);
	//�ǂ�����2
	DrawBox(m_fallen2Left, m_fallen2Top, m_fallen2Right, m_fallen2Bottom, 0xffff00, true);
	//�`���[�W�G�l�~�[
	if (m_isRushBlink)//�~�܂��Ă�Ԃ͌����Ȃ�
	{
		DrawBox(m_chargeLeft, m_chargeTop, m_chargeRight, m_chargeBottom, 0xffff00, false);
	}
#if false	
	//�ǂ�����͈�
	DrawBox(m_fallenRangeLeft, m_fallenRangeTop, m_fallenRangeRight, m_fallenRangeBottom, 0xffff00, false);
	//�ǂ�����2�͈�
	DrawBox(m_fallenRange2Left, m_fallenRange2Top, m_fallenRange2Right, m_fallenRange2Bottom, 0xffff00, false);
#endif
}
//�M�̓���
void EnemyStage1::BarrelMove()
{
	m_barrelPos.y += m_vec.y;//�d�͂̃x�N�g���p

	m_vec.y += 3.0f;//�d��

	if (m_fall == 5)//�n�ʂɓ���������
	{
		m_isCourse = false;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x -= Enemy::kBarrelSpeed * m_barrelSpeed;//�Ƃ肠�����E�Ɉړ�

	}
	else if (m_fall == 4)//�n�ʂɓ���������
	{
		m_isCourse = true;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x += Enemy::kBarrelSpeed * m_barrelSpeed;//���Ɉړ�

	}

	if (m_fall == 3)//�n�ʂɓ���������
	{
		m_isCourse = false;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x -= Enemy::kBarrelSpeed * m_barrelSpeed;//�Ƃ肠�����E�Ɉړ�

	}

	if (m_fall == 2)//�n�ʂɓ���������
	{
		m_isCourse = true;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x += Enemy::kBarrelSpeed * m_barrelSpeed;//���Ɉړ�

	}

	if (m_fall == 1)//�n�ʂɓ���������
	{
		m_isCourse = false;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x -= Enemy::kBarrelSpeed * m_barrelSpeed;//�Ƃ肠�����E�Ɉړ�

	}

	if (m_barrelRight < 0)//�M����ʍ��ɏ�����ƍŏ��̈ʒu�ɖ߂��Ă���
	{
		m_barrelPos.x = Enemy::kBossPosLeft;
		m_barrelPos.y = Enemy::kBossPosTop;
	}
	else if (m_barrelRight > Game::kScreenWidth + 100)//�M����ʉE�ɏ�����ƍŏ��̈ʒu�ɖ߂��Ă���
	{
		m_barrelPos.x = Enemy::kBossPosLeft;
		m_barrelPos.y = Enemy::kBossPosTop;
	}

	if (m_fall == 0 && !m_isCourse)//�M���E�Ɉړ�����ꍇ
	{
		m_barrelPos.x -= Enemy::kBarrelSpeed;
	}

	if (m_fall == 0 && m_isCourse)//�M�����Ɉړ�����ꍇ
	{
		m_barrelPos.x += Enemy::kBarrelSpeed;
	}
}
//�����̓���
void EnemyStage1::fireBallMove()
{
	m_pos.y += 3.0f;//�d��

	if (!m_isFireBallCourse)//�E����
	{
		m_pos.x -= 3.0f;
		if (m_pos.x < Stage2::kBox1Xs)//������ύX����
		{
			m_isFireBallCourse = true;
		}
	}
	else//������
	{
		m_pos.x += 3.0f;
		if (m_pos.x > Stage2::kBoxBottom8Xs - 30)//������ύX����
		{
			m_isFireBallCourse = false;
		}
	}

	if (m_fallFireBall== 2)//�n�ʂɓ���������
	{
		//m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_pos.y = static_cast<float>(m_getFireBallPos) + 10;//�v���C���[�̈ʒu���W
	}
}
//�ǂ����񓮂�
void EnemyStage1::falleMove()
{
	//��̖�
	if (m_isCanFallen)//�����̈ʒu�ɂ��邩�ǂ���
	{
		if (m_fallenRange == 1)//�͈͓���������
		{
			m_isFallenDrop = true;
			m_isCanFallen = false;
		}

	}

	if (m_isFallenDrop)//�������̗h���
	{
		m_fallenCount++;//�k���鎞��
		//�h���
		m_fallenPos.x = Stage2::kBox2Xt + GetRand(10);
		m_fallenPos.y = Stage2::kBoxBottom8Yf  + GetRand(10);
	}

	if (m_fallenCount >= 45)
	{
		m_isFallenDrop = false;
		//�����J�n
		m_fallenUpSpeed = 10.0f;//��������ŏ���������
		m_fallenPos.y += m_fallenUpSpeed;//�����X�s�[�h
		if (m_fallenPos.y >= Stage2::kBox2Yt)//������ꏊ����
		{
			m_isFallenUp = true;//��ɖ߂�����
		}
	}
	
	if (m_isFallenUp)//�V��
	{
		m_fallenUpSpeed = 15.0f;//��������ŏ���������
		m_fallenPos.y -= m_fallenUpSpeed;

		if (m_fallenPos.y <= Stage2::kBoxBottom8Yf)
		{
			m_fallenCount = 0;//�J�E���g���Z�b�g
			m_isFallenUp = false;
			m_isCanFallen = true;//�ēx�����邽�߂̏���

			m_fallenPos.x = Stage2::kBox2Xt;
			m_fallenPos.y = Stage2::kBoxBottom8Yf;
		}
	}
	
	//��̖�
	if (m_isCanFallen2)//�����̈ʒu�ɂ��邩�ǂ���
	{
		if (m_fallenRange == 2)//�͈͓���������
		{
			m_isFallenDrop2 = true;
			m_isCanFallen2 = false;
		}

	}

	if (m_isFallenDrop2)//�������̗h���
	{
		m_fallenCount2++;//�k���鎞��
		//�h���
		m_fallen2Pos.x = Stage2::kBox4Xt + GetRand(10);
		m_fallen2Pos.y = Stage2::kBoxBottom8Yf + GetRand(10);
	}

	if (m_fallenCount2 >= 45)
	{
		m_isFallenDrop2 = false;
		//�����J�n
		m_fallenUpSpeed2 = 10.0f;//��������ŏ���������
		m_fallen2Pos.y += m_fallenUpSpeed2;//�����X�s�[�h
		if (m_fallen2Pos.y >= Stage2::kBox4Yt)//������ꏊ����
		{
			m_isFallenUp2 = true;//��ɖ߂�����
		}
	}

	if (m_isFallenUp2)//�V��
	{
		m_fallenUpSpeed2 = 15.0f;//��������ŏ���������
		m_fallen2Pos.y -= m_fallenUpSpeed2;

		if (m_fallen2Pos.y <= Stage2::kBoxBottom8Yf)
		{
			m_fallenCount2 = 0;//�J�E���g���Z�b�g
			m_isFallenUp2 = false;
			m_isCanFallen2 = true;//�ēx�����邽�߂̏���

			m_fallen2Pos.x = Stage2::kBox4Xt;
			m_fallen2Pos.y = Stage2::kBoxBottom8Yf;
		}
	}


	////��̖�
	//if (m_isCanFallen2)//�����̈ʒu�ɂ��邩�ǂ���
	//{
	//	if (m_fallenRange == 2)//�͈͓���������
	//	{
	//		m_isFallenDrop2 = true;
	//		m_isCanFallen2 = false;
	//	}
	//}

	//if (m_isFallenDrop2)//�������̗h���
	//{
	//	m_fallenCount2++;//�k���鎞��
	//	//�h���
	//	m_fallen2Pos.x = Stage2::kBox4Xt + GetRand(10);
	//	m_fallen2Pos.y = Stage2::kBoxBottom8Yf + GetRand(10);

	//	if (m_fallenCount2 >= 30)//3�b��
	//	{
	//		//�|�W�V���������Z�b�g
	//		m_fallen2Pos.x = Stage2::kBox4Xt;
	//		m_fallen2Pos.y = Stage2::kBoxBottom8Yf;
	//	}
	//}

	//if (m_fallenCount2 >= 45)
	//{
	//	m_isFallenDrop2 = false;
	//	//�����J�n
	//	m_fallen2Pos.y += 10;//�����X�s�[�h
	//	if (m_fallen2Pos.y >= Stage2::kBox4Yt)//������ꏊ����
	//	{
	//		m_fallenCount2 = 0;//�J�E���g���Z�b�g

	//		//�����|�W�V�����ɖ߂�
	//		m_fallen2Pos.x = Stage2::kBox4Xt;
	//		m_fallen2Pos.y = Stage2::kBoxBottom8Yf;
	//		m_isCanFallen2 = true;

	//	}
	//}
}
//�G�ɓːi����
void EnemyStage1::ChargeMove()
{
	if (m_isRush)//�����邩�ǂ���
	{

		//�v���C���[�ɓːi����
		Vec2 toPlayer{ 0.0f,0.0f };

		m_rushCount++;
		if (m_rushCount == 1)
		{
			m_playerSavePos = m_playerPos;//�����O�̃v���C���[���W���擾����
			//m_chargeSpeed
			//m_chargeSpeed = 30.0f;
		}
		if (m_rushCount >= 120)
		{
			m_isRushBlink = true;
			toPlayer.x = m_playerSavePos.x - m_chargePos.x;
			toPlayer.y = m_playerSavePos.y - m_chargePos.y;

			m_length = toPlayer.length();//�������擾
			
			toPlayer = toPlayer.normalize();//���K��
			//m_chargeSpeed = 0.0f;

		}

		m_chargePos += toPlayer * m_chargeSpeed;//�v���C���[�̕����ɒ����ňړ�

		/*
		if (m_length >= m_chargePos.length())
		{
			printfDx("%f\n", m_playerSavePos.length());
		//	printfDx("%f\n", m_length);
			m_rushCount = 0;
			m_isRushBlink = false;
		}
		*/
		/*
		if (static_cast<int>(m_playerSavePos.x) == m_chargeLeft)
		{
			toPlayer.x = 0.0f;
			toPlayer.y = 0.0f;
			m_chargeSpeed = 0.0f;
		}
		*/
		if (m_rushCount == 120 * 2)//�ǐՂł��鎞�Ԃ����Z�b�g
		{
			m_rushCount = 0;
			m_isRushBlink = false;
		}
		

		DrawFormatString(100, 45, 0xffffff, "�v���C���[�܂ł̋��� %f", toPlayer);
	}
	else//�Ⴄ�K�w�ɂ���ꍇ
	{
		m_isRushBlink = false;//�Ⴄ�K�w�ɂ���ꍇ�͔���Ȃ�
	}

	//printfDx("%d\n", m_chargeLeft);
	DrawFormatString(100,0,0xffffff,    "�G�̉E����W         m_chargeLeft   -> %d", m_chargeLeft);
	DrawFormatString(100, 15, 0xffffff, "�v���C���[�E����W   m_playerSavePos-> %f", m_playerSavePos.x);
	DrawFormatString(100, 30, 0xffffff, "�v���C���[�܂ł̋��� m_length       -> %f", m_length);

}
//�G�̃L�������W�擾
void EnemyStage1::npcPos()
{
	//enemy�̍��W
	m_posLeft = m_pos.x;
	m_posTop = m_pos.y;
	m_posRight = m_posLeft + 30;
	m_posBottom = m_posTop + 30;

	//�M
	m_barrelLeft = m_barrelPos.x;
	m_barrelTop = m_barrelPos.y;
	m_barrelRight = m_barrelLeft + 40;
	m_barrelBottom = m_barrelTop + 40;

	//�h�b�X��
	m_fallenLeft = m_fallenPos.x;
	m_fallenTop = m_fallenPos.y;
	m_fallenRight = m_fallenLeft  + 150;
	m_fallenBottom = m_fallenTop  +10;
	//�h�b�X����������
	m_fallenRangeLeft =1110;
	m_fallenRangeTop = 550;
	m_fallenRangeRight = m_fallenRangeLeft+ 250;
	m_fallenRangeBottom = m_fallenRangeTop + 120;
	//�h�b�X��2
	m_fallen2Left = m_fallen2Pos.x;
	m_fallen2Top = m_fallen2Pos.y;
	m_fallen2Right = m_fallen2Left + 150;
	m_fallen2Bottom = m_fallen2Top + 10;
	//�h�b�X��2��������
	m_fallenRange2Left = 1110 + 150 + 150;
	m_fallenRange2Top = 550;
	m_fallenRange2Right = m_fallenRange2Left + 250;
	m_fallenRange2Bottom = m_fallenRange2Top + 120;

	//�`���[�W�G�l�~�[
	m_chargeLeft = m_chargePos.x;
	m_chargeTop = m_chargePos.y;
	m_chargeRight = m_chargeLeft + 30;
	m_chargeBottom = m_chargeTop + 30;
}
