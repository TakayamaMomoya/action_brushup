//*****************************************************
//
// �W���C�p�b�h���͏���[inputjoypad.h]
// Author:���R����
//
//*****************************************************
#ifndef _INPUTJOYPAD_H_	// ��d�C���N���[�h�h�~
#define _INPUTJOYPAD_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "input.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace Joypad
{
const int MAX_PLAYER = 4;	// �v���C���[�̍ő吔
}

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CInputJoypad
{
public:
	// �񋓌^��`
	enum E_PADBUTTONS
	{//�Q�[���p�b�h�{�^��
		PADBUTTONS_UP = 0,	// ����
		PADBUTTONS_DOWN,	// �����
		PADBUTTONS_LEFT,	// �����
		PADBUTTONS_RIGHT,	// �E���
		PADBUTTONS_START,	// �X�^�[�g�{�^��
		PADBUTTONS_BACK,	// �o�b�N�{�^��
		PADBUTTONS_LSTICK,	// ���X�e�B�b�N��������
		PADBUTTONS_RSTICK,	// �E�X�e�B�b�N��������
		PADBUTTONS_LB,	// LB�{�^��
		PADBUTTONS_RB,	// RB�{�^��
		PADBUTTONS_UNKNOWN,	// �s���{�^��
		PADBUTTONS_UNKNOWN2,	// �s���{�^��
		PADBUTTONS_A,	// A�{�^��
		PADBUTTONS_B,	// B�{�^��
		PADBUTTONS_X,	// X�{�^��
		PADBUTTONS_Y,	// Y�{�^��
		PADBUTTONS_MAX
	};
	enum E_STATE_PADVIB
	{//�o�C�u���[�V�����̏��
		PADVIB_NONE = 0,	//�g�p���Ă��Ȃ����
		PADVIB_USE,	//�g�p���Ă�����
		PADVIB_MAX
	};
	enum E_DIRECTION
	{// �X�e�B�b�N�̃g���K�[
		DIRECTION_UP = 0,	// ��
		DIRECTION_DOWN,	// ��
		DIRECTION_RIGHT,	// �E
		DIRECTION_LEFT,	// ��
		DIRECTION_MAX
	};

	CInputJoypad();	// �R���X�g���N�^
	~CInputJoypad();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����

	// �ϐ��擾�E�ݒ�֐�
	bool GetPress(E_PADBUTTONS nKey, int nPlayer);	// �{�^���v���X
	bool GetTrigger(E_PADBUTTONS nKey, int nPlayer);	// �{�^���g���K�[
	bool GetRelease(E_PADBUTTONS nKey, int nPlayer);	// �{�^�������[�X
	int GetRepeat(E_PADBUTTONS nKey, int nPlayer);	// �{�^�����s�[�g
	float GetJoyStickLX(int nPlayer);	// ���W���C�X�e�B�b�N�X��
	float GetJoyStickLY(int nPlayer);
	float GetJoyStickRX(int nPlayer);	// �E�W���C�X�e�B�b�N�X��
	float GetJoyStickRY(int nPlayer);
	bool GetLStickTrigger(E_DIRECTION direction,int nPlayer);	// ���W���C�X�e�B�b�N�e��
	D3DXVECTOR3 GetVecStickL(void);	// ���W���C�X�e�B�b�N�X��
	void Vibration(int nPlayer, E_STATE_PADVIB state, short sVib, int nTime);	// �o�C�u���[�V�����ݒ�

	// �ÓI�����o�֐�
	static CInputJoypad *Create(void);	// ��������
	static CInputJoypad *GetInstance(void) { return s_pJoyPad; }	// �C���X�^���X�̎擾

private:
	// �����o�֐�
	void CheckStickTrigger(XINPUT_STATE state,int nPlayer);	// �X�e�B�b�N�̃g���K�[����m�F

	// �����o�ϐ�
	XINPUT_STATE m_aState[Joypad::MAX_PLAYER];				//�Q�[���p�b�h�̃v���X���
	XINPUT_STATE m_aStateTrigger[Joypad::MAX_PLAYER];		//�Q�[���p�b�h�̃g���K�[���
	XINPUT_STATE m_aStateRelease[Joypad::MAX_PLAYER];		//�Q�[���p�b�h�̃����[�X���
	XINPUT_STATE m_aStateRepeat[Joypad::MAX_PLAYER];			//�Q�[���p�b�h�̃��s�[�g���
	XINPUT_VIBRATION m_aVibration[Joypad::MAX_PLAYER];		//�Q�[���p�b�h�̐U�����
	E_STATE_PADVIB m_aVibState[Joypad::MAX_PLAYER];					//�U���̏��
	int m_nVibTimer;		// �o�C�u���[�V�����̃^�C�}�[
	int m_aCntRepeat[Joypad::MAX_PLAYER][PADBUTTONS_MAX];	// ���s�[�g�J�E���^�[
	bool m_abTrigggerLStick[Joypad::MAX_PLAYER][DIRECTION_MAX];	// �X�e�B�b�N�̃g���K�[����

	// �ÓI�����o�ϐ�
	static CInputJoypad *s_pJoyPad;	// ���g�̃|�C���^
};

#endif
