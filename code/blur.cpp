//*****************************************************
//
// ブラーの処理[blur.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "blur.h"
#include "renderer.h"

//=====================================================
// コンストラクタ
//=====================================================
CBlur::CBlur() : m_colPolygon{}, m_apRenderMT{}, m_apTextureMT{}, m_viewpotrMT(), m_pZBuffMT(nullptr), m_pVtxBuffMT(nullptr), m_fDiffPolygon(0.0f), m_fAlpha(0.0f)
{

}

//=====================================================
// デストラクタ
//=====================================================
CBlur::~CBlur()
{

}

//=====================================================
// 初期化
//=====================================================
void CBlur::Init(void)
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

    for (int i = 0; i < Blur::NUM_RENDER; i++)
    {
        // レンダーターゲット用のテクスチャ生成
        if (SUCCEEDED(pDevice->CreateTexture(SCREEN_WIDTH,
            SCREEN_HEIGHT,
            1,
            D3DUSAGE_RENDERTARGET,
            D3DFMT_X8R8G8B8,
            D3DPOOL_DEFAULT,
            &m_apTextureMT[i],
            NULL)))
        {
            // ターゲットレンダリング用インターフェイス生成
            if (FAILED(m_apTextureMT[0]->GetSurfaceLevel(0, &m_apRenderMT[i])))
            {
                assert(("ターゲットレンダリング用インターフェース生成に失敗", false));
            }
        }
        else
        {
            assert(("レンダーターゲット用のテクスチャ生成に失敗", false));
        }
    }

    // ターゲットレンダリング用Zバッファ生成
    if (FAILED(pDevice->CreateDepthStencilSurface(SCREEN_WIDTH,
        SCREEN_HEIGHT,
        D3DFMT_D16,
        D3DMULTISAMPLE_NONE,
        0,
        TRUE,
        &m_pZBuffMT,
        NULL)))
    {
        assert(("ターゲットレンダリング用Zバッファ生成に失敗", false));
    }

    // レンダリングターゲットとZバッファを保存
    LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;

    pDevice->GetRenderTarget(0, &pRenderDef);
    pDevice->GetDepthStencilSurface(&pZBuffDef);

    for (int i = 0; i < 2; i++)
    {
        // レンダリングターゲットとZバッファを設定
        pDevice->SetRenderTarget(0, m_apRenderMT[i]);
        pDevice->SetDepthStencilSurface(m_pZBuffMT);

        // クリアする
        pDevice->Clear(0, nullptr,
            (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
            D3DCOLOR_RGBA(255, 0, 0, 0), 1.0f, 0);
    }

    // レンダリングターゲットとZバッファを元に戻す
    pDevice->SetRenderTarget(0, pRenderDef);
    pDevice->SetDepthStencilSurface(pZBuffDef);

    // ビューポート初期化
    m_viewpotrMT.X = 0;
    m_viewpotrMT.Y = 0;
    m_viewpotrMT.Width = SCREEN_WIDTH;
    m_viewpotrMT.Height = SCREEN_HEIGHT;
    m_viewpotrMT.MinZ = 0.0f;
    m_viewpotrMT.MaxZ = 1.0f;

    // ポリゴンの生成
    CreatePolygon();
}

//=====================================================
// ポリゴンの生成
//=====================================================
void CBlur::CreatePolygon(void)
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

    // 頂点バッファの生成
    if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &m_pVtxBuffMT,
        NULL)))
    {
        assert(("頂点バッファの生成に失敗", false));
    }

    //頂点情報のポインタ
    VERTEX_2D *pVtx;

    //頂点バッファをロックし、頂点情報へのポインタを取得
    m_pVtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

    //頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

    //法線ベクトルの設定
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //頂点カラーの設定
    pVtx[0].col = m_colPolygon;
    pVtx[1].col = m_colPolygon;
    pVtx[2].col = m_colPolygon;
    pVtx[3].col = m_colPolygon;

    //テクスチャ座標
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    //頂点バッファをアンロック
    m_pVtxBuffMT->Unlock();
}