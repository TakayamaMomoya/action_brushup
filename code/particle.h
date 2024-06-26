//*****************************************************
//
// パーティクル処理[particle.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _PARTICLE_H_	// 二重インクルード防止
#define _PARTICLE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// クラス定義
//*****************************************************
class CParticle : public CObject
{
public:
	// 列挙型定義
	enum E_TYPE
	{// 種類
		TYPE_NONE = 0,	// 何でもない
		TYPE_SPARK,	// 火花
		TYPE_FIRE,	// 爆発前
		TYPE_EXPLOSION,	// 爆発
		TYPE_MAX
	};

	CParticle(int nPriority = 3);	// コンストラクタ
	~CParticle();	// デストラクタ

	// メンバ関数
	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void) {};  // 描画
	void SetPosition(D3DXVECTOR3 pos);	// 位置
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; };	// 向き
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

	// 静的メンバ関数
	static CParticle *Create(D3DXVECTOR3 pos, E_TYPE type, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f }, D3DXVECTOR3 *pPosOwner = nullptr, int nPriorityEffect = 5);	// 生成処理
	static void Load(void);	// 読込処理
	static void Unload(void);	// 破棄処理

private:
	struct S_PARTICLE_INFO
	{// パーティクル情報
		char acTexPath[256];
		int nLife;	// 寿命
		int nLifeEffect;	// エフェクトの寿命
		float fRadiusEffect;	// エフェクトの半径
		int nNumEffect;	// エフェクトの数
		float fSpeed;	// エフェクトの基準スピード
		D3DXCOLOR col;	// 色
		int nAdd;	// 加算処理をするかどうか
		float fGravity;	// 重力
		float fDecrease;	// 半径減少量
		float fRangeRot;	// 向きのランダム範囲
		int nRot;	// 向きを反映するかどうか
		bool bTurn;	// 反転するかどうか
		int modeRender;	// 描画モード
	};

	// メンバ変数
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 *m_pPosOwner;	// 持ち主の位置
	D3DXVECTOR3 m_rot;	// 向き
	int m_nLife;	// 寿命
	E_TYPE m_type; // 種類
	int m_nPriorityEffect;	// エフェクトのプライオリティ

	// 静的メンバ変数
	static S_PARTICLE_INFO *m_apParticleInfo[TYPE_MAX + 1];	// パーティクル情報
};

#endif