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
	m_fallenRangeLeft(0),
	m_fallenRangeTop(0),
	m_fallenRangeRight(0),
	m_fallenRangeBottom(0),
	m_fall(0),
	m_fallFireBall(0),
	m_ladderNum(0),
	m_getPos(0.0f),
	m_getFireBallPos(0),
	m_isFirstMove(false),
	m_isCourse(false),
	m_isFireBallCourse(false),
	m_pos(0.0f, 0.0f),
	m_barrelPos(0.0f,0.0f),//�M
	m_fallenPos(0.0f, 0.0f),//�h�b�X���I�ȓz
	m_vec(0.0f,0.0f)
{
	m_isFirstMove = true;//��������

	//�t�@�C�A�{�[�������ʒu
	m_pos.x = Game::kScreenWidth - 400;
	m_pos.y = Game::kScreenHeight - 400;
	//�M�����ʒu
	m_barrelPos.x = Enemy::kBossPosLeft;
	m_barrelPos.y = Enemy::kBossPosTop;
	//�ǂ�����
	m_fallenPos.x = Stage2::kBox2Xt;
	m_fallenPos.y = Stage2::kBoxBottom8Yf;

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
	//�͈�
	DrawBox(m_fallenRangeLeft, m_fallenRangeTop, m_fallenRangeRight, m_fallenRangeBottom, 0xffff00, false);
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
		m_barrelPos.x -= Enemy::kBarrelSpeed;//�Ƃ肠�����E�Ɉړ�

	}

	if (m_ladderNum == 4)//��q���~���
	{
		m_barrelPos.y += 10;
	}
	else if (m_fall == 4)//�n�ʂɓ���������
	{
		m_isCourse = true;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x += Enemy::kBarrelSpeed;//���Ɉړ�

	}

	if (m_fall == 3)//�n�ʂɓ���������
	{
		m_isCourse = false;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x -= Enemy::kBarrelSpeed;//�Ƃ肠�����E�Ɉړ�

	}

	if (m_fall == 2)//�n�ʂɓ���������
	{
		m_isCourse = true;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x += Enemy::kBarrelSpeed;//���Ɉړ�

	}

	if (m_fall == 1)//�n�ʂɓ���������
	{
		m_isCourse = false;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x -= Enemy::kBarrelSpeed;//�Ƃ肠�����E�Ɉړ�

	}

	if (m_barrelRight < 0)//�M����ʍ��ɏ�����ƍŏ��̈ʒu�ɖ߂��Ă���
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
	m_fallenRight = m_fallenLeft  + Stage2::kBoxWidth;
	m_fallenBottom = m_fallenTop  +10;

	m_fallenRangeLeft = m_fallenLeft - 50;
	m_fallenRangeTop = m_fallenTop + 30;
	m_fallenRangeRight = m_fallenRight + 50;
	m_fallenRangeBottom = m_fallenRangeTop + 100;
}
