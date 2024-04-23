//*****************************************************
//
// �X�R�A�̏���[score.h]
// Author:���R����
//
//*****************************************************

#ifndef _SCORE_H_
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

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {}
	static CScore *Create(void);
	int AddScore(int nValue);
	void SetPosition(D3DXVECTOR3 pos) {};
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(); }
	D3DXVECTOR3 GetPositionOld(void) { return D3DXVECTOR3(); };	// �ʒu�擾����
	float GetWidth(void) { return 0.0f; }	// �T�C�Y�擾
	float GetHeight(void) { return 0.0f; }	// �T�C�Y�擾
	int GetScore(void) { return m_nSocreDest; }
	static CScore *GetInstance(void) { return m_pScore; }
	void SetResultScore(void);

private:
	CNumber *m_pObjNumber;	// �X�R�A�l�̃|�C���^
	int m_nScore;	// �X�R�A�̒l
	int m_nSocreDest;	// �ڕW�̃X�R�A�l
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
	static CScore *m_pScore;	// ���g�̃|�C���^
};

#endif
