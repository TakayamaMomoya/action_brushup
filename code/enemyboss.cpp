//*****************************************************
//
// ボス敵の処理[enemyboss.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "enemyboss.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "universal.h"
#include "debugproc.h"
#include "game.h"
#include "bullet.h"
#include "missile.h"
#include "effect3D.h"
#include "frame.h"
#include "shadow.h"
#include "score.h"
#include "sound.h"
#include "particle.h"
#include "slow.h"
#include "camera.h"
#include "cameraState.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float INITIAL_LIFE = 60.0f;	// 初期体力
const int INITIAL_SCORE = 3000;	// 初期スコア
const float ROLL_FACT = 0.1f;	// 回転係数
const float MOVE_FACT = 0.04f;	// 移動量減衰係数
const float LINE_END_MOVE = 5.0f;	// 移動終了のしきい値
const float MID_POINT = 2740.0f;	// ボス戦ステージの中央X座標
const float WIDTH_STAGE = 160.0f;	// ステージの幅
const float TIME_DAMAGE = 0.2f;	// 無敵時間
const float FLOAT_HEIGHT = 180.0f;	// 浮かんでいる高さ
const float SHOT_HEIGHT = 30.0f;	// 射撃時の高さ
const float RADIUS_COLLISION = 35.0f;	// 当たり判定の半径
const float SIZE_SHADOW = 40.0f;	// 影のサイズ
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CEnemyBoss *CEnemyBoss::m_pEnemyBoss = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CEnemyBoss::CEnemyBoss() : m_pState(nullptr), m_info()
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemyBoss::~CEnemyBoss()
{

}

//=====================================================
// 生成処理
//=====================================================
CEnemyBoss *CEnemyBoss::Create(void)
{
	if (m_pEnemyBoss == nullptr)
	{
		m_pEnemyBoss = new CEnemyBoss;
	}

	return m_pEnemyBoss;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemyBoss::Init(void)
{
	typeid(CEnemyBossStateDash);

	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		pSound->Stop();

		pSound->Play(CSound::LABEL_BGM_BOSS);
	}

	// フレーム演出の生成
	CFrame::Create(100, 240, 70);

	// 継承クラスの初期化
	CEnemy::Init();

	// 初期の体力設定
	SetLife(INITIAL_LIFE);

	// スコア設定
	SetScore(INITIAL_SCORE);

	// 影の設定
	CShadow *pShadow = GetShadow();

	if (pShadow != nullptr)
	{
		pShadow->SetSize(SIZE_SHADOW, SIZE_SHADOW);
	}

	// カメラをボス出現のものに変更
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->ChangeState(new CCameraStateApperBoss);
	}

	// ステイトの切り替え
	ChangeState(new CEnemyBossStateApper);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEnemyBoss::Uninit(void)
{
	CParticle::Create(GetMtxPos(0), CParticle::TYPE_EXPLOSION);

	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		pSound->Play(CSound::LABEL_SE_EXPLOSION);
	}

	m_pEnemyBoss = nullptr;

	// 継承クラスの終了
	CEnemy::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemyBoss::Update(void)
{
	// 位置を保存
	SetPositionOld(GetPosition());

	// 継承クラスの更新
	CEnemy::Update();

	// 状態管理
	ManageState();

	if (m_pState != nullptr)
	{// ステイトの更新
		m_pState->Update(this);
	}
	
	// 当たり判定管理
	ManageCollision();
}

//=====================================================
// 状態管理
//=====================================================
void CEnemyBoss::ManageState(void)
{
	CEnemy::STATE state = CEnemy::GetState();

	float fTimer = GetCntState();
	float fAddTime = CManager::GetDeltaTime() * Slow::GetTimeScale();

	switch (state)
	{
	case CEnemy::STATE_NORMAL:
		break;
	case CEnemy::STATE_DAMAGE:

		fTimer += fAddTime;

		SetAllCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		if (fTimer > TIME_DAMAGE)
		{// 通常状態に戻る
			fTimer = 0;
			state = CEnemy::STATE_NORMAL;

			ResetAllCol();
		}
		break;
	case CEnemy::STATE_DEATH:
		if (m_info.fTimerState >= 180)
		{
			Death();
		}
		else
		{
			m_info.fTimerState++;
		}

		break;
	default:
		break;
	}

	CEnemy::SetState(state);

	SetCntState(fTimer);
}

//=====================================================
// 当たり判定管理
//=====================================================
void CEnemyBoss::ManageCollision(void)
{
	// 当たり判定追従
	FollowCollision();
}

//=====================================================
// 当たり判定の追従
//=====================================================
void CEnemyBoss::FollowCollision(void)
{
	CCollisionSphere *pCollision = GetClsnSphere();

	if (pCollision != nullptr)
	{
		D3DXVECTOR3 pos = GetMtxPos(IDX_WAIST);

		pCollision->SetPositionOld(pCollision->GetPosition());
		pCollision->SetPosition(pos);
		pCollision->SetRadius(RADIUS_COLLISION);
	}
}

//=====================================================
// ステイトの切り替え
//=====================================================
void CEnemyBoss::ChangeState(CEnemyBossState *pState)
{
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	m_pState = pState;

	if (m_pState != nullptr)
	{
		m_pState->Init(this);
	}
}

//=====================================================
// 目標位置への移動
//=====================================================
bool CEnemyBoss::FollowDest(void)
{
	bool bEnd = false;

	D3DXVECTOR3 pos = GetPosition();

	D3DXVECTOR3 vecDiff = m_info.posDest - pos;

	// 差分距離の取得
	float fLength = D3DXVec3Length(&vecDiff);

	if (LINE_END_MOVE > fLength)
	{
		bEnd = true;
	}

	vecDiff *= MOVE_FACT;

	pos += vecDiff;

	SetPosition(pos);

	return bEnd;
}

//=====================================================
// 状態の切り替え
//=====================================================
void CEnemyBoss::SwitchState(void)
{
	ATTACKSTATE state;

	// 状態を振る
	state = (ATTACKSTATE)(rand() % (ATTACK_MAX));

	while (m_info.attackState == state)
	{
		state = (ATTACKSTATE)(rand() % (ATTACK_MAX));
	}

	m_info.attackState = state;

	// ステイトの生成
	CEnemyBossState *pState = nullptr;

	switch (m_info.attackState)
	{
	case ATTACK_MISSILE:
		pState = new CEnemyBossStateMissile;
		break;
	case ATTACK_DASH:
		pState = new CEnemyBossStateDash;
		break;
	case ATTACK_SHOT:
		pState = new CEnemyBossStateShot;
		break;
	default:
		break;
	}

	// 状態の切り替え
	ChangeState(pState);
}

//=====================================================
// ヒット処理
//=====================================================
void CEnemyBoss::Hit(float fDamage)
{
	CEnemy::STATE state = CEnemy::GetState();

	if (state == CEnemy::STATE_NORMAL)
	{
		float fLife = CEnemy::GetLife();

		fLife -= fDamage;

		CSound *pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(CSound::LABEL_SE_HIT_BOSS);
		}

		if (fLife <= 0.0f)
		{// 死亡状態
			fLife = 0.0f;

			// モーションの設定
			SetMotion(MOTION_DEATH);

			// パーティクルの発生
			CParticle::Create(GetMtxPos(IDX_WAIST), CParticle::TYPE_FIRE);

			// ゲームを終了状態にする
			CGame::SetState(CGame::STATE_END);

			// 死亡状態に変更
			m_info.state = STATE_NONE;
			state = CEnemy::STATE_DEATH;

			// スコア管理
			ManageScore();

			// スコア設定
			CScore *pScore = CScore::GetInstance();

			if (pScore != nullptr)
			{
				pScore->SetResultScore();
			}

			// 当たり判定削除
			DeleteCollision();

			if (m_pState != nullptr)
			{// ステイトの破棄
				delete m_pState;
				m_pState = nullptr;
			}
		}
		else
		{
			state = CEnemy::STATE_DAMAGE;
		}

		CEnemy::SetLife(fLife);
	}

	CEnemy::SetState(state);
}

//=====================================================
// 描画処理
//=====================================================
void CEnemyBoss::Draw(void)
{
	// 継承クラスの描画
	CEnemy::Draw();

#ifdef _DEBUG
	CDebugProc::GetInstance()->Print("\nボス位置：[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CDebugProc::GetInstance()->Print("\nボス体力：[%f]", GetLife());
	CDebugProc::GetInstance()->Print("\nボス状態：[%d]",CEnemy::GetState());
	CDebugProc::GetInstance()->Print("\nボスモーション：[%d]", GetMotion());
	CDebugProc::GetInstance()->Print("\nキー：[%d]", GetKey());
	CDebugProc::GetInstance()->Print("\nフレーム：[%d]", GetFrame());
	CDebugProc::GetInstance()->Print("\nIsFinish：[%d]", IsFinish());
#endif
}