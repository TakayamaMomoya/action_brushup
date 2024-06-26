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

	// �ϐ��擾�E�ݒ�֐�
	CCamera *GetCamera(void) { return m_pCamera; }	// �J�����擾
	CLight *GetLight(void) { return m_pLight; }	// ���C�g�擾
	void SetMode(CScene::E_MODE mode);	// ���[�h�̐ݒ�
	CScene::E_MODE GetMode(void) { return m_mode; }	// ���[�h�̎擾
	void SetScore(int nScore) { m_nScore = nScore; }	// �X�R�A�̐ݒ�
	int GetScore(void) { return m_nScore; }	// �X�R�A�̎擾
	void SetDeltaTime(float fValue) { m_fDeltaTime = fValue; }	// �f���^�^�C���̐ݒ�
	float GetDeltaTime(void) { return m_fDeltaTime; }	// �f���^�^�C���̎擾

	// �ÓI�����o�֐�
	static CManager *Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// ��������
	static CManager *GetInstace(void) { return s_pManager; };	// �C���X�^���X�̎擾
private:
	// �����o�ϐ�
	CCamera *m_pCamera;	// �J�����̃|�C���^
	CLight *m_pLight;	// ���C�g�̃|�C���^
	CScene *m_pScene;	// ���݂̃V�[��
	CScene::E_MODE m_mode;	// ���݂̃��[�h
	int m_nScore;	// �X�R�A
	float m_fDeltaTime;	// �O��̃t���[�����炩����������

	// �ÓI�����o�ϐ�
	static CManager *s_pManager;	// ���g�̃|�C���^
};

namespace Manager
{
//*****************************************************
// �V���[�g�J�b�g�֐�
//*****************************************************
CCamera *GetCamera(void);	// �J�����擾
CLight *GetLight(void);	// ���C�g�擾
void SetMode(CScene::E_MODE mode);	// ���[�h�̐ݒ�
CScene::E_MODE GetMode(void);	// ���[�h�̎擾
void SetScore(int nScore);	// �X�R�A�̐ݒ�
int GetScore(void);	// �X�R�A�̎擾
float GetDeltaTime(void);	// �f���^�^�C���̎擾
}

#endif