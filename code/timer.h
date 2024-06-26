//*****************************************************
//
// タイマーの処理[timer.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _TIMER_H_	// 二重インクルード防止
#define _TIMER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CNumber;

//*****************************************************
// クラスの定義
//*****************************************************
class CTimer : public CObject
{
public:
	CTimer();	// コンストラクタ
	~CTimer();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void AddTimer(int nValue);	// タイマーの加算

	// 変数取得・設定関数
	int GetSecond(void) { return m_nSecond; }	// 時間取得
	void EnableStop(bool bStop) { m_bStop = bStop; }	// 停止状態

	// 静的メンバ関数
	static CTimer *Create(void);	// 生成処理
	static CTimer *GetInstance(void) { return m_pTimer; }	// インスタンスの取得

private:
	// メンバ変数
	CNumber *m_pObjMinute;	// 分表示のポインタ
	CNumber *m_pObjSecond;	// 秒表示のポインタ
	int m_nSecond;	// 現在の時間(秒)
	int m_nCntSecond;	// 一秒計測用カウンター
	int m_nIdxTexture;	// テクスチャ番号
	bool m_bStop;	// 止めるかどうか

	// 静的メンバ変数
	static CTimer *m_pTimer;	// 自身のポインタ
};

#endif
