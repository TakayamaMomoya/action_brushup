//*****************************************************
//
// ジョイパッド入力処理[inputjoypad.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _INPUTJOYPAD_H_	// 二重インクルード防止
#define _INPUTJOYPAD_H_

//*****************************************************
// インクルード
//*****************************************************
#include "input.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace Joypad
{
const int MAX_PLAYER = 4;	// プレイヤーの最大数
}

//*****************************************************
// クラスの定義
//*****************************************************
class CInputJoypad
{
public:
	// 列挙型定義
	enum E_PADBUTTONS
	{//ゲームパッドボタン
		PADBUTTONS_UP = 0,	// 上矢印
		PADBUTTONS_DOWN,	// 下矢印
		PADBUTTONS_LEFT,	// 左矢印
		PADBUTTONS_RIGHT,	// 右矢印
		PADBUTTONS_START,	// スタートボタン
		PADBUTTONS_BACK,	// バックボタン
		PADBUTTONS_LSTICK,	// 左スティック押し込み
		PADBUTTONS_RSTICK,	// 右スティック押し込み
		PADBUTTONS_LB,	// LBボタン
		PADBUTTONS_RB,	// RBボタン
		PADBUTTONS_UNKNOWN,	// 不明ボタン
		PADBUTTONS_UNKNOWN2,	// 不明ボタン
		PADBUTTONS_A,	// Aボタン
		PADBUTTONS_B,	// Bボタン
		PADBUTTONS_X,	// Xボタン
		PADBUTTONS_Y,	// Yボタン
		PADBUTTONS_MAX
	};
	enum E_STATE_PADVIB
	{//バイブレーションの状態
		PADVIB_NONE = 0,	//使用していない状態
		PADVIB_USE,	//使用している状態
		PADVIB_MAX
	};
	enum E_DIRECTION
	{// スティックのトリガー
		DIRECTION_UP = 0,	// 上
		DIRECTION_DOWN,	// 下
		DIRECTION_RIGHT,	// 右
		DIRECTION_LEFT,	// 左
		DIRECTION_MAX
	};

	CInputJoypad();	// コンストラクタ
	~CInputJoypad();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理

	// 変数取得・設定関数
	bool GetPress(E_PADBUTTONS nKey, int nPlayer);	// ボタンプレス
	bool GetTrigger(E_PADBUTTONS nKey, int nPlayer);	// ボタントリガー
	bool GetRelease(E_PADBUTTONS nKey, int nPlayer);	// ボタンリリース
	int GetRepeat(E_PADBUTTONS nKey, int nPlayer);	// ボタンリピート
	float GetJoyStickLX(int nPlayer);	// 左ジョイスティック傾き
	float GetJoyStickLY(int nPlayer);
	float GetJoyStickRX(int nPlayer);	// 右ジョイスティック傾き
	float GetJoyStickRY(int nPlayer);
	bool GetLStickTrigger(E_DIRECTION direction,int nPlayer);	// 左ジョイスティック弾き
	D3DXVECTOR3 GetVecStickL(void);	// 左ジョイスティック傾き
	void Vibration(int nPlayer, E_STATE_PADVIB state, short sVib, int nTime);	// バイブレーション設定

	// 静的メンバ関数
	static CInputJoypad *Create(void);	// 生成処理
	static CInputJoypad *GetInstance(void) { return s_pJoyPad; }	// インスタンスの取得

private:
	// メンバ関数
	void CheckStickTrigger(XINPUT_STATE state,int nPlayer);	// スティックのトリガー判定確認

	// メンバ変数
	XINPUT_STATE m_aState[Joypad::MAX_PLAYER];				//ゲームパッドのプレス情報
	XINPUT_STATE m_aStateTrigger[Joypad::MAX_PLAYER];		//ゲームパッドのトリガー情報
	XINPUT_STATE m_aStateRelease[Joypad::MAX_PLAYER];		//ゲームパッドのリリース情報
	XINPUT_STATE m_aStateRepeat[Joypad::MAX_PLAYER];			//ゲームパッドのリピート情報
	XINPUT_VIBRATION m_aVibration[Joypad::MAX_PLAYER];		//ゲームパッドの振動情報
	E_STATE_PADVIB m_aVibState[Joypad::MAX_PLAYER];					//振動の状態
	int m_nVibTimer;		// バイブレーションのタイマー
	int m_aCntRepeat[Joypad::MAX_PLAYER][PADBUTTONS_MAX];	// リピートカウンター
	bool m_abTrigggerLStick[Joypad::MAX_PLAYER][DIRECTION_MAX];	// スティックのトリガー判定

	// 静的メンバ変数
	static CInputJoypad *s_pJoyPad;	// 自身のポインタ
};

#endif
