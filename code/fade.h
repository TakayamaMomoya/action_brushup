//*****************************************************
//
// �t�F�[�h����[fade.h]
// Author:���R����
//
//*****************************************************
#ifndef _FADE_H_	// ��d�C���N���[�h�h�~
#define _FADE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object2D.h"
#include "scene.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CFade
{
public:
	// �񋓌^��`
	enum E_STATE
	{// ���
		STATE_NONE = 0,	// �������Ă��Ȃ����
		STATE_IN,	// �t�F�[�h�C�����
		STATE_OUT,	// �t�F�[�h�A�E�g���
		STATE_MAX
	};

	CFade();	// �R���X�g���N�^
	~CFade();	// �f�X�g���N�^
	
	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	// �ϐ��擾�E�ݒ�֐�
	void SetFade(CScene::MODE modeNext);	// �t�F�[�h���J�n���鏈��
	E_STATE GetState(void);	// ���

	// �ÓI�����o�֐�
	static CFade *Create(void);	// ��������
	static CFade *GetInstance(void) { return m_pFade; }	// �C���X�^���X�̎擾

private:
	// �����o�ϐ�
	E_STATE m_fade;	// �t�F�[�h�̏��
	CScene::MODE m_modeNext;	// �t�F�[�h��̉��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	D3DXCOLOR m_col;	// �|���S���̐F

	// �ÓI�����o�ϐ�
	static CFade *m_pFade;	// ���g�̃|�C���^
};
#endif
