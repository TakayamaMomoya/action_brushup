//*****************************************************
//
// �X�R�A�̏���[score.h]
// Author:���R����
//
//*****************************************************
#ifndef _SCORE_H_	// ��d�C���N���[�h�h�~
#define _SCORE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CNumber;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CScore : public CObject
{
public:
	CScore();	// �R���X�g���N�^
	~CScore();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void) {}	// �`��
	void SetResultScore(void);	// �ŏI�X�R�A�̐ݒ�

	// �ϐ��擾�E�ݒ�֐�
	int AddScore(int nValue);	// �X�R�A
	int GetScore(void) { return m_nSocreDest; }

	// �ÓI�����o�֐�
	static CScore *Create(void);	// ��������
	static CScore *GetInstance(void) { return s_pScore; }	// �C���X�^���X�̎擾

private:
	// �����o�ϐ�
	CNumber *m_pObjNumber;	// �X�R�A�l�̃|�C���^
	int m_nScore;	// �X�R�A�̒l
	int m_nSocreDest;	// �ڕW�̃X�R�A�l
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
	
	// �ÓI�����o�ϐ�
	static CScore *s_pScore;	// ���g�̃|�C���^
};

#endif
