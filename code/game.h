//*****************************************************
//
// �Q�[������[game.h]
// Author:���R����
//
//*****************************************************
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "scene.h"

//*****************************************************
// �O���錾
//*****************************************************
class CScore;
class CTimer;
class CGame;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGame : public CScene
{
public:
	enum STATE
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

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update();
	virtual void Draw();
	static void SetState(STATE state) { m_state = state; }
	static STATE GetState(void) { return m_state; }
	static void SetProgress(int nProgress) { m_nProgress = nProgress; }
	void EnableStop(bool bStop) { m_bStop = bStop; }
	static CGame *GetInstance(void) { return m_pGame; }
	int GetProgress(void) { return m_nProgress; }

private:
	void LoadCheckPoint(void);
	void CreateTutorial(void);
	void ManageState(void);
	void Debug(void);

	static STATE m_state;	// ���
	static int m_nProgress;	// �i�s�x����
	static CGame *m_pGame;	// ���g�̃|�C���^

	D3DXVECTOR3 *m_pPosCheckPoint;	// �`�F�b�N�|�C���g���W�̃|�C���^
	int m_nNumCheckPoint;	// �`�F�b�N�|�C���g�̐�
	int m_nCntState;	// ��ԑJ�ڃJ�E���^�[
	bool m_bStop;	// ��~���
};

#endif