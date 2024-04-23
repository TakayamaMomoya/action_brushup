//*****************************************************
//
// �����L���O�̏���[Ranking.h]
// Author:���R����
//
//*****************************************************

#ifndef _RANKING_H_
#define _RANKING_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include"scene.h"
#include "number.h"

//*****************************************************
// �O���錾
//*****************************************************
class CSkybox;

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_RANK	(5) // �����L���O�̐�

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CRanking : public CScene
{
public:
	//�j���[���R�[�h�����̏��
	typedef enum
	{
		STATE_NORMAL = 0,					//�ʏ���
		STATE_DIFF,							//�F���ς���Ă�����
		STATE_MAX
	}STATE;

	CRanking();	// �R���X�g���N�^
	~CRanking();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Reset(void);
	void Set(int nScore);
	void Save(void);
	void Load(void);

private:
	void Sort(void);

	int m_nScore;	// �X�R�A�̒l
	int m_nRankUpdate = -1;	// �X�V�����NNo.
	int m_aScore[NUM_RANK];	// �����L���O�X�R�A
	STATE m_state = STATE_NORMAL;	// �j���[���R�[�h�̓_�ŏ��
	int m_nCntState;	// ��ԑJ�ڃJ�E���^
	int m_nTimerTrans;	// ��ʑJ�ڃJ�E���^�[
	CNumber *m_apNumber[NUM_RANK];	// �����L���O�̐���
	CSkybox *m_pSkybox;	// �X�J�C�{�b�N�X
};

#endif