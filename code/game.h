//*****************************************************
//
// �Q�[������[game.h]
// Author:���R����
//
//*****************************************************
#ifndef _GAME_H_	// ��d�C���N���[�h�h�~
#define _GAME_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "scene.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGame : public CScene
{
public:
	// �񋓌^��`
	enum E_STATE
	{// ���
		STATE_NONE,	// �������Ă��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_BOSS,	// �{�X����
		STATE_RESULT,	// ���U���g���
		STATE_END,	// �I�����
		STATE_MAX
	};

	CGame();	// �R���X�g���N�^
	~CGame();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update();	// �X�V����
	void Draw();	// �`��

	// �ϐ��擾�E�ݒ�֐�
	void EnableStop(bool bStop) { m_bStop = bStop; }	// ��~���
	int GetProgress(void) { return m_nProgress; }	// �i�s�x

	// �ÓI�����o�֐�
	static void SetState(E_STATE state) { m_state = state; }	// ���
	static E_STATE GetState(void) { return m_state; }
	static void SetProgress(int nProgress) { m_nProgress = nProgress; }	// �i�s�x
	static CGame *GetInstance(void) { return m_pGame; }	// �C���X�^���X�̎擾

private:
	// �����o�֐�
	void LoadCheckPoint(void);	// �`�F�b�N�|�C���g�Ǎ�
	void CreateTutorial(void);	// �`���[�g���A������
	void ManageState(void);	// ��ԊǗ�
	void Debug(void);	// �f�o�b�O����

	// �����o�֐�
	D3DXVECTOR3 *m_pPosCheckPoint;	// �`�F�b�N�|�C���g���W�̃|�C���^
	int m_nNumCheckPoint;	// �`�F�b�N�|�C���g�̐�
	int m_nCntState;	// ��ԑJ�ڃJ�E���^�[
	bool m_bStop;	// ��~���

	// �ÓI�����o�֐�
	static E_STATE m_state;	// ���
	static int m_nProgress;	// �i�s�x
	static CGame *m_pGame;	// ���g�̃|�C���^
};

#endif