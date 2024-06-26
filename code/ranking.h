//*****************************************************
//
// �����L���O�̏���[Ranking.h]
// Author:���R����
//
//*****************************************************
#ifndef _RANKING_H_	// ��d�C���N���[�h�h�~
#define _RANKING_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include"scene.h"
#include "number.h"

//*****************************************************
// �O���錾
//*****************************************************
class CMeshCylinder;

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
	// �񋓌^��`
	enum E_STATE
	{//�j���[���R�[�h�����̏��
		STATE_NORMAL = 0,	//�ʏ���
		STATE_DIFF,	//�F���ς���Ă�����
		STATE_MAX
	};

	CRanking();	// �R���X�g���N�^
	~CRanking();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void Reset(void);	// �����L���O�̃��Z�b�g
	void Set(int nScore);	// �����L���O�ݒ�
	void Save(void);	// �ۑ�
	void Load(void);	// �Ǎ�

private:
	// �����o�֐�
	void Sort(void);	// �\�[�g����

	// �����o�ϐ�
	int m_nScore;	// �X�R�A�̒l
	int m_nRankUpdate = -1;	// �X�V�����NNo.
	int m_aScore[NUM_RANK];	// �����L���O�X�R�A
	E_STATE m_state = STATE_NORMAL;	// �j���[���R�[�h�̓_�ŏ��
	int m_nCntState;	// ��ԑJ�ڃJ�E���^
	int m_nTimerTrans;	// ��ʑJ�ڃJ�E���^�[
	CNumber *m_apNumber[NUM_RANK];	// �����L���O�̐���
	CMeshCylinder *m_pCylinder;	// �V�����_�[
};

#endif