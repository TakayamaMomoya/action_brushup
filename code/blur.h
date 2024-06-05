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

    void Init(void); // ������

private:
    // �����o�֐�
    void CreatePolygon(void);

    // �����o�ϐ�
    LPDIRECT3DTEXTURE9 m_apTextureMT[Blur::NUM_RENDER];    // �����_�����O�^�[�Q�b�g�p�e�N�X�`��
    LPDIRECT3DSURFACE9 m_apRenderMT[Blur::NUM_RENDER]; // �^�[�Q�b�g�����_�����O�p�C���^�[�t�F�[�X
    LPDIRECT3DSURFACE9 m_pZBuffMT;  // �^�[�Q�b�g�����_�����O�pZ�o�b�t�@
    D3DVIEWPORT9 m_viewpotrMT;  // �^�[�Q�b�g�����_�����O�p�r���[�|�[�g
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMT;   // �t�B�[�h�o�b�N�p�|���S���̒��_�o�b�t�@
    float m_fAlpha; // �d�˂�|���S���̓����x
    float m_fDiffPolygon;   // �|���S���̍����̑傫��
    D3DXCOLOR m_colPolygon; // �|���S���̐F
};

#endif
