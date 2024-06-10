//*****************************************************
//
// カメラの処理[camera.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _CAMERA_H_	// 二重インクルード防止
#define _CAMERA_H_

//****************************************************
// インクルード
//****************************************************
#include "main.h"

//****************************************************
// マクロ定義
//****************************************************
#define MIN_DRAW		(10.0f)					// 描画を開始する距離
#define MAX_DRAW		(700000.0f)				// 描画を終了する距離

//****************************************************
// 前方宣言
//****************************************************
class CCameraState;

//****************************************************
// クラスの定義
//****************************************************
class CCamera
{
public:
	// 構造体宣言
	struct S_InfoCamera
	{// カメラの情報
		D3DXVECTOR3 posV;	// 視点
		D3DXVECTOR3 posVOld;	// 視点の前回の位置
		D3DXVECTOR3 posR;	// 注視点
		D3DXVECTOR3 posVDest;	// 目的の視点
		D3DXVECTOR3 posRDest;	// 目的の注視点
		D3DXVECTOR3 vecU;	// 上方向ベクトル
		D3DXVECTOR3 rot;	// 向き
		float fViewAngle;	// 視野角
		float fLength;	// 視点から注視点までの距離
		D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
		D3DXMATRIX mtxView;	// ビューマトリックス
		int nTimerQuake;	// 振動のタイマー
		float fQuakeSize;

		// コンストラクタ
		S_InfoCamera() : posV{}, posVOld{}, posR{}, posVDest{}, posRDest{}, vecU{}, rot{}, fViewAngle(0.0f),
			fLength(0.0f), mtxProjection(), mtxView(), nTimerQuake(0), fQuakeSize(0.0f) {};
	};

	CCamera();	// コンストラクタ
	~CCamera();	// デストラクタ

	// メンバ変数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void SetCamera(void);	// カメラのセット
	void SetPosV(void);	// 視点位置の設定
	void SetPosR(void);	// 注視点位置の設定
	void SetQuake(float fQuakeSize, int nTime);	// 振動設定
	void Quake(void);	// 振動中の処理

	// 変数取得・設定関数
	void SetDist(float fDist) { m_camera.fLength = fDist; }	// カメラ距離
	float GetDist(void) { return m_camera.fLength; }
	S_InfoCamera *GetInfo(void);	// 情報構造体
	void ChangeState(CCameraState *pBehavior);	// ステイト変更

private:
	// メンバ関数
	void Debug(void);	// デバッグ処理

	// メンバ関数
	S_InfoCamera m_camera;	// 構造体の情報
	CCameraState *m_pState;	// ステイト
};

#endif