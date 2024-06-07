//*****************************************************
//
// フェード処理[fade.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _FADE_H_	// 二重インクルード防止
#define _FADE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object2D.h"
#include "scene.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CFade
{
public:
	// 列挙型定義
	enum E_STATE
	{// 状態
		STATE_NONE = 0,	// 何もしていない状態
		STATE_IN,	// フェードイン状態
		STATE_OUT,	// フェードアウト状態
		STATE_MAX
	};

	CFade();	// コンストラクタ
	~CFade();	// デストラクタ
	
	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	// 変数取得・設定関数
	void SetFade(CScene::MODE modeNext);	// フェードを開始する処理
	E_STATE GetState(void);	// 状態

	// 静的メンバ関数
	static CFade *Create(void);	// 生成処理
	static CFade *GetInstance(void) { return m_pFade; }	// インスタンスの取得

private:
	// メンバ変数
	E_STATE m_fade;	// フェードの状態
	CScene::MODE m_modeNext;	// フェード後の画面
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファ
	D3DXCOLOR m_col;	// ポリゴンの色

	// 静的メンバ変数
	static CFade *m_pFade;	// 自身のポインタ
};
#endif
