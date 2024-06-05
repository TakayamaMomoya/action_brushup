//*****************************************************
//
// ブラーの処理[blur.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _BLUR_H_    // 二重インクルードの防止
#define _BLUR_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace Blur
{
const int NUM_RENDER = 2;   // ターゲットレンダリング用のインターフェースの数
}

//*****************************************************
// クラスの定義
//*****************************************************
class CBlur
{
public:
	CBlur();	// コンストラクタ
	~CBlur();	// デストラクタ

    void Init(void); // 初期化

private:
    // メンバ関数
    void CreatePolygon(void);

    // メンバ変数
    LPDIRECT3DTEXTURE9 m_apTextureMT[Blur::NUM_RENDER];    // レンダリングターゲット用テクスチャ
    LPDIRECT3DSURFACE9 m_apRenderMT[Blur::NUM_RENDER]; // ターゲットレンダリング用インターフェース
    LPDIRECT3DSURFACE9 m_pZBuffMT;  // ターゲットレンダリング用Zバッファ
    D3DVIEWPORT9 m_viewpotrMT;  // ターゲットレンダリング用ビューポート
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMT;   // フィードバック用ポリゴンの頂点バッファ
    float m_fAlpha; // 重ねるポリゴンの透明度
    float m_fDiffPolygon;   // ポリゴンの差分の大きさ
    D3DXCOLOR m_colPolygon; // ポリゴンの色
};

#endif
