//*****************************************************
//
// UIマネージャー[UIManager.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _UIMANAGER_H_	// 二重インクルード防止
#define _UIMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CLife;
class CScore;
class CTimer;

//*****************************************************
// クラスの定義
//*****************************************************
class CUIManager : public CObject
{
public:
	CUIManager();	// コンストラクタ
	~CUIManager();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	// 変数取得・設定関数
	bool IsDisp(void) { return m_bDisp; }	// 表示フラグ
	void EnableDisp(bool bDisp) { m_bDisp = bDisp; }

	// 静的メンバ関数
	static CUIManager *Create(void);	// 生成処理
	static CUIManager *GetInstance(void) { return m_pUIManager; }	// インスタンスの取得

private:
	// メンバ変数
	bool m_bDisp;	// UIを表示するかどうか
	CLife *m_pLife;	// ライフ
	CScore *m_pScore;	// スコア
	CTimer *m_pTimer;	// タイマー

	// 静的メンバ変数
	static CUIManager *m_pUIManager;	// 自身のポインタ
};

#endif
