//*****************************************************
//
// �}�l�[�W���[����[manager.h]
// Author:���R����
//
//*****************************************************
#ifndef _MANAGER_H_	// ��d�C���N���[�h�h�~
#define _MANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "scene.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCamera;
class CLight;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CManager
{
public:
	CManager();	// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^

	// �����o�ϐ�
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
	void Uninit(void);
	void Update();
	void Draw();

	// �ÓI�����o�֐�
	static CCamera *GetCamera(void) { return m_pCamera; }	// �J�����擾
	static CLight *GetLight(void) { return m_pLight; }	// ���C�g�擾
	static void SetMode(CScene::MODE mode);	// ���[�h�̐ݒ�
	static CScene::MODE GetMode(void) { return m_mode; }	// ���[�h�̎擾
	static void SetScore(int nScore) { m_nScore = nScore; }	// �X�R�A�̐ݒ�
	static int GetScore(void) { return m_nScore; }	// �X�R�A�̎擾
	static void SetDeltaTime(float fValue) { m_fDeltaTime = fValue; }	// �f���^�^�C���̐ݒ�
	static float GetDeltaTime(void) { return m_fDeltaTime; }	// �f���^�^�C���̎擾

private:
	// �ÓI�����o�ϐ�
	static CCamera *m_pCamera;	// �J�����̃|�C���^
	static CLight *m_pLight;	// ���C�g�̃|�C���^
	static CScene *m_pScene;	// ���݂̃V�[��
	static CScene::MODE m_mode;	// ���݂̃��[�h
	static int m_nScore;	// �X�R�A
	static float m_fDeltaTime;	// �O��̃t���[�����炩����������
};

#endif