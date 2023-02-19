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
	m_fall(0),
	m_ladderNum(0),
	m_getPos(0.0f),
	m_isFirstMove(false),
	m_isCourse(false),
	m_pos(0.0f, 0.0f),
	m_barrelPos(0.0f,0.0f),//�M
	m_vec(0.0f,0.0f)
{
	m_isFirstMove = true;//��������

	m_pos.x = Game::kScreenWidth - 600;
	m_pos.y = Game::kScreenHeight - 300;

	m_barrelPos.x = Enemy::kBossPosLeft;
	m_barrelPos.y = Enemy::kBossPosTop;

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
	m_barrelPos.y += m_vec.y;//�d�͂̃x�N�g���p
	m_vec.y += 1.0f;//�d��

	BarrelMove();//�M�̓���
	fireBallMove();//�t�@�C�A�{�[���̓���
	npcPos();//�G�̃T�C�Y�擾
}

void EnemyStage1::Draw()
{
	//�G�l�~�[
	DrawBox(m_posLeft, m_posTop, m_posRight, m_posBottom, 0xffffff, true);
	//�{�X
	DrawBox(Enemy::kBossPosLeft, Enemy::kBossPosTop,
		Enemy::kBossPosRight, Enemy::kBossPosBottom, 0xffff00, true);
	//�M�̈ړ�
	DrawBox(m_barrelLeft, m_barrelTop, m_barrelRight, m_barrelBottom, 0xffff00, true);
}

void EnemyStage1::BarrelMove()
{
	if (m_fall == 5)//�n�ʂɓ���������
	{
		m_isCourse = false;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x -= 5.0f;//�Ƃ肠�����E�Ɉړ�

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
		m_barrelPos.x += 5.0f;//���Ɉړ�

	}

	if (m_fall == 3)//�n�ʂɓ���������
	{
		m_isCourse = false;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x -= 5.0f;//�Ƃ肠�����E�Ɉړ�

	}

	if (m_fall == 2)//�n�ʂɓ���������
	{
		m_isCourse = true;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x += 5.0f;//���Ɉړ�

	}

	if (m_fall == 1)//�n�ʂɓ���������
	{
		m_isCourse = false;
		m_vec.y = 0.0f;//���ɗ����Ȃ��悤��
		m_barrelPos.y = m_getPos;//�v���C���[�̈ʒu���W
		m_barrelPos.x -= 5.0f;//�Ƃ肠�����E�Ɉړ�

	}

	if (m_barrelRight < 0)//�M����ʍ��ɏ�����ƍŏ��̈ʒu�ɖ߂��Ă���
	{
		m_barrelPos.x = Enemy::kBossPosLeft;
		m_barrelPos.y = Enemy::kBossPosTop;
	}

	if (m_fall == 0 && !m_isCourse)//�M���E�Ɉړ�����ꍇ
	{
		m_barrelPos.x -= 1.0f;
	}

	if (m_fall == 0 && m_isCourse)//�M�����Ɉړ�����ꍇ
	{
		m_barrelPos.x += 1.0f;
	}
}

void EnemyStage1::fireBallMove()
{

}

void EnemyStage1::npcPos()
{
	//enemy�̍��W
	m_posLeft = m_pos.x - 10;
	m_posTop = m_pos.y - 10;
	m_posRight = m_posLeft + 10;
	m_posBottom = m_posTop + 10;

	//�M
	m_barrelLeft = m_barrelPos.x;
	m_barrelTop = m_barrelPos.y;
	m_barrelRight = m_barrelLeft + 40;
	m_barrelBottom = m_barrelTop + 40;
}
