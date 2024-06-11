//*****************************************************
//
// 入力マネージャー[inputManager.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _INPUTMANAGER_H_	// 二重インクルード防止
#define _INPUTMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CInputManager
{
public:
	// 列挙型定義
	enum E_BUTTON
	{
		BUTTON_ENTER = 0,	// エンターボタン
		BUTTON_BACK,	// 戻るボタン
		BUTTON_JUMP,	// ジャンプ
		BUTTON_ATTACK,	// 攻撃
		BUTTON_PARRY,	// パリィ
		BUTTON_MOVE_RIGHT,	// 右移動
		BUTTON_MOVE_LEFT,	// 左移動
		BUTTON_DASH,	// ダッシュ
		BUTTON_PAUSE,	// ポーズ
		BUTTON_AXIS_UP,	// 上方向キー
		BUTTON_AXIS_DOWN,	// 下方向キー
		BUTTON_AXIS_RIGHT,	// 右方向キー
		BUTTON_AXIS_LEFT,	// 左方向キー
		BUTTON_MAX
	};

	CInputManager();	// コンストラクタ
	~CInputManager();	// デストラクタ

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理

	// 変数取得・設定関数
	bool GetTrigger(E_BUTTON button) { return m_info.abTrigger[button]; }	// ボタントリガー情報
	bool GetPress(E_BUTTON button) { return m_info.abPress[button]; }	// ボタンプレス情報

	// 静的メンバ関数
	static CInputManager *Create(HINSTANCE hInstance, HWND hWnd);
	static CInputManager *GetInstance(void) { return m_pInputManager; }

private:
	// 構造体定義
	struct S_Info
	{// 自身の情報
		bool abTrigger[BUTTON_MAX];	// トリガー情報
		bool abPress[BUTTON_MAX];	// プレス情報

		// コンストラクタ
		S_Info() : abTrigger{}, abPress{} {}
	};

	// メンバ変数
	S_Info m_info;	// 情報

	// 静的メンバ変数
	static CInputManager *m_pInputManager;	// 自身のポインタ
};

#endif
