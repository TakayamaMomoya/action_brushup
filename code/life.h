//*****************************************************
//
// ライフ管理の処理[life.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _LIFE_H_	// 二重インクルード防止
#define _LIFE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CUI;

//*****************************************************
// クラスの定義
//*****************************************************
class CLife : public CObject
{
public:
	CLife(int nPriority = 6);	// コンストラクタ
	~CLife();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void) {};	// 描画

	// 静的メンバ関数
	static CLife *Create(void);	// 生成処理

private:
	enum E_PULSESTATE
	{// 波形の状態
		PULSESTATE_IN = 0,	// フェードイン状態
		PULSESTATE_OUT,	// フェードアウト状態
		PULSESTATE_MAX,
	};

	// メンバ関数
	void UpdatePulse(void);	// 波形の更新
	void FadePulse(void);	// 波形のフェード

	// メンバ変数
	CUI *m_pFrame;	// フレームのポインタ
	CUI *m_pPulse;	// 波形のポインタ
	E_PULSESTATE m_pulseState;	// 波形の状態
	int m_nCntPulse;	// 波形のカウンター
};

#endif
