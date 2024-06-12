//*****************************************************
//
// メッシュシリンダーの処理[meshcylinder.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _MESHCYLINDER_H_	// 二重インクルード防止
#define _MESHCYLINDER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace MeshCylinder
{
const float  MESH_RADIUS = 100.0f;	// 半径
const int MESH_U = 16;	// 横の分割数
const int MESH_V = 1;	// 縦の分割数
const int SPLIT_TEX_U = 3;	// 横のテクスチャ分割数
const int SPLIT_TEX_V = 1;	// 縦のテクスチャ分割数
const float MESH_HEIGHT = 50.0f;	// メッシュの高さ
}

//*****************************************************
// クラス定義
//*****************************************************
class CMeshCylinder : public CObject
{
public:
	CMeshCylinder(int nPriority = 2);	// コンストラクタ
	~CMeshCylinder();	// デストラクタ

	// 構造体定義
	struct S_MeshCylinder
	{// 自身の情報
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 rot;	//向き
		D3DXMATRIX mtxWorld;	//ワールドマトリックス
		int nNumIdx;	//インデックス数
		int nNumVtx;	//頂点数
		float fRadius;	// 半径
		float fHeight;	// 高さ
		int nMeshU;	// 横の分割数
		int nMeshV;	// 縦の分割数
		int nTexU;	// テクスチャの横の分割数
		int nTexV;	// テクスチャの縦の分割数
		// コンストラクタ
		S_MeshCylinder() : pos{}, rot{}, mtxWorld{}, nNumIdx(0), nNumVtx(0),fRadius(0.0f), fHeight(0.0f), nMeshU(0), nMeshV(0), nTexU(0), nTexV(0) {}
	};

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void SetVtx(void);	// 頂点の設定

	// 変数取得・設定関数
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }	// 頂点バッファ
	void SetPosition(D3DXVECTOR3 pos) { m_meshCylinder.pos = pos; }	// 位置
	D3DXVECTOR3 GetPosition(void) { return m_meshCylinder.pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_meshCylinder.rot = rot; }	// 向き
	D3DXVECTOR3 GetRotation(void) { return m_meshCylinder.rot; }
	int GetNumVtx(void) { return m_meshCylinder.nNumVtx; }	// 頂点数
	void SetRadius(float fRadius) { m_meshCylinder.fRadius = fRadius; }	// 半径
	void SetHeight(float fHeight) { m_meshCylinder.fHeight = fHeight; }	// 高さ
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }	// テクスチャ番号
	void SetNumMeshU(int nNumMesh) { m_meshCylinder.nMeshU = nNumMesh; }	// メッシュの横の分割数
	void SetNumMeshV(int nNumMesh) { m_meshCylinder.nMeshV = nNumMesh; }	// メッシュの縦の分割数
	S_MeshCylinder *GetMeshCylinder(void) { return &m_meshCylinder; }	// 自身の情報の構造体
	void SetCol(D3DXCOLOR col);	// 色
	D3DXCOLOR GetCol(void) { return m_col; }
	void SetMtx(D3DXMATRIX mtx) { m_meshCylinder.mtxWorld = mtx; }	// マトリックス

	// 静的メンバ関数
	static CMeshCylinder *Create	// 生成処理
	(
		int nMeshU = MeshCylinder::MESH_U,
		int nMeshV = MeshCylinder::MESH_V,
		int nTexU = MeshCylinder::SPLIT_TEX_U,
		int nTexV = MeshCylinder::SPLIT_TEX_V
	);

private:
	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//インデックスバッファへのポインタ
	S_MeshCylinder m_meshCylinder;	//構造体の情報
	D3DXCOLOR m_col;	// 色
	int m_nIdxTexture;	// テクスチャ番号
};

#endif