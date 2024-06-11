//*****************************************************
//
// ���̓}�l�[�W���[[inputManager.h]
// Author:���R����
//
//*****************************************************
#ifndef _INPUTMANAGER_H_	// ��d�C���N���[�h�h�~
#define _INPUTMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CInputManager
{
public:
	// �񋓌^��`
	enum E_BUTTON
	{
		BUTTON_ENTER = 0,	// �G���^�[�{�^��
		BUTTON_BACK,	// �߂�{�^��
		BUTTON_JUMP,	// �W�����v
		BUTTON_ATTACK,	// �U��
		BUTTON_PARRY,	// �p���B
		BUTTON_MOVE_RIGHT,	// �E�ړ�
		BUTTON_MOVE_LEFT,	// ���ړ�
		BUTTON_DASH,	// �_�b�V��
		BUTTON_PAUSE,	// �|�[�Y
		BUTTON_AXIS_UP,	// ������L�[
		BUTTON_AXIS_DOWN,	// �������L�[
		BUTTON_AXIS_RIGHT,	// �E�����L�[
		BUTTON_AXIS_LEFT,	// �������L�[
		BUTTON_MAX
	};

	CInputManager();	// �R���X�g���N�^
	~CInputManager();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����

	// �ϐ��擾�E�ݒ�֐�
	bool GetTrigger(E_BUTTON button) { return m_info.abTrigger[button]; }	// �{�^���g���K�[���
	bool GetPress(E_BUTTON button) { return m_info.abPress[button]; }	// �{�^���v���X���

	// �ÓI�����o�֐�
	static CInputManager *Create(HINSTANCE hInstance, HWND hWnd);
	static CInputManager *GetInstance(void) { return m_pInputManager; }

private:
	// �\���̒�`
	struct S_Info
	{// ���g�̏��
		bool abTrigger[BUTTON_MAX];	// �g���K�[���
		bool abPress[BUTTON_MAX];	// �v���X���

		// �R���X�g���N�^
		S_Info() : abTrigger{}, abPress{} {}
	};

	// �����o�ϐ�
	S_Info m_info;	// ���

	// �ÓI�����o�ϐ�
	static CInputManager *m_pInputManager;	// ���g�̃|�C���^
};

#endif
