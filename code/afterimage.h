//*****************************************************
//
// 残像の処理[afterimage.cpp]
// Author:髙山桃也
//
//*****************************************************
#ifndef _AFTERIMAGE_H_	// 二重インクルード防止
#define _AFTERIMAGE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "ObjectX.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CCollisionCube;

//*****************************************************
// クラスの定義
//*****************************************************
class CAfterImage : public CObjectX
{
public:
	CAfterImage(int nPriority = 6);	// コンストラクタ
	~CAfterImage();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

	// 静的メンバ関数
	static CAfterImage *Create(D3DXMATRIX mtx, int nIdxModel, D3DXCOLOR col, int m_nLife);	// 生成処理

private:
	// メンバ変数
	int m_nLife;	// 体力
	float m_fDecAlpha;	// 透明度減少量

	// 静的メンバ変数
	static int s_nNumAll;	// 総数
};

#endif
