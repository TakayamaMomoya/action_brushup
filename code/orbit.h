//******************************************
//
// 軌跡の処理(orbit.h)
// Author:髙山桃也
//
//******************************************
#ifndef _ORBIT_H_	// 二重インクルード防止
#define _ORBIT_H_

//******************************************
// インクルード
//******************************************
#include "object.h"

//******************************************
// 定数定義
//******************************************
namespace Orbit
{
const int MAX_EDGE = 500;	// 辺の最大数
const int NUM_OFFSET = 2;	// オフセットの数
}

//******************************************
// クラス定義
//******************************************
class COrbit : public CObject
{
public:
	COrbit(int nPriority = 6);	// コンストラクタ
	~COrbit();	// デストラクタ

	// メンバ関数
	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);  // 描画
	void SetPositionOffset(D3DXMATRIX mtxWorld, int nIdxOrbit);	// オフセットの位置を設定
	
	// 変数取得・設定関数
	bool IsEnd(void) { return m_bEnd; }	// 切り離すフラグ
	void SetEnd(bool bEnd) { m_bEnd = bEnd; }

	// 静的メンバ関数
	static COrbit *Create(D3DXMATRIX mtxWorld, D3DXVECTOR3 posOffset1, D3DXVECTOR3 posOffset2, D3DXCOLOR col, int nNumEdge);	// 生成処理

private:
	// メンバ関数
	void UpdatePolygon(void);	// ポリゴンの更新

	// メンバ変数
	int m_nIdxTexture;	// テクスチャ番号
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3 m_aPosOffset[Orbit::NUM_OFFSET];	// オフセット位置
	D3DXVECTOR3 m_aPosPoint[Orbit::MAX_EDGE][Orbit::NUM_OFFSET];	// 頂点座標保存用
	D3DXCOLOR m_col;	// 色
	D3DXCOLOR m_aColPoint[Orbit::MAX_EDGE][Orbit::NUM_OFFSET];	// 頂点カラー保存用
	D3DXMATRIX m_aMtxOffset[Orbit::NUM_OFFSET];	// オフセットのマトリックス
	int m_nNumEdge;	//辺の数
	int m_nID;	// 番号
	bool m_bEnd;	// 終了してるかどうか
};

#endif