//*****************************************************
//
// レンダラーの処理[renderer.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _RENDERER_H_	// 二重インクルード防止
#define _RENDERER_H_

//*****************************************************
// クラスの定義
//*****************************************************
class CRenderer
{
public:
	CRenderer();	// コンストラクタ
	~CRenderer();	// デストラクタ

	// メンバ関数
	static CRenderer *Create(HWND hWnd, BOOL bWindow);
	HRESULT Init(HWND hWnd, BOOL bWindow);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void DrawFPS(void);	//FPS表示処理
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// デバイスの取得

	// 静的メンバ関数
	static bool IsFog(void) { return s_bFog; }
	static void EnableFog(bool bFog) { s_bFog = bFog; }
	static CRenderer *GetInstance(void) { return s_pRenderer; }

private:
	// メンバ変数
	LPDIRECT3D9 m_pD3D;	// オブジェクトの生成
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// デバイス

	// 静的メンバ変数
	static bool s_bFog;	// フォグをかけるかどうか
	static CRenderer *s_pRenderer;	// 自身のポインタ
};

namespace Renderer
{
//*****************************************************
// ショートカット関数
//*****************************************************
LPDIRECT3DDEVICE9 GetDevice(void);	// デバイスの取得
}

#endif