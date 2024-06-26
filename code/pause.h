//*****************************************************
//
// ポーズの処理[pause.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _PAUSE_H_	// 二重インクルード防止
#define _PAUSE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CObject2D;

//*****************************************************
// クラス定義
//*****************************************************
class CPause : CObject
{
public:
	CPause();	// コンストラクタ
	~CPause();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

	// 静的メンバ関数
	static CPause *Create(void);	// 生成処理
	static CPause *GetInstance(void) { return m_pPause; }	// インスタンスの取得

private:
	// 列挙型定義
	enum E_MENU
	{// 項目の種類
		MENU_RESUME = 0,	// 再開
		MENU_RESTART,	// リトライ
		MENU_CHECKPOINT,	// チェックポイントから再開
		MENU_QUIT,	// 終了
		MENU_MAX
	};
	enum E_STATE
	{
		STATE_NONE = 0,	// 何でもない状態
		STATE_IN,	// フェードイン状態
		STATE_OUT,	// フェードアウト状態
		STATE_MAX
	};

	// メンバ関数
	void ManageState(void);	// 状態管理
	void ManageBg(void);	// 背景の管理
	void Input(void);	// 入力処理
	void Fade(E_MENU menu);	// フェードする処理

	// メンバ変数
	E_MENU m_menu;	// 選択項目
	CObject2D *m_apMenu[MENU_MAX];	// メニュー項目の２Dオブジェクト
	CObject2D *m_pBg;	// 背景２Dオブジェクト
	D3DXVECTOR3 m_aPosDest[MENU_MAX];	// 目標の位置
	E_STATE m_state;	// 状態

	// 静的メンバ関数
	static CPause *m_pPause;	// 自身のポインタ
};

#endif