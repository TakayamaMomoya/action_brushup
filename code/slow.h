//*****************************************************
//
// スローの処理[slow.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _SLOW_H_	// 二重インクルード防止
#define _SLOW_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CSlow : public CObject
{
public:
	CSlow();	// コンストラクタ
	~CSlow();	// デストラクタ

	// メンバ変数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	// 変数取得・設定関数
	float GetScale(void) { return m_fTimeScale; }	// タイムスケール
	void SetScale(float fScale);
	void SetSlowTime(float fTime, float fScale);	// 一定時間スローにする処理

	// 静的メンバ変数
	static CSlow *Create(void);
	static CSlow *GetInstance(void) { return s_pSlow; }

private:
	// メンバ変数
	float m_fTimeScale;	// タイムスケール
	float m_fTimeSlow;	// スローにする時間

	// 静的メンバ変数
	static CSlow *s_pSlow;	// 自身のポインタ
};

namespace Slow
{
//*****************************************************
// ショートカット関数
//*****************************************************
float GetTimeScale(void);	// タイムスケールの取得
}

#endif