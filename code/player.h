//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:髙山桃也
//
//*****************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"
#include "motion.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CCollisionCube;
class CCollisionSphere;

//*****************************************************
// クラスの定義
//*****************************************************
class CPlayer : public CObject
{
public:
	// 列挙型定義
	enum E_MOTION
	{// モーションの種類
		MOTION_NEUTRAL = 0,	// 待機状態
		MOTION_MOVE,	// 移動モーション
		MOTION_JUMP,	// ジャンプモーション
		MOTION_FALL,	// 落下モーション
		MOTION_ATTACK,	// 攻撃モーション
		MOTION_ATTACKTURN,	// 反転攻撃モーション
		MOTION_AIRATTACK,	// 空中攻撃モーション
		MOTION_PARRY,	// パリィモーション
		MOTION_DASH,	// ダッシュモーション
		MOTION_TITLE_NEUTRAL,	// タイトル待機
		MOTION_TITLE_STANDUP,	// タイトル立ち上がり
		MOTION_APPER,	// 出現モーション
		MOTION_MAX
	};
	
	// 構造体定義
	struct S_Param
	{// パラメーター
		int nInitialLife;	// 初期体力
		float fSpeedMove;	// 移動速度
		float fGravity;	// 重力
		float fFactMove;	// 移動減衰係数
		float fFactRoll;	// 回転係数
		float fSpeedDash;	// ダッシュの速度
		float fPowJump;	// ジャンプ力
		float fPowAttackJump;	// 二段ジャンプ力
		int nTimeDamage;	// ダメージ状態の時間
		int nTimeDash;	// ダッシュのクールタイム
	};

	CPlayer(int nPriority = 4);	// コンストラクタ
	~CPlayer();	// デストラクタ
	
	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void Hit(float fDamage);	// ヒット処理

	// 変数取得・設定関数
	void SetPosition(D3DXVECTOR3 pos) { m_info.pos = pos; }	// 位置
	D3DXVECTOR3 GetPosition(void) { return m_info.pos; }
	void SetMove(D3DXVECTOR3 move) { m_info.move = move; }	// 移動量
	D3DXVECTOR3 GetMove(void) { return m_info.move; }
	void SetPositionOld(D3DXVECTOR3 pos) { m_info.posOld = pos; }	// 前回の位置
	D3DXVECTOR3 GetPositionOld(void) { return m_info.posOld; }
	void SetRot(D3DXVECTOR3 rot) { m_info.rot = rot; }	// 向き
	D3DXVECTOR3 GetRot(void) { return m_info.rot; }
	int GetLife(void) { return m_info.nLife; }	// ライフ
	S_Param GetParam(void) { return m_param; }	// パラメーター
	CMotion *GetBody(void) { return m_info.pBody; }	// 見た目

	// 静的メンバ関数
	static CPlayer *Create(void);	// 生成処理
	static CPlayer *GetInstance(void) { return s_pPlayer; }	// インスタンスの取得

private:
	// 列挙型定義
	enum E_STATE
	{// 状態
		STATE_NONE = 0,	// 何でもない状態
		STATE_NORMAL,	// 通常状態
		STATE_DAMAGE,	// ダメージ状態
		STATE_MAX
	};
	enum E_JUMPSTATE
	{// ジャンプ状態
		JUMPSTATE_NONE = 0,
		JUMPSTATE_NORMAL,
		JUMPSTATE_ATTACK,
		JUMPSTATE_MAX
	};

	// 構造体定義
	struct S_AttackInfo
	{// 攻撃の情報
		int nIdxMotion;	// モーション番号
		int nIdxParent;	// 親パーツ番号
		D3DXVECTOR3 pos;	// オフセット位置
		int nKey;	// キー番号
		int nFrame;	// 発生するフレーム
		float fRadius;	// 半径
		float fScaleHitStop;	// ヒットストップのタイムスケール
		float fTimeHitStop;	// ヒットストップの持続時間
	};
	struct S_Info
	{// ステータス情報
		int nLife;	// 体力
		int nCntAfterImage;	// 残像を出すカウンター
		int nCntState;	// 状態遷移カウンター
		int nTimeParry;	// パリィ継続時間
		int nCntParry;	// パリィのカウンター
		int nCntDash;	// ダッシュのカウンター
		bool bSprint;	// ダッシュ状態かどうか
		bool bAttack;	// 攻撃フラグ
		float fRadiusParry;	// パリィ判定の半径
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 posOld;	// 前回の位置
		D3DXVECTOR3 offsetParry;	// パリィ判定のオフセット
		D3DXVECTOR3 move;	// 移動量
		D3DXVECTOR3 rot;	// 向き
		D3DXVECTOR3 rotDest;	// 目標の向き
		CMotion *pBody;	// 体のポインタ
		CCollisionCube *pCollisionCube;	// 立方体の当たり判定
		CCollisionSphere *pClsnAttack;	// 攻撃の当たり判定
		CCollisionSphere *pClsnHit;	// 被弾当たり判定
		int nNumAttack;	// 攻撃判定の数
		S_AttackInfo *pAttackInfo;	// 攻撃の情報ポインタ
		E_STATE state;	// 状態
		E_JUMPSTATE jump;	// ジャンプ状態
	};

	// メンバ関数
	void Load(void);	// 読込
	void LoadParam(FILE *pFile,char *pTemp);	// パラメータ読込
	void ManageState(void);	// 状態管理
	void Input(void);	// 入力
	void InputMove(void);	// 移動の入力
	void InputAttack(void);	// 攻撃の入力
	void Parry(void);	// パリィの操作
	void ManageMotion(void);	// モーションの管理
	void ManageCollision(void);	// 当たり判定の管理
	void RotDest(void);	// 目標を向く処理
	void ManageAttack(void);	// 攻撃の管理
	void SetAttackCollision(S_AttackInfo attackInfo);	// 攻撃判定の設定
	void Death(void);	// 死亡処理
	void SetMotion(E_MOTION motion);	// モーションの設定

	// メンバ変数
	S_Info m_info;	// 自身の情報
	S_Param m_param;	// パラメーター

	// 静的メンバ変数
	static CPlayer *s_pPlayer;	// 自身のポインタ
};

#endif