//*****************************************************
//
// �����_���[�̏���[renderer.h]
// Author:���R����
//
//*****************************************************
#ifndef _RENDERER_H_	// ��d�C���N���[�h�h�~
#define _RENDERER_H_

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CRenderer
{
public:
	CRenderer();	// �R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^

	// �����o�֐�
	static CRenderer *Create(HWND hWnd, BOOL bWindow);
	HRESULT Init(HWND hWnd, BOOL bWindow);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void DrawFPS(void);	//FPS�\������
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// �f�o�C�X�̎擾

	// �ÓI�����o�֐�
	static bool IsFog(void) { return s_bFog; }
	static void EnableFog(bool bFog) { s_bFog = bFog; }
	static CRenderer *GetInstance(void) { return s_pRenderer; }

private:
	// �����o�ϐ�
	LPDIRECT3D9 m_pD3D;	// �I�u�W�F�N�g�̐���
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// �f�o�C�X

	// �ÓI�����o�ϐ�
	static bool s_bFog;	// �t�H�O�������邩�ǂ���
	static CRenderer *s_pRenderer;	// ���g�̃|�C���^
};

namespace Renderer
{
//*****************************************************
// �V���[�g�J�b�g�֐�
//*****************************************************
LPDIRECT3DDEVICE9 GetDevice(void);	// �f�o�C�X�̎擾
}

#endif