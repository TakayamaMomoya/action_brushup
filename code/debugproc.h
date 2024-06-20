//*****************************************************
//
// �f�o�b�O�\������ [debugproc.h]
// Author:���R����
//
//*****************************************************
#ifndef _DEBUGPROC_H_	// ��d�C���N���[�h�h�~
#define _DEBUGPROC_H_

//*****************************************************
// �}�N����`��`
//*****************************************************
#define MAX_DEBUGSTRING (2048)	// �f�o�b�O�̍ő啶����

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CDebugProc
{
public:
	CDebugProc();	// �R���X�g���N�^
	~CDebugProc();	// �f�X�g���N�^

	// �����o�֐�
	void Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void Print(const char *fmt, ...);	// �����̑��

	// �ÓI�����o�֐�
	static CDebugProc *Create(void);
	static CDebugProc *GetInstance(void) { return s_pDebugProc; }

private:
	// �����o�ϐ�
	char m_aStr[MAX_DEBUGSTRING];	// �f�o�b�O�\���p�̕�����
	bool m_bDisp;		// �f�o�b�O�\����ON/OFF

	// �ÓI�����o�ϐ�
	static LPD3DXFONT s_pFont;	// �t�H���g�ւ̃|�C���^
	static CDebugProc *s_pDebugProc;	// ���g�̃|�C���^
};

#endif