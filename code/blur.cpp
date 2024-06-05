//*****************************************************
//
// �u���[�̏���[blur.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "blur.h"
#include "renderer.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CBlur::CBlur() : m_colPolygon{}, m_apRenderMT{}, m_apTextureMT{}, m_viewpotrMT(), m_pZBuffMT(nullptr), m_pVtxBuffMT(nullptr), m_fDiffPolygon(0.0f), m_fAlpha(0.0f)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBlur::~CBlur()
{

}

//=====================================================
// ������
//=====================================================
void CBlur::Init(void)
{
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

    for (int i = 0; i < Blur::NUM_RENDER; i++)
    {
        // �����_�[�^�[�Q�b�g�p�̃e�N�X�`������
        if (SUCCEEDED(pDevice->CreateTexture(SCREEN_WIDTH,
            SCREEN_HEIGHT,
            1,
            D3DUSAGE_RENDERTARGET,
            D3DFMT_X8R8G8B8,
            D3DPOOL_DEFAULT,
            &m_apTextureMT[i],
            NULL)))
        {
            // �^�[�Q�b�g�����_�����O�p�C���^�[�t�F�C�X����
            if (FAILED(m_apTextureMT[0]->GetSurfaceLevel(0, &m_apRenderMT[i])))
            {
                assert(("�^�[�Q�b�g�����_�����O�p�C���^�[�t�F�[�X�����Ɏ��s", false));
            }
        }
        else
        {
            assert(("�����_�[�^�[�Q�b�g�p�̃e�N�X�`�������Ɏ��s", false));
        }
    }

    // �^�[�Q�b�g�����_�����O�pZ�o�b�t�@����
    if (FAILED(pDevice->CreateDepthStencilSurface(SCREEN_WIDTH,
        SCREEN_HEIGHT,
        D3DFMT_D16,
        D3DMULTISAMPLE_NONE,
        0,
        TRUE,
        &m_pZBuffMT,
        NULL)))
    {
        assert(("�^�[�Q�b�g�����_�����O�pZ�o�b�t�@�����Ɏ��s", false));
    }

    // �����_�����O�^�[�Q�b�g��Z�o�b�t�@��ۑ�
    LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;

    pDevice->GetRenderTarget(0, &pRenderDef);
    pDevice->GetDepthStencilSurface(&pZBuffDef);

    for (int i = 0; i < 2; i++)
    {
        // �����_�����O�^�[�Q�b�g��Z�o�b�t�@��ݒ�
        pDevice->SetRenderTarget(0, m_apRenderMT[i]);
        pDevice->SetDepthStencilSurface(m_pZBuffMT);

        // �N���A����
        pDevice->Clear(0, nullptr,
            (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
            D3DCOLOR_RGBA(255, 0, 0, 0), 1.0f, 0);
    }

    // �����_�����O�^�[�Q�b�g��Z�o�b�t�@�����ɖ߂�
    pDevice->SetRenderTarget(0, pRenderDef);
    pDevice->SetDepthStencilSurface(pZBuffDef);

    // �r���[�|�[�g������
    m_viewpotrMT.X = 0;
    m_viewpotrMT.Y = 0;
    m_viewpotrMT.Width = SCREEN_WIDTH;
    m_viewpotrMT.Height = SCREEN_HEIGHT;
    m_viewpotrMT.MinZ = 0.0f;
    m_viewpotrMT.MaxZ = 1.0f;

    // �|���S���̐���
    CreatePolygon();
}

//=====================================================
// �|���S���̐���
//=====================================================
void CBlur::CreatePolygon(void)
{
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

    // ���_�o�b�t�@�̐���
    if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &m_pVtxBuffMT,
        NULL)))
    {
        assert(("���_�o�b�t�@�̐����Ɏ��s", false));
    }

    //���_���̃|�C���^
    VERTEX_2D *pVtx;

    //���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    m_pVtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

    //���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

    //�@���x�N�g���̐ݒ�
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //���_�J���[�̐ݒ�
    pVtx[0].col = m_colPolygon;
    pVtx[1].col = m_colPolygon;
    pVtx[2].col = m_colPolygon;
    pVtx[3].col = m_colPolygon;

    //�e�N�X�`�����W
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    //���_�o�b�t�@���A�����b�N
    m_pVtxBuffMT->Unlock();
}