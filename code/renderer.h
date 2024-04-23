//*****************************************************
//
// �����_���[�̏���[renderer.h]
// Author:���R����
//
//*****************************************************

#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CRenderer
{
public:
	CRenderer();	// �R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^

	static CRenderer *Create(HWND hWnd, BOOL bWindow);
	HRESULT Init(HWND hWnd, BOOL bWindow);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void DrawFPS(void);	//FPS�\������
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// �f�o�C�X�̎擾
	static bool IsFog(void) { return m_bFog; }
	static void EnableFog(bool bFog) { m_bFog = bFog; }
	static CRenderer *GetInstance(void) { return m_pRenderer; }

private:
	LPDIRECT3D9 m_pD3D;	// �I�u�W�F�N�g�̐���
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// �f�o�C�X
	static bool m_bFog;	// �t�H�O�������邩�ǂ���

	static CRenderer *m_pRenderer;	// ���g�̃|�C���^
};

namespace Renderer
{
LPDIRECT3DDEVICE9 GetDevice(void);
}

#endif