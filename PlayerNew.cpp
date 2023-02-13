#include "SceneMain2.h"
#include "PlayerNew.h"
#include <DxLib.h>
#include "Pad.h"
#include "game.h"

//�萔
namespace
{
	constexpr int kmapSize = 250;

	constexpr double kPlayerSize = 1.4;
	//�v���C���[�̏������W
	constexpr float kPosX = 0.0f;
	constexpr float kPosY = static_cast<float>(Game::kScreenHeight) - 50.0f - 300.0f;//�f�o�b�N�p��-300�ړ�
	//��������
	constexpr float kMoveSpeed = 15.0f; //�����Ɖ������ق����ʔ����I�C���҂�
	// �W�����v��
	constexpr float kJump = -10.0f;
	// �d��
	constexpr float kGravity = 1.0f;

	//�n�ʂ̍���Y��
	constexpr int kGround = 700;

	constexpr int kCharaImageLeftPos = -112; //���ړ�
	constexpr int kCharaImageRightPos = 112; //�E�ړ�

	//�A�j���[�V�����t���[����
	constexpr int kAnimationFrame = 3;

}
//�R���X�g���N�^
PlayerNew::PlayerNew() :
	m_hPlayer(-1),
	m_hPlayerIdle(-1),
	m_hPlayerLighting(-1),
	m_hHealthBer(-1),
	m_hMapFirst(-1),
	m_hMapSecond(-1),
	m_hMapThird(-1),
	m_hMapFourth(-1),
	m_hMapFifth(-1),
	m_hMapChip(-1),
	m_hMapChipSecond(-1),
	m_playerLeft(0),
	m_playerTop(0),
	m_playerRight(0),
	m_playerBottom(0),
	m_charaImagePos(0),
	m_charaImageIdlePos(0),
	m_charaImageAttackPos(0),
	m_charaImageDamagePos(0),
	m_charaImageJumpPos(0),
	m_charaImageCrouching(0),
	m_count(0),
	m_boxPosX(0),
	m_boxPosY(0),
	m_boxPosBottomX(0),
	m_boxPosBottomY(0),
	m_stagingBoxX(0),
	m_stagingBoxY(0),
	m_stagingBoxBottomX(0),
	m_stagingBoxBottomY(0),
	m_playerHealthBer(0),
	m_playerHealthBerCount(0),
	m_playerHealthSizeX(0),
	m_playerHealthSizeY(0),
	m_boxDropCount(0),
	m_frameCount(0),
	m_hierarchy(0),
	m_tip(0),
	m_gravity(0.0f),
	m_isRunMoveLeft(false),
	m_isRunMoveRight(false),
	m_isIdleMove(false),
	m_isAttackMove(false),
	m_isDamageMove(false),
	m_isJumpMove(false),
	m_isCrouchingMove(false),
	m_isHealthBer(false),
	m_isDead(false),
	m_isReset(false),
	m_isTitle(false),
	m_isGetSword(false),
	m_isAttack(false),
	m_isEnemyDead(false),
	m_isStopMove(false),
	m_isItemDrop(false),
	m_isFloorOne(false),
	m_isLadder(false),
	m_isInvaliDown(false),
	m_isCharaDirection(false),
	m_isCharaIdleDirection(false),
	m_isStageClear(false),
	m_isMenu(false),
	m_isItemTip(false),
	m_isItemDropTip(false),
	m_isUpTip(false),
	m_isGravity(false),
	m_isFall(false),
	m_playerSize(0.0f, 0.0f),
	m_pos(0.0f, 0.0f),
	m_imagePos(0.0f, 0.0f),
	m_imageBalancePos(0.0f, 0.0f),
	m_underPos(0.0f, 0.0f),
	m_attackPos(0.0f, 0.0f),
	m_attackBottomPos(0.0f, 0.0f),
	m_vec(0.0f, 0.0f),
	m_getPos(0.0f)

{
	m_charaImagePos = (1344 - kCharaImageRightPos);
	m_func = &PlayerNew::UpdateMove;



}
//�f�X�g���N�^
PlayerNew::~PlayerNew()
{

}
//������
void PlayerNew::Init()
{
	/*
	m_hierarchy = 1;
	m_playerHealthBer = 100;

	m_boxDropCount = 120;

	m_boxPosX = kBoxPosX;
	m_boxPosY = kBoxPosY;
	m_boxPosBottomX = m_boxPosX + kBoxPosBottomX;
	m_boxPosBottomY = m_boxPosY + kBoxPosBottomY;

	m_pos.x = kPosX;
	m_pos.y = kPosY;

	m_underPos.x = m_pos.x + 50;
	m_underPos.y = m_pos.y + 100;

	m_gravity = kGravity;
	
	m_isEnemyDead = true;
	m_isStopMove = true;
	m_isItemTip = true;
	m_isItemDropTip = true;
	m_isUpTip = true;

	GetGraphSizeF(m_hPlayer, &m_playerSize.x, &m_playerSize.y);
	*/
}
//�������̊J��
void PlayerNew::End()
{

}
//�A�b�v�f�[�g����
void PlayerNew::Update()
{
	(this->*m_func)();
}
//�`��
void PlayerNew::Draw()
{
	DrawRectRotaGraph(static_cast<int>(m_imagePos.x) + static_cast<int>(m_imageBalancePos.x),
		static_cast<int>(m_imagePos.y) + static_cast<int>(m_imageBalancePos.y),
		m_charaImageIdlePos, 0, 80, 80, kPlayerSize, 0, m_hPlayerIdle, true, m_isCharaIdleDirection);

	////////////////////
	///*����̊m�F�p*///
	////////////////////
#if true	

	//�L�����N�^�[
	DrawBox(m_playerLeft, m_playerTop, m_playerRight, m_playerBottom, 0xff0000, false);

	if (m_isAttack)
	{
		DrawBox(m_attackPos.x, m_attackPos.y, m_attackBottomPos.x, m_attackBottomPos.y, 0x0000ff, false);
	}

#endif
}
//����
void PlayerNew::Operation()
{
	//���͔���
	Pad::update();

	m_isCrouchingMove = false;
	m_isRunMoveRight = false;//�E�ɓ����Ă��邩�ǂ���
	m_isRunMoveLeft = false;//���ɓ����Ă��邩�ǂ���
	m_isIdleMove = true;//�����Ă��邩�ǂ���

	//�ړ�
	if (CheckHitKey(KEY_INPUT_RIGHT) && !m_isAttackMove && !m_isDamageMove && !m_isCrouchingMove)//�E
	{
		m_pos.x += kMoveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) && !m_isAttackMove && !m_isDamageMove && !m_isCrouchingMove)//��
	{
		m_pos.x -= kMoveSpeed;
	}
	/*
	if (CheckHitKey(KEY_INPUT_UP))
	{
		m_vec.y = 0.0f;
		m_pos.y -= kMoveSpeed;
	}
	*/
	//�W�����v
	if (Pad::isTrigger(KEY_INPUT_UP))//��
	{
		m_vec.y = 0.0f;
		//m_isGravity = false;
		printfDx("�W�����v\n");
		m_vec.y = kJump;//�W�����v�J�n
		
	}
	
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_pos.y += kMoveSpeed;
	}
}
//�A�b�v�f�[�g����
void PlayerNew::UpdateMove()
{
	//����
	Operation();
	if (!m_isFall)//�n�ʂɓ������Ă��Ȃ�������
	{
		//�d��
		m_vec.y += kGravity;
	}
	else//�n�ʂɓ������Ă�����
	{
	//	m_vec.y = 0.0f;
		m_pos.y = m_getPos;

		//�v���C���[�̈ʒu���W
	}
	
	//�v���C���[�ʒu
	m_pos += m_vec;

#if true	
	m_playerLeft = static_cast<int>(m_pos.x) - 15;
	m_playerTop = static_cast<int>(m_pos.y) + 10;
	m_playerRight = m_playerLeft + 40;
	m_playerBottom = m_playerTop + 40;
#else
	m_playerLeft = static_cast<int>(m_pos.x) - 25;
	m_playerTop = static_cast<int>(m_pos.y) + 10;
	m_playerRight = static_cast<int>(m_pos.x) + 25;
	m_playerBottom = static_cast<int>(m_pos.y) + 60;
#endif

	DrawBox(m_playerLeft, m_playerTop, m_playerRight, m_playerBottom, 0xffffff, true);
}
