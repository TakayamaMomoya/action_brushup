//*****************************************************
//
// �V�[������[scene.h]
// Author:���R����
//
//*****************************************************
#ifndef _SCENE_H_	// ��d�C���N���[�h�h�~
#define _SCENE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"

//*****************************************************
// �O���錾
//*****************************************************
class CPlayer;
class CMeshField;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CScene
{
public:
	// �񋓌^��`
	enum E_MODE
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RANKING,
		MODE_MAX
	};

	CScene();	// �R���X�g���N�^
	~CScene();	// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void);	// ����������
	virtual void Uninit(void);	// �I������
	virtual void Update();	// �X�V����
	virtual void Draw();	// �`��

	// �ϐ��擾�E�ݒ�֐�
	int GetTimer(void) { return m_nTimerTrans; }	// ��ԑJ�ڃ^�C�}�[
	void SetTimer(int nTime) { m_nTimerTrans = nTime; }

	// �ÓI�����o�֐�
	static CScene *Create(E_MODE mode);	// ��������

private:
	int m_nTimerTrans;	// �J�ڃ^�C�}�[
};

#endif