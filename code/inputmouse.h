//*****************************************************
//
// マウス入力処理[inputmouse.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _INPUTMOUSE_H_	// 二重インクルード防止
#define _INPUTMOUSE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "input.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace Mouse
{
const int NUM_BUTTON_MAX = 8;	//マウスボタンの数
}

//*****************************************************
// クラスの定義
//*****************************************************
class CInputMouse : public CInput
{
public:
	// 列挙型定義
	typedef enum
	{//マウスボタン
		BUTTON_LMB = 0,					//左クリック
		BUTTON_RMB,						//右クリック
		BUTTON_WHEEL,						//ウィールクリック
		BUTTON_SIDE01,						//サイドボタン１
		BUTTON_SIDE02,						//サイドボタン２
		BUTTON_MAX
	}BUTTON;

	CInputMouse();	// コンストラクタ
	~CInputMouse();	// デストラクタ

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理

	// 変数取得・設定関数
	bool GetPress(int nKey);	// ボタンプレス情報
	bool GetTrigger(int nKey);	// ボタントリガー情報
	bool GetRelease(int nKey);	// ボタンリリース情報
	int GetRepeat(int nKey);	// ボタンリピート情報
	LONG GetMoveIX(void);	// X軸の移動量
	LONG GetMoveIY(void);	// Y軸の移動量
	LONG GetMoveIZ(void);	// ホイールの回転量

	// 静的メンバ関数
	static CInputMouse *Create(HINSTANCE hInstance, HWND hWnd);	// 生成処理
	static CInputMouse *GetInstance(void) { return m_pMouse; }	// インスタンスの取得

private:
	// メンバ変数
	DIMOUSESTATE2 m_mouseState;	//マウスの情報構造体
	BYTE m_aKeyState[Mouse::NUM_BUTTON_MAX];	// プレス情報
	BYTE m_aKeyStateTrigger[Mouse::NUM_BUTTON_MAX];	// トリガー情報
	BYTE m_aKeyStateRelease[Mouse::NUM_BUTTON_MAX];	// リリース情報
	BYTE m_aKeyStateRepeat[Mouse::NUM_BUTTON_MAX];	// リピート情報
	int m_aCntRepeat[Mouse::NUM_BUTTON_MAX];	// リピートカウンター

	// 静的メンバ変数
	static CInputMouse *m_pMouse;	// 自身のポインタ
};

#endif