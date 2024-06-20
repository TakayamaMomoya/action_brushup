//*****************************************************
//
// デバッグ表示処理 [debugproc.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _DEBUGPROC_H_	// 二重インクルード防止
#define _DEBUGPROC_H_

//*****************************************************
// マクロ定義定義
//*****************************************************
#define MAX_DEBUGSTRING (2048)	// デバッグの最大文字数

//*****************************************************
// クラスの定義
//*****************************************************
class CDebugProc
{
public:
	CDebugProc();	// コンストラクタ
	~CDebugProc();	// デストラクタ

	// メンバ関数
	void Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void Print(const char *fmt, ...);	// 文字の代入

	// 静的メンバ関数
	static CDebugProc *Create(void);
	static CDebugProc *GetInstance(void) { return s_pDebugProc; }

private:
	// メンバ変数
	char m_aStr[MAX_DEBUGSTRING];	// デバッグ表示用の文字列
	bool m_bDisp;		// デバッグ表示のON/OFF

	// 静的メンバ変数
	static LPD3DXFONT s_pFont;	// フォントへのポインタ
	static CDebugProc *s_pDebugProc;	// 自身のポインタ
};

#endif