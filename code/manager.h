//*****************************************************
//
// マネージャー処理[manager.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _MANAGER_H_	// 二重インクルード防止
#define _MANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "scene.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CCamera;
class CLight;

//*****************************************************
// クラスの定義
//*****************************************************
class CManager
{
public:
	CManager();	// コンストラクタ
	~CManager();	// デストラクタ

	// メンバ変数
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
	void Uninit(void);
	void Update();
	void Draw();

	// 静的メンバ関数
	static CCamera *GetCamera(void) { return m_pCamera; }	// カメラ取得
	static CLight *GetLight(void) { return m_pLight; }	// ライト取得
	static void SetMode(CScene::MODE mode);	// モードの設定
	static CScene::MODE GetMode(void) { return m_mode; }	// モードの取得
	static void SetScore(int nScore) { m_nScore = nScore; }	// スコアの設定
	static int GetScore(void) { return m_nScore; }	// スコアの取得
	static void SetDeltaTime(float fValue) { m_fDeltaTime = fValue; }	// デルタタイムの設定
	static float GetDeltaTime(void) { return m_fDeltaTime; }	// デルタタイムの取得

private:
	// 静的メンバ変数
	static CCamera *m_pCamera;	// カメラのポインタ
	static CLight *m_pLight;	// ライトのポインタ
	static CScene *m_pScene;	// 現在のシーン
	static CScene::MODE m_mode;	// 現在のモード
	static int m_nScore;	// スコア
	static float m_fDeltaTime;	// 前回のフレームからかかった時間
};

#endif