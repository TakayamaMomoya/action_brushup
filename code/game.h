//*****************************************************
//
// ゲーム処理[game.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _GAME_H_	// 二重インクルード防止
#define _GAME_H_

//*****************************************************
// インクルード
//*****************************************************
#include "scene.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CGame : public CScene
{
public:
	// 列挙型定義
	enum E_STATE
	{// 状態
		STATE_NONE,	// 何もしていない状態
		STATE_NORMAL,	// 通常状態
		STATE_BOSS,	// ボス戦状態
		STATE_RESULT,	// リザルト状態
		STATE_END,	// 終了状態
		STATE_MAX
	};

	CGame();	// コンストラクタ
	~CGame();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update();	// 更新処理
	void Draw();	// 描画

	// 変数取得・設定関数
	void EnableStop(bool bStop) { m_bStop = bStop; }	// 停止状態
	int GetProgress(void) { return m_nProgress; }	// 進行度

	// 静的メンバ関数
	static void SetState(E_STATE state) { m_state = state; }	// 状態
	static E_STATE GetState(void) { return m_state; }
	static void SetProgress(int nProgress) { m_nProgress = nProgress; }	// 進行度
	static CGame *GetInstance(void) { return m_pGame; }	// インスタンスの取得

private:
	// メンバ関数
	void LoadCheckPoint(void);	// チェックポイント読込
	void CreateTutorial(void);	// チュートリアル生成
	void ManageState(void);	// 状態管理
	void Debug(void);	// デバッグ処理

	// メンバ関数
	D3DXVECTOR3 *m_pPosCheckPoint;	// チェックポイント座標のポインタ
	int m_nNumCheckPoint;	// チェックポイントの数
	int m_nCntState;	// 状態遷移カウンター
	bool m_bStop;	// 停止状態

	// 静的メンバ関数
	static E_STATE m_state;	// 状態
	static int m_nProgress;	// 進行度
	static CGame *m_pGame;	// 自身のポインタ
};

#endif