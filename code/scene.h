//*****************************************************
//
// シーン処理[scene.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _SCENE_H_	// 二重インクルード防止
#define _SCENE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CPlayer;
class CMeshField;

//*****************************************************
// クラスの定義
//*****************************************************
class CScene
{
public:
	// 列挙型定義
	enum E_MODE
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RANKING,
		MODE_MAX
	};

	CScene();	// コンストラクタ
	~CScene();	// デストラクタ

	// メンバ関数
	virtual HRESULT Init(void);	// 初期化処理
	virtual void Uninit(void);	// 終了処理
	virtual void Update();	// 更新処理
	virtual void Draw();	// 描画

	// 変数取得・設定関数
	int GetTimer(void) { return m_nTimerTrans; }	// 状態遷移タイマー
	void SetTimer(int nTime) { m_nTimerTrans = nTime; }

	// 静的メンバ関数
	static CScene *Create(E_MODE mode);	// 生成処理

private:
	int m_nTimerTrans;	// 遷移タイマー
};

#endif