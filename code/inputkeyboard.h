//*****************************************************
//
// �L�[�{�[�h���͏���[inputkeyboard.h]
// Author:���R����
//
//*****************************************************
#ifndef _INPUTKEYBOARD_H_	// ��d�C���N���[�h�h�~
#define _INPUTKEYBOARD_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "input.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int NUM_KEY_MAX = 256;	// �L�[�̍ő吔
}

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();	// �R���X�g���N�^
	~CInputKeyboard();	// �f�X�g���N�^

	// �����o�ϐ�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����

	// �ϐ��擾�E�ݒ�֐�
	bool GetPress(int nKey);	// �{�^���v���X���
	bool GetTrigger(int nKey);	// �{�^���g���K�[���
	bool GetRelease(int nKey);	// �{�^�������[�X���
	int GetRepeat(int nKey);	// �{�^�����s�[�g���

	// �ÓI�����o�֐�
	static CInputKeyboard *Create(HINSTANCE hInstance, HWND hWnd);	// ��������
	static CInputKeyboard *GetInstance(void) { return m_pKeyboard; }	// �C���X�^���X�̎擾

private:
	// �����o�ϐ�
	BYTE m_aKeyState[NUM_KEY_MAX];					// �v���X���
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			// �g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			// �����[�X���
	BYTE m_aKeyStateRepeat[NUM_KEY_MAX];			// ���s�[�g���
	int m_aCntRepeat[NUM_KEY_MAX];	// ���s�[�g�J�E���^�[

	// �ÓI�����o�ϐ�
	static CInputKeyboard *m_pKeyboard;	// ���g�̃|�C���^
};

#endif