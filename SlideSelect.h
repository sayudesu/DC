#pragma once

class TitleCursorGame;
class GameSceneCollision;

class SlideSelect
{
public:
	SlideSelect();
	virtual ~SlideSelect();

	void Update();//�X�V����
	void Draw();//�`�揈��
	void Slider();//�I����ʂ��X���C�h����������
	void Collsion();//�J�[�\���̔���
public:
	//�I��������Ԃ�n��
	bool SetSceneStage() { return m_isSceneStage; }
	bool SetSceneRetry() { return m_isSceneRetry; }
	bool SetSceneTitle() { return m_isSceneTitle; }
	bool SetSceneDead()  { return m_isSceneDead;  }
private:
	//�T�E���h�n���h��
	int m_hSoundSelect;//�{�^�����������ꍇ�̃T�E���h
	int m_hSoundSelect2;

	int m_backGround_Y;//�w�i��DrawBox�ʒu�c���W
	int m_SringBox_Y;//�����g�͈͏c���W
	int m_SringBox2_Y;//�����g�͈͏c���W
	int m_SringBox3_Y;//�����g�͈͏c���W

	int m_Sring_Y;//�����c���W
	int m_Sring2_Y;//�����c���W
	int m_Sring3_Y;//�����c���W

	int m_color1;//�I����ʂ̐F
	int m_color2;
	int m_color3;

	int m_soundCount;//�T�E���h�Đ��܂ł̃J�E���g
	int m_soundCount2;
	int m_soundCount3;

	bool m_isMoveStop;//�X���C�h�������~�߂�

	bool m_isSceneStage;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	bool m_isSceneRetry;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	bool m_isSceneTitle;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�
	bool m_isSceneDead;//��ʂ��Â��Ȃ�����ɃV�[���̐؂�ւ�

	TitleCursorGame* m_pCursor;
	GameSceneCollision* m_pCursorCollision;
};

