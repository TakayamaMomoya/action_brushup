//*****************************************************
//
// 2Dエフェクト処理[effect2D.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "effect2D.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define SPEED_MOVE	(7.0f)	// 移動速度

//=====================================================
// コンストラクタ
//=====================================================
CEffect2D::CEffect2D(int nPriority) : CObject2D(nPriority),m_nLife(0),m_fDecrease(0.0f)
{

}

//=====================================================
// デストラクタ
//=====================================================
CEffect2D::~CEffect2D()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEffect2D::Init(void)
{
	// 継承クラスの初期化
	CObject2D::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEffect2D::Uninit(void)
{
	// 継承クラスの終了
	CObject2D::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEffect2D::Update(void)
{
	// 寿命減衰
	m_nLife--;

	// サイズ縮小
	SetSize(GetSize().x - m_fDecrease, GetSize().y - m_fDecrease);

	// 継承クラスの更新
	CObject2D::Update();

	if (m_nLife < 0)
	{// 自分の削除
		Uninit();
	}

	// 頂点座標設定
	SetVtx();
}

//=====================================================
// 描画処理
//=====================================================
void CEffect2D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 継承クラスの描画
	CObject2D::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=====================================================
// 生成処理
//=====================================================
CEffect2D *CEffect2D::Create(D3DXVECTOR3 pos, float fRadius, int nLife, D3DXCOLOR col, D3DXVECTOR3 move)
{
	CEffect2D *pEffect2D = nullptr;

	if (pEffect2D == nullptr)
	{// インスタンス生成
		pEffect2D = new CEffect2D;
	}
	
	// 初期化処理
	pEffect2D->Init();

	pEffect2D->SetPosition(pos);
	pEffect2D->SetSize(fRadius, fRadius);

	pEffect2D->m_nLife = nLife;

	pEffect2D->m_fDecrease = fRadius / nLife;

	pEffect2D->SetMove(move);

	pEffect2D->SetCol(col);

	return pEffect2D;
}