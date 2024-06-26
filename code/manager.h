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

	// 変数取得・設定関数
	CCamera *GetCamera(void) { return m_pCamera; }	// カメラ取得
	CLight *GetLight(void) { return m_pLight; }	// ライト取得
	void SetMode(CScene::E_MODE mode);	// モードの設定
	CScene::E_MODE GetMode(void) { return m_mode; }	// モードの取得
	void SetScore(int nScore) { m_nScore = nScore; }	// スコアの設定
	int GetScore(void) { return m_nScore; }	// スコアの取得
	void SetDeltaTime(float fValue) { m_fDeltaTime = fValue; }	// デルタタイムの設定
	float GetDeltaTime(void) { return m_fDeltaTime; }	// デルタタイムの取得

	// 静的メンバ関数
	static CManager *Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// 生成処理
	static CManager *GetInstace(void) { return s_pManager; };	// インスタンスの取得
private:
	// メンバ変数
	CCamera *m_pCamera;	// カメラのポインタ
	CLight *m_pLight;	// ライトのポインタ
	CScene *m_pScene;	// 現在のシーン
	CScene::E_MODE m_mode;	// 現在のモード
	int m_nScore;	// スコア
	float m_fDeltaTime;	// 前回のフレームからかかった時間

	// 静的メンバ変数
	static CManager *s_pManager;	// 自身のポインタ
};

namespace Manager
{
//*****************************************************
// ショートカット関数
//*****************************************************
CCamera *GetCamera(void);	// カメラ取得
CLight *GetLight(void);	// ライト取得
void SetMode(CScene::E_MODE mode);	// モードの設定
CScene::E_MODE GetMode(void);	// モードの取得
void SetScore(int nScore);	// スコアの設定
int GetScore(void);	// スコアの取得
float GetDeltaTime(void);	// デルタタイムの取得
}

#endif