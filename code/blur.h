//*****************************************************
//
// �u���[�̏���[blur.h]
// Author:���R����
//
//*****************************************************

#ifndef _BLUR_H_    // ��d�C���N���[�h�̖h�~
#define _BLUR_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace Blur
{
const int NUM_RENDER = 2;   // �^�[�Q�b�g�����_�����O�p�̃C���^�[�t�F�[�X�̐�
}

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CBlur
{
public:
	CBlur();	// �R���X�g���N�^
	~CBlur();	// �f�X�g���N�^

    // �����o�֐�
    void Init(void); // ������
    void Uninit(void);  // �I��
    void SaveRenderInfo(void);  // �`��ɕK�v�ȗv�f��ۑ�����
    void ChangeTarget(void);    // �����_�[�^�[�Q�b�g�̕ύX
    void OverlapLastTexture(void);  // �O��̃e�N�X�`�����d�˂�
    void RestoreTarget(void);   // �����_�[�^�[�Q�b�g�̕���
    void DrawBuckBuffer(void);   // �o�b�N�o�b�t�@�ւ̕`��
    void SwapBuffer(void);  // �o�b�t�@�[�̓���ւ�

    // �ÓI�����o�֐�
    static CBlur *Create(void);   // ����
    static CBlur *GetInstance(void) { return m_pBlur; }    // �擾����

private:
    // �����o�֐�
    void CreatePolygon(void);

    // �����o�ϐ�
    LPDIRECT3DTEXTURE9 m_apTextureMT[Blur::NUM_RENDER];    // �����_�����O�^�[�Q�b�g�p�e�N�X�`��
    LPDIRECT3DSURFACE9 m_apRenderMT[Blur::NUM_RENDER]; // �^�[�Q�b�g�����_�����O�p�C���^�[�t�F�[�X
    LPDIRECT3DSURFACE9 m_pZBuffMT;  // �^�[�Q�b�g�����_�����O�pZ�o�b�t�@
    D3DVIEWPORT9 m_viewpotrMT;  // �^�[�Q�b�g�����_�����O�p�r���[�|�[�g
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMT;   // �t�B�[�h�o�b�N�p�|���S���̒��_�o�b�t�@
    LPDIRECT3DSURFACE9 m_pRenderDef;    // �ۑ��p�̃C���^�[�t�F�C�X
    LPDIRECT3DSURFACE9 m_pZBuffDef; // �ۑ��p��Z�o�b�t�@
    D3DVIEWPORT9 m_viewportDef; // �ۑ��p�̃r���[�|�[�g
    D3DXMATRIX m_mtxViewDef;    // �ۑ��p�̃r���[�}�g���b�N�X
    D3DXMATRIX m_mtxProjDef;    // �ۑ��p�̃v���W�F�N�V�����}�g���b�N�X
    float m_fAlpha; // �d�˂�|���S���̓����x
    float m_fDiffPolygon;   // �|���S���̍����̑傫��
    D3DXCOLOR m_colPolygon; // �|���S���̐F

    // �ÓI�����o�ϐ�
    static CBlur *m_pBlur;  // ���g�̃|�C���^
};

#endif
