//*****************************************************
//
// X�t�@�C�����f���̏���[model.h]
// Author:���R����
//
//*****************************************************
#ifndef _MODEL_H_	// ��d�C���N���[�h�h�~
#define _MODEL_H_

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_MODEL	(256)	// ���f���̐�

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CModel
{
public:
	typedef struct
	{// ���f���̍\����
		int *pIdxTexture;	// �e�N�X�`���ԍ��ւ̃|�C���^
		LPD3DXMESH pMesh;		//���b�V���ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;	//�}�e���A���ւ̃o�b�t�@
		DWORD dwNumMat;	//�}�e���A���̐�
	}Model;

	CModel();	// �R���X�g���N�^
	~CModel();	// �f�X�g���N�^
	
	// �ÓI�����o�֐�
	static int Load(char *pPath);	// �Ǎ�
	static void Unload(void);	// �j��
	static void Init(int nIdx);	// ������
	static Model *GetModel(int nIdx) { return m_apModel[nIdx]; }	// ���f���̎擾	
	static int GetNumAll(void) { return m_nNumAll; }// �����擾

private:
	// �ÓI�����o�ϐ�
	static Model *m_apModel[NUM_MODEL];	// ���f���ւ̃|�C���^
	static char m_aPath[NUM_MODEL][256];	// ���f���̃t�@�C����
	static int m_nNumAll;	// ����
};

#endif