//*****************************************************
//
// 通常敵の処理[enemyNormal.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "enemyNormal.h"
#include "manager.h"
#include "score.h"
#include "collision.h"
#include "debugproc.h"
#include "particle.h"
#include "player.h"
#include "game.h"
#include "enemyManager.h"
#include "slow.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float SPEED_MOVE = 1.0f;	// 移動速度
const float RATE_RADIUS = 1.5f;	// 当たり判定の大きさの倍率
const float INITIAL_LIFE = 5.0f;	// 初期体力
const int DAMAGE_FRAME = 10;	// ダメージ状態の継続フレーム
const int INITIAL_SCORE = 1000;	// 初期スコア
const int TIME_DEATH = 30;	// 死亡までのタイム
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
int CEnemyNormal::s_nNumAll = 0;	// 総数

//=====================================================
// コンストラクタ
//=====================================================
CEnemyNormal::CEnemyNormal() : m_fLife(0.0f),m_nScore(0),m_fCntAttack(0.0f),m_nTimerState(0),m_pCollisionSphere(nullptr),
								m_pCollisionCube(nullptr),m_pNext(nullptr),m_pPrev(nullptr)
{
	s_nNumAll++;
}

//=====================================================
// デストラクタ
//=====================================================
CEnemyNormal::~CEnemyNormal()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemyNormal::Init(void)
{
	// 最も大きいパーツの半径取得
	float fRadius = GetRadiusMax();

	// 継承クラスの初期化
	CEnemy::Init();

	// タイプの設定
	SetType(TYPE_ENEMY);

	if (m_pCollisionSphere == nullptr)
	{// 球の当たり判定生成
		m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_ENEMY, CCollision::TYPE_SPHERE,this);

		if (m_pCollisionSphere != nullptr)
		{// 情報の設定
			m_pCollisionSphere->SetPosition(GetPosition());
			m_pCollisionSphere->SetRadius(fRadius);
		}
	}

	if (m_pCollisionCube == nullptr)
	{// 立方体の当たり判定
		m_pCollisionCube = CCollisionCube::Create(CCollision::TAG_ENEMY, this);

		D3DXVECTOR3 vtxMax = { fRadius,fRadius,fRadius };
		D3DXVECTOR3 vtxMin = { -fRadius,-fRadius,-fRadius };

		if (m_pCollisionCube != nullptr)
		{
			m_pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	// 体力の初期設定
	m_fLife = INITIAL_LIFE;

	m_nScore = INITIAL_SCORE;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEnemyNormal::Uninit(void)
{
	if (m_pCollisionSphere != nullptr)
	{// 当たり判定の消去
		m_pCollisionSphere->Uninit();

		m_pCollisionSphere = nullptr;
	}

	if (m_pCollisionCube == nullptr)
	{// 立方体の当たり判定
		m_pCollisionCube->Uninit();

		m_pCollisionCube = nullptr;
	}

	// 継承クラスの終了
	CEnemy::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemyNormal::Update(void)
{
	CEnemy::E_STATE state = GetState();

	if (state != STATE_DEATH)
	{
		float fScale = Slow::GetTimeScale();
		float DeltaTime = Manager::GetDeltaTime();

		m_fCntAttack += DeltaTime * fScale;

		if (m_fCntAttack == INT_MAX)
		{
			m_fCntAttack = 0;
		}

		// 継承クラスの更新
		CEnemy::Update();
	}

	// 状態管理処理
	ManageState();

	// 位置の更新
	SetPosition(GetPosition() + GetMove());

	// 当たり判定管理
	ManageCollision();
}

//=====================================================
// 当たり判定の管理
//=====================================================
void CEnemyNormal::ManageCollision(void)
{
	if (m_pCollisionSphere != nullptr)
	{// 球の当たり判定の管理
		m_pCollisionSphere->SetPositionOld(m_pCollisionSphere->GetPosition());

		m_pCollisionSphere->SetPosition(GetPosition());
	}

	if (m_pCollisionCube != nullptr)
	{// 立方体の当たり判定の管理
	 // パーツの最大半径取得
		float fRadius = GetRadiusMax();

		// 当たり判定の位置設定
		m_pCollisionCube->SetPosition(GetPosition());

		D3DXVECTOR3 vtxMax = { fRadius,fRadius,fRadius };
		D3DXVECTOR3 vtxMin = { -fRadius,10.0f,-fRadius };

		D3DXVECTOR3 move = GetMove();

		// 押し出しの当たり判定
		m_pCollisionCube->CollideCube(CCollision::TAG_BLOCK, &move);

		SetMove(move);
	}
}

//=====================================================
// 状態管理
//=====================================================
void CEnemyNormal::ManageState(void)
{
	CEnemy::E_STATE state = GetState();

	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	switch (state)
	{
	case STATE_NORMAL:
		break;
	case STATE_DAMAGE:
		if (m_nTimerState > DAMAGE_FRAME)
		{// 通常状態に戻る
			m_nTimerState = 0;
			state = STATE_NORMAL;
		}
		else
		{// カウントアップ
			m_nTimerState++;
		}

		break;
	case STATE_DEATH:

		m_nTimerState++;

		// 透明になりながら消える
		col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);

		col.a = 1.0f - (float)((float)(m_nTimerState) / (TIME_DEATH));

		SetAllCol(col);

		if (m_nTimerState >= TIME_DEATH)
		{// 死亡
			Death();
		}

		break;
	default:
		break;
	}

	// 状態設定
	SetState(state);
}

//=====================================================
// 死亡処理
//=====================================================
void CEnemyNormal::Death(void)
{
	// 自身の終了
	Uninit();
}

//=====================================================
// 描画処理
//=====================================================
void CEnemyNormal::Draw(void)
{
	// 継承クラスの描画
	CEnemy::Draw();
}

//=====================================================
// 球の当たり判定の位置設定
//=====================================================
void CEnemyNormal::SetSpherePosition(D3DXVECTOR3 pos)
{
	if (m_pCollisionSphere != nullptr)
	{// 位置設定
		m_pCollisionSphere->SetPosition(pos);
	}
}