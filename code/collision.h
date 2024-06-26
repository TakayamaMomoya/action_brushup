//*****************************************************
//
// 当たり判定処理[collision.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _COLLISION_H_	// 二重インクルード防止
#define _COLLISION_H_

//*****************************************************
// インクルード
//****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//****************************************************
class CObject2D;

//*****************************************************
// クラス定義
//*****************************************************
class CCollision
{
public:
	// 列挙型定義
	enum E_TAG
	{// 識別タグ
		TAG_NONE = 0,	// 何でもない
		TAG_PLAYER,	// プレイヤー
		TAG_ENEMY,	// 敵
		TAG_PLAYERBULLET,	// プレイヤーの弾
		TAG_ENEMYBULLET,	// 敵の弾
		TAG_BLOCK,	// ブロック
		TAG_MAX
	};

	enum E_TYPE
	{// 種類
		TYPE_NONE = 0, // 何でもない
		TYPE_SPHERE,	// 球の当たり判定
		TYPE_CUBE,	// 立方体の当たり判定
		TYPE_MAX
	};

	CCollision();	// コンストラクタ
	~CCollision();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void ReleaseOther(void) { m_pObjectOther = nullptr; }	// 当たったものの解放
	bool TriggerCube(E_TAG tag);	// キューブのトリガー判定
	bool ChckObstclBtwn(CObject *pObject, D3DXVECTOR3 vecDiff);	// 間に障害物があるかのチェック

	// 変数取得・設定関数
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// 位置
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }	// 前回の位置
	void SetPositionOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	CCollision **GetCollision(void) { return &s_apCollision[0]; }	// 当たり判定の配列
	E_TAG GetTag(void) { return m_tag; }	// タグ
	void SetTag(E_TAG tag) { m_tag = tag; }
	E_TYPE GetType(void) { return m_type; }	// 種類
	void SetType(E_TYPE type) { m_type = type; }
	virtual float GetRadius(void) { return 0.0f; }	// 半径
	void SetOwner(CObject *pObj) { m_pObjectOwner = pObj; }	// 持ち主
	CObject *GetOwner(void) { return m_pObjectOwner; }
	void SetOther(CObject *pObj) { m_pObjectOther = pObj; }	// 当たったもの
	CObject *GetOther(void) { return m_pObjectOther; }
	virtual D3DXVECTOR3 GetVtxMax(void) { return D3DXVECTOR3(0.0f,0.0f,0.0f); }	// 最大頂点
	virtual D3DXVECTOR3 GetVtxMin(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }	// 最小頂点

	// 静的メンバ関数
	static bool IsCross(D3DXVECTOR3 posTarget, D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest, float *fRate, D3DXVECTOR3 move = { 0.0f,0.0f,0.0f });	// 外積の判定
	static bool IsCrossTrigger(D3DXVECTOR3 posTarget, D3DXVECTOR3 posTargetOld, D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest);	// 外積のトリガー判定
	static int GetNumAll(void) { return s_nNumAll; }	// 総数取得
	static void DeleteAll(void);	// 全削除
	static CCollision *Create(E_TAG tag, E_TYPE type, CObject *obj);	// 生成処理

private:
	// メンバ変数
	D3DXVECTOR3 m_pos;	// 場所
	D3DXVECTOR3 m_posOld;	// 前回の場所
	E_TAG m_tag;	// 識別用タグ
	E_TYPE m_type;	// 種類
	int m_nID;	// 番号
	CObject *m_pObjectOwner;	// 持ち主
	CObject *m_pObjectOther;	// 当たったもの

	// 静的メンバ変数
	static CCollision *s_apCollision[NUM_OBJECT];	// 当たり判定の配列
	static int s_nNumAll;	// 総数
};

class CCollisionSphere : public CCollision
{// 球の当たり判定
public:
	CCollisionSphere();	// コンストラクタ
	~CCollisionSphere();	// デストラクタ
	
	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	bool SphereCollision(E_TAG tag);	// 球の判定	

	// 変数取得・設定関数
	float GetRadius(void) { return m_fRadius; }	// 半径
	void SetRadius(float fRadius) { m_fRadius = fRadius; }
	bool IsTriggerExit(E_TAG tag);	// トリガーで出た判定
	bool IsTriggerEnter(E_TAG tag);	// トリガーで入った判定

	// 静的メンバ関数
	static CCollisionSphere *Create(E_TAG tag, E_TYPE type, CObject *obj);	// 生成処理

private:
	// メンバ変数
	float m_fRadius;	// 半径
};

class CCollisionCube : public CCollision
{// 立方体の当たり判定
public:
	CCollisionCube();	// コンストラクタ
	~CCollisionCube();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	bool CollideCube(E_TAG tag, D3DXVECTOR3 *pMove);	// キューブの当たり判定

	// 変数取得・設定関数
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }	// 最大頂点
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }	// 最小頂点
	void SetVtx(D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);	// 最大・最小頂点
	D3DXVECTOR3 CollideVector(CObject *pObj);	// ベクトルとの判定

	// 静的メンバ関数
	static CCollisionCube *Create(E_TAG tag, CObject *obj);	// 生成処理

private:
	// メンバ変数
	D3DXVECTOR3 m_vtxMax;	// 最大頂点
	D3DXVECTOR3 m_vtxMin;	// 最小頂点
};


#endif