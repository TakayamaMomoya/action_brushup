//*****************************************************
//
// キーボード入力処理[inputkeyboard.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _INPUTKEYBOARD_H_	// 二重インクルード防止
#define _INPUTKEYBOARD_H_

//*****************************************************
// インクルード
//*****************************************************
#include "input.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int NUM_KEY_MAX = 256;	// キーの最大数
}

//*****************************************************
// クラスの定義
//*****************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();	// コンストラクタ
	~CInputKeyboard();	// デストラクタ

	// メンバ変数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理

	// 変数取得・設定関数
	bool GetPress(int nKey);	// ボタンプレス情報
	bool GetTrigger(int nKey);	// ボタントリガー情報
	bool GetRelease(int nKey);	// ボタンリリース情報
	int GetRepeat(int nKey);	// ボタンリピート情報

	// 静的メンバ関数
	static CInputKeyboard *Create(HINSTANCE hInstance, HWND hWnd);	// 生成処理
	static CInputKeyboard *GetInstance(void) { return m_pKeyboard; }	// インスタンスの取得

private:
	// メンバ変数
	BYTE m_aKeyState[NUM_KEY_MAX];					// プレス情報
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			// トリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			// リリース情報
	BYTE m_aKeyStateRepeat[NUM_KEY_MAX];			// リピート情報
	int m_aCntRepeat[NUM_KEY_MAX];	// リピートカウンター

	// 静的メンバ変数
	static CInputKeyboard *m_pKeyboard;	// 自身のポインタ
};

#endif