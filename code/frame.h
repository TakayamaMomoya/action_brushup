//*****************************************************
//
// �t���[���̏���[frame.h]
// Author:���R����
//
//*****************************************************

#ifndef _FRAME_H_
#define _FRAME_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CObject2D;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CFrame	: public CObject
{
public:
	CFrame(int nPriority = 0);
	~CFrame();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	// �ÓI�����o�֐�
	static CFrame *Create(int nTimeIn, int nTimeWait, int nTimeOut);	// ��������

private:
	// �񋓌^��`
	enum STATE
	{// ���
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_IN,	// �C�����
		STATE_WAIT,	// �ҋ@���
		STATE_OUT,	// �A�E�g���
		STATE_MAX
	};

	// �\���̒�`
	struct SInfo
	{// ���g�̏��
		CObject2D *pUpper;
		CObject2D *pUnder;
		STATE state;
		int nTimeIn;
		int nTimeWait;
		int nTimeOut;
		int nCntFade;
	};

	// �����o�֐�
	void ManageState(void);
	void ManageUpper(void);
	void ManageUnder(void);

	// �����o�ϐ�
	SInfo m_info;
};

#endif