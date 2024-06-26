//*****************************************************
//
// フェード処理[fade.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "fade.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float FADE_SPEED = 0.05f;	// フェードのスピード
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CFade *CFade::s_pFade = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CFade::CFade() : m_fade(STATE_NONE), m_modeNext(CScene::MODE_TITLE), m_pVtxBuff(nullptr), m_col{}
{

}

//=====================================================
// デストラクタ
//=====================================================
CFade::~CFade()
{

}

//=====================================================
// 生成処理
//=====================================================
CFade *CFade::Create(void)
{
	if (s_pFade == nullptr)
	{
		s_pFade = new CFade;

		if (s_pFade != nullptr)
		{
			s_pFade->Init();
		}
	}

	return s_pFade;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CFade::Init(void)
{
	//情報の設定
	m_fade = STATE_NONE;
	m_col = { 0.0f,0.0f,0.0f,0.0f };

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	if (m_pVtxBuff == nullptr)
	{
		// 頂点バッファの生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			NULL)))
		{
			assert(("頂点バッファの生成に失敗", false));
		}
	}

	// 頂点情報のポインタ
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CFade::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{// 頂点バッファの破棄
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	delete this;
}

//=====================================================
// 更新処理
//=====================================================
void CFade::Update(void)
{
	if (m_fade != STATE_NONE)
	{
		if (m_fade == STATE_IN)
		{// フェードイン状態
			m_col.a += FADE_SPEED;
			
			if (m_col.a >= 1.0f)
			{// ポリゴンが完全に不透明になったら
				m_col.a = 1.0f;
				m_fade = STATE_OUT;

				// モード設定
				Manager::SetMode(m_modeNext);
			}
		}
		else if (m_fade == STATE_OUT)
		{// フェードアウト状態
			m_col.a -= FADE_SPEED;

			if (m_col.a <= 0.0f)
			{// ポリゴンが完全に不透明になったら
				m_col.a = 0.0f;
				m_fade = STATE_NONE;
			}
		}

		// 頂点情報のポインタ
		VERTEX_2D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点カラーの設定
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		// 頂点バッファをアンロック
		m_pVtxBuff->Unlock();
	}
}

//=====================================================
// 描画処理
//=====================================================
void CFade::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャ設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================================
// 設定処理
//=====================================================
void CFade::SetFade(CScene::E_MODE modeNext)
{
	if (m_fade == STATE_NONE)
	{
		m_fade = STATE_IN;
		m_modeNext = modeNext;
		m_col = { 0.0f, 0.0f, 0.0f, 0.0f };
	}
}

//=====================================================
// 情報取得処理
//=====================================================
CFade::E_STATE CFade::GetState(void)
{
	return m_fade;
}