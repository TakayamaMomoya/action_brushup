//*****************************************************
//
// モーションの処理[motion.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _MOTION_H_
#define _MOTION_H_

//*****************************************************
// インクルード
//*****************************************************
#include "parts.h"
#include "object.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define MAX_PARTS	(20)	// パーツの最大数
#define MAX_MOTION	(20)	// モーションの最大数

//*****************************************************
// クラスの定義
//*****************************************************
class CMotion : public CObject
{
public:
	// 構造体定義
	struct S_Key
	{//キーの構造体
		float fPosX;				//位置X
		float fPosY;				//位置Y
		float fPosZ;				//位置Z
		float fRotX;				//向きX
		float fRotY;				//向きY
		float fRotZ;				//向きZ
	};

	struct S_InfoKey
	{//キー情報構造体
		int nFrame;					//再生フレーム
		S_Key aKey[MAX_PARTS];			//各モデルのキー要素
	};

	struct S_InfoParticle
	{// パーティクル情報構造体
		int nKey;	//生成するキー
		int nFrame;	//生成するフレーム
		int nType;	// 種類
		D3DXVECTOR3 offset;	// オフセット位置
		int nIdxParent;	// 親となるパーツの番号
	};
	
	struct S_InfoCollision
	{// 当たり判定情報構造体
		int nKey;	//生成するキー
		int nFrame;	//生成するフレーム
		D3DXVECTOR3 offset;	// オフセット位置
		int nIdxParent;	// 親となるパーツの番号
	};

	struct S_InfoMotion
	{//モーション情報の構造体
		bool bLoop;						//ループするかどうか
		int nNumKey;					//キーの総数
		S_InfoKey aKeyInfo[MAX_PARTS];	//キー情報
		int nNumParticle;	// パーティクルの数
		int nNumCollision;	// 当たり判定の数
		S_InfoParticle *pParticle;	// パーティクルのポインタ
		S_InfoCollision *pCollision;	// 当たり判定のポインタ
	};

	struct S_Part
	{// パーツの構造体
		int nIdx;
		int nIdxParent;
		CParts *m_pParts;
	};

	CMotion(int nPriority = 5);	// コンストラクタ
	~CMotion();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void Load(char *pPath);	// 読込
	void MultiplyMtx(void);	// マトリックスをかけ合わせる処理
	void SetMatrix(void);	// マトリックス設定
	void CreateAfterImage(D3DXCOLOR col = { 0.0f,0.0f,0.0f,0.0f }, int m_nLife = 10);	// 残像の生成
	void InitPose(int nMotion);	// ポーズの初期化

	// 変数取得・設定関数
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// 位置
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 *GetPosAddress(void) { return &m_pos; }	// 位置のアドレス
	void SetPosShadow(D3DXVECTOR3 pos) { m_posShadow = pos; }	// 影の位置
	void SetPositionOld(D3DXVECTOR3 pos) { m_posOld = pos; }	// 前回の位置
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	D3DXVECTOR3 GetPosPart(int nIdx);	// パーツの位置
	void SetMove(D3DXVECTOR3 move) { m_move = move; }	// 移動量
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// 向き
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetMotion(int nMotionType);	// モーションの種類
	int GetMotion(void) { return m_motionType; }
	void SetKeyOld(void);	// 前回のキー
	S_Part *GetParts(int nIdx) { return m_apParts[nIdx]; }	// パーツ情報
	D3DXMATRIX *GetMatrix(void) { return &m_mtxWorld; }	// マトリックス
	bool IsFinish(void) { return m_bFinish; }	// モーション終了フラグ
	float GetRadiusMax(void);	// 最大半径
	int GetKey(void) { return m_nKey; }	// 現在のキー
	float GetFrame(void) { return m_fCounterMotion; }	// モーションカウンター
	void SetAllCol(D3DXCOLOR col);	// 全パーツの色
	void ResetAllCol(void);
	void EnableShadow(bool bShadow) { m_bShadow = bShadow; }	// モデル影有効フラグ

	// 静的メンバ関数
	static CMotion *Create(char *pPath);	// 生成処理

private:
	// メンバ変数
	S_Part *m_apParts[MAX_PARTS];	// パーツの構造体
	S_InfoMotion m_aMotionInfo[MAX_MOTION];	//モーション情報の構造体
	S_Key m_aKeyOld[MAX_PARTS];	// 前回のキー情報の構造体
	int m_nNumMotion;	//モーションの総数
	int m_motionType;	//モーションの種類
	int m_motionTypeOld;	//前回のモーションの種類
	bool m_bLoopMotion;	//ループするかどうか
	int m_nNumKey;	//キーの総数
	int m_nKey;	//現在のキー
	float m_fCounterMotion;	//モーションカウンター
	int m_nNumParts;	// パーツの数
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_posOld;	// 前回の位置
	D3DXVECTOR3 m_posShadow;	// 影の位置
	D3DXVECTOR3 m_move;	// 移動量
	D3DXVECTOR3 m_rot;							//向き
	D3DXMATRIX m_mtxWorld;	// マトリックス
	bool m_bFinish;	// モーションが終わったかどうか
	bool m_bShadow;	// 影を描画するかどうか
};

#endif