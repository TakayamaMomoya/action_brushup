//*****************************************************
//
// �}�E�X���͏���[inputmouse.h]
// Author:���R����
//
//*****************************************************
#ifndef _INPUTMOUSE_H_	// ��d�C���N���[�h�h�~
#define _INPUTMOUSE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "input.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace Mouse
{
const int NUM_BUTTON_MAX = 8;	//�}�E�X�{�^���̐�
}

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CInputMouse : public CInput
{
public:
	// �񋓌^��`
	typedef enum
	{//�}�E�X�{�^��
		BUTTON_LMB = 0,					//���N���b�N
		BUTTON_RMB,						//�E�N���b�N
		BUTTON_WHEEL,						//�E�B�[���N���b�N
		BUTTON_SIDE01,						//�T�C�h�{�^���P
		BUTTON_SIDE02,						//�T�C�h�{�^���Q
		BUTTON_MAX
	}BUTTON;

	CInputMouse();	// �R���X�g���N�^
	~CInputMouse();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����

	// �ϐ��擾�E�ݒ�֐�
	bool GetPress(int nKey);	// �{�^���v���X���
	bool GetTrigger(int nKey);	// �{�^���g���K�[���
	bool GetRelease(int nKey);	// �{�^�������[�X���
	int GetRepeat(int nKey);	// �{�^�����s�[�g���
	LONG GetMoveIX(void);	// X���̈ړ���
	LONG GetMoveIY(void);	// Y���̈ړ���
	LONG GetMoveIZ(void);	// �z�C�[���̉�]��

	// �ÓI�����o�֐�
	static CInputMouse *Create(HINSTANCE hInstance, HWND hWnd);	// ��������
	static CInputMouse *GetInstance(void) { return m_pMouse; }	// �C���X�^���X�̎擾

private:
	// �����o�ϐ�
	DIMOUSESTATE2 m_mouseState;	//�}�E�X�̏��\����
	BYTE m_aKeyState[Mouse::NUM_BUTTON_MAX];	// �v���X���
	BYTE m_aKeyStateTrigger[Mouse::NUM_BUTTON_MAX];	// �g���K�[���
	BYTE m_aKeyStateRelease[Mouse::NUM_BUTTON_MAX];	// �����[�X���
	BYTE m_aKeyStateRepeat[Mouse::NUM_BUTTON_MAX];	// ���s�[�g���
	int m_aCntRepeat[Mouse::NUM_BUTTON_MAX];	// ���s�[�g�J�E���^�[

	// �ÓI�����o�ϐ�
	static CInputMouse *m_pMouse;	// ���g�̃|�C���^
};

#endif