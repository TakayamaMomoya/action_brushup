//*****************************************************
//
// �|�[�Y�̏���[pause.h]
// Author:���R����
//
//*****************************************************
#ifndef _PAUSE_H_	// ��d�C���N���[�h�h�~
#define _PAUSE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CObject2D;

//*****************************************************
// �N���X��`
//*****************************************************
class CPause : CObject
{
public:
	CPause();	// �R���X�g���N�^
	~CPause();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	// �ÓI�����o�֐�
	static CPause *Create(void);	// ��������
	static CPause *GetInstance(void) { return m_pPause; }	// �C���X�^���X�̎擾

private:
	// �񋓌^��`
	enum E_MENU
	{// ���ڂ̎��
		MENU_RESUME = 0,	// �ĊJ
		MENU_RESTART,	// ���g���C
		MENU_CHECKPOINT,	// �`�F�b�N�|�C���g����ĊJ
		MENU_QUIT,	// �I��
		MENU_MAX
	};
	enum E_STATE
	{
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_IN,	// �t�F�[�h�C�����
		STATE_OUT,	// �t�F�[�h�A�E�g���
		STATE_MAX
	};

	// �����o�֐�
	void ManageState(void);	// ��ԊǗ�
	void ManageBg(void);	// �w�i�̊Ǘ�
	void Input(void);	// ���͏���
	void Fade(E_MENU menu);	// �t�F�[�h���鏈��

	// �����o�ϐ�
	E_MENU m_menu;	// �I������
	CObject2D *m_apMenu[MENU_MAX];	// ���j���[���ڂ̂QD�I�u�W�F�N�g
	CObject2D *m_pBg;	// �w�i�QD�I�u�W�F�N�g
	D3DXVECTOR3 m_aPosDest[MENU_MAX];	// �ڕW�̈ʒu
	E_STATE m_state;	// ���

	// �ÓI�����o�֐�
	static CPause *m_pPause;	// ���g�̃|�C���^
};

#endif