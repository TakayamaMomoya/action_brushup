//*****************************************************
//
// ビルボードの処理[billboard.h]
// Author:��山桃也
//
//*****************************************************
#ifndef _BILLBOARD_H_	// 二重インクルード防止
#define _BILLBOARD_H_

//*****************************************************
// インクルード
//*****************************************************
#include "polygon3D.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CBillboard : public CPolygon3D
{
public:
	CBillboard(int nPriority = 5);	// コンストラクタ
	~CBillboard();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void SetVtx(void) override;	// 頂点設定

	// 静的メンバ関数
	static CBillboard *Create(D3DXVECTOR3 pos, float width, float height);

private:
};

#endif