/*
#pragma once
#include <unordered_map>
#include <string>

/// <summary>
/// SE�̊Ǘ����s���V���O���g���N���X
/// </summary>
class SoundManager
{
public:
	/// <summary>
	/// SoundManager�g�p�҂�GetInstance()��ʂ�������Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static SoundManager& GetInstance()
	{
		static SoundManager instance;//�������B��̎���
		return instance;//����̎Q�Ƃ�Ԃ�
	}
	/// <summary>
	/// �w��̃T�E���h��炷
	/// </summary>
	/// <param name="name">�T�E���h��</param>
	void Play(const wchar_t* name);

private:
	std::unordered_map<std::wstring, int>nameAndHandleTable_;
	int LoadSoundFile(const wchar_t* fileName);
	SoundManager();
	~SoundManager();
	//�R�s�[��������֎~����
	SoundManager(const SoundManager&) = delete;
	void operator = (const SoundManager&) = delete;
};
*/

