//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "inputjoypad.h"
#include "inputManager.h"
#include "debugproc.h"
#include "particle.h"
#include "sound.h"
#include "collision.h"
#include "model.h"
#include "texture.h"
#include "camera.h"
#include "collision.h"
#include "universal.h"
#include "game.h"
#include "motion.h"
#include "afterimage.h"
#include "effect3D.h"
#include "fade.h"
#include "enemyManager.h"
#include "bullet.h"
#include "animManager.h"
#include "shadow.h"
#include "block.h"
#include "orbit.h"
#include "frame.h"
#include "timer.h"
#include "cameraState.h"
#include "slow.h"
#include "blur.h"
#include "blurEvent.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const char* PARAM_PATH = "data\\TEXT\\player.txt";	// パラメーターのパス
const float LINE_STOP = 0.3f;	// 動いてる判定のしきい値
const int TIME_AFTERIMAGE = 4;	// 残像を出す頻度
const float BULLET_SPEED = 5.0f;	// 弾いた弾速度
const float BULLET_SIZE = 3.0f;	// 弾いた弾サイズ
const CScene::E_MODE MODE_DEATH = CScene::MODE_GAME;	// 死んだ後に遷移するモード
const float TIME_HITSTOP_SLASH = 0.1f;	// 斬撃のヒットストップ時間
const float SCALE_HITSTOP_SLASH = 0.1f;	// 斬撃のヒットストップタイムスケール
const float TIME_BLUR_DASH = 0.4f;	// ダッシュのブラー時間
const float DESITY_BLUR_DASH = 0.4f;	// ダッシュのブラーの濃さ
const float SIZE_BLUR_DASH = 0.4f;	// ダッシュのブラーサイズ
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CPlayer *CPlayer::s_pPlayer = nullptr;	// 自身のポインタ

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CPlayer::CPlayer(int nPriority)
{
	ZeroMemory(&m_info, sizeof(CPlayer::S_Info));
}

//=====================================================
// デストラクタ
//=====================================================
CPlayer::~CPlayer()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CPlayer::Init(void)
{
	// 情報の読込
	Load();

	// 初期位置に設定
	SetPosition(D3DXVECTOR3(0.0f, -16.0f, 0.0f));

	// 値の初期化
	m_info.state = STATE_NORMAL;
	m_info.jump = JUMPSTATE_NORMAL;

	if (m_info.pCollisionCube == nullptr)
	{// 立方体の当たり判定
		m_info.pCollisionCube = CCollisionCube::Create(CCollision::TAG_PLAYER, this);

		D3DXVECTOR3 vtxMax = { 5.0f,20.0f,5.0f };
		D3DXVECTOR3 vtxMin = { -5.0f,0.0f,-5.0f };

		if (m_info.pCollisionCube != nullptr)
		{
			m_info.pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	if (m_info.pClsnAttack == nullptr)
	{// 球の当たり判定生成
		m_info.pClsnAttack = CCollisionSphere::Create(CCollision::TAG_NONE, CCollision::TYPE_SPHERE, this);

		if (m_info.pClsnAttack != nullptr)
		{// 情報の設定
			m_info.pClsnAttack->SetPosition(D3DXVECTOR3(0.0f,0.0f,0.0f));
			m_info.pClsnAttack->SetRadius(0.0f);
		}
	}

	if (m_info.pClsnHit == nullptr)
	{// 被弾当たり判定生成
		m_info.pClsnHit = CCollisionSphere::Create(CCollision::TAG_PLAYER, CCollision::TYPE_SPHERE, this);

		if (m_info.pClsnHit != nullptr)
		{// 情報の設定
			m_info.pClsnHit->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_info.pClsnHit->SetRadius(1.0f);
		}
	}

	// 初期の向き設定
	D3DXVECTOR3 rot = { 0.0f,-D3DX_PI * 0.5f,0.0f };

	m_info.rotDest = rot;
	SetRot(rot);

	// 進行度の取得
	CGame *pGame = CGame::GetInstance();
	int nProgress = 0;

	if (pGame != nullptr)
	{
		nProgress = pGame->GetProgress();
	}

#ifndef _DEBUG
	if (nProgress == 0)
	{// 出現演出の開始
		SetMotion(MOTION_APPER);

		// タイマーを止める
		CTimer *pTimer = CTimer::GetInstance();

		if (pTimer != nullptr)
		{
			pTimer->EnableStop(true);
		}

		// フレーム演出の生成
		CFrame::Create(20, 120, 70);

		// カメラ距離の設定
		CCamera *pCamera = Manager::GetCamera();

		if (pCamera != nullptr)
		{
			pCamera->SetDist(100.0f);

			pCamera->ChangeState(new CCameraStateApperPlayer);
		}
	}
	else
#endif
	{
		// カメラに追従ステイトを設定
		CCamera *pCamera = Manager::GetCamera();

		if (pCamera != nullptr)
		{
			pCamera->ChangeState(new CCameraStateFollowPlayer);
		}
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CPlayer::Uninit(void)
{
	if (m_info.pBody != nullptr)
	{// 体の破棄
		m_info.pBody->Uninit();
		m_info.pBody = nullptr;
	}

	if (m_info.pCollisionCube != nullptr)
	{// 当たり判定破棄
		m_info.pCollisionCube->Uninit();
		m_info.pCollisionCube = nullptr;
	}

	if (m_info.pClsnAttack != nullptr)
	{// 攻撃当たり判定破棄
		m_info.pClsnAttack->Uninit();
		m_info.pClsnAttack = nullptr;
	}

	if (m_info.pClsnHit != nullptr)
	{// 被弾当たり判定破棄
		m_info.pClsnHit->Uninit();
		m_info.pClsnHit = nullptr;
	}

	if (s_pPlayer != nullptr)
	{// 自身のポインタを空にする
		s_pPlayer = nullptr;
	}

	// 自身の破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CPlayer::Update(void)
{
	// 前回の位置を保存
	m_info.posOld = m_info.pos;

	// 状態管理
	ManageState();

	int nMotion = MOTION_NEUTRAL;

	if (m_info.pBody != nullptr)
	{
		nMotion = m_info.pBody->GetMotion();
	}

	if (nMotion != MOTION_APPER)
	{
		// 操作処理
		Input();

		// モーションの管理
		ManageMotion();

		// 目標方向を向く処理
		RotDest();

		float fScale = Slow::GetTimeScale();

		// 位置に移動量を反映
		m_info.pos += m_info.move * fScale;

		// 当たり判定管理
		ManageCollision();

		// 移動量減衰
		m_info.move.x += (0 - m_info.move.x) * m_param.fFactMove * fScale;

		if (m_info.pBody != nullptr)
		{
			if (m_info.pBody->GetMotion() != MOTION_DASH || m_info.pBody->IsFinish())
			{
				m_info.move.y -= m_param.fGravity * fScale;
			}
		}
	}
	else
	{
		if (m_info.pBody != nullptr)
		{
			if (m_info.pBody->IsFinish())
			{
				SetMotion(MOTION_NEUTRAL);

				// タイマーを動かす
				CTimer *pTimer = CTimer::GetInstance();

				if (pTimer != nullptr)
				{
					pTimer->EnableStop(false);
				}

				// カメラ距離の設定
				CCamera *pCamera = Manager::GetCamera();

				if (pCamera != nullptr)
				{
					pCamera->ChangeState(new CCameraStateFollowPlayer);
				}
			}
		}
	}

	if (m_info.pBody != nullptr)
	{// 体の追従
		m_info.pBody->SetPosition(m_info.pos);
		m_info.pBody->SetRot(m_info.rot);
	}

	if (m_info.pBody != nullptr)
	{// 影の追従

		float fHeight = 0.0f;

		// ブロックの高さを取得
		fHeight = CBlock::CheckShadow(GetPosition());

		// 影の位置設定
		m_info.pBody->SetPosShadow(D3DXVECTOR3(GetPosition().x, fHeight + 0.1f, GetPosition().z));
	}
}

//=====================================================
// 状態管理
//=====================================================
void CPlayer::ManageState(void)
{
	switch (m_info.state)
	{
	case CPlayer::STATE_NORMAL:
		break;
	case CPlayer::STATE_DAMAGE:

		m_info.nCntState++;

		if (m_info.nCntState >= m_param.nTimeDamage)
		{
			m_info.state = STATE_NORMAL;

			if (m_info.pBody != nullptr)
			{
				m_info.pBody->ResetAllCol();
			}

			m_info.nCntState = 0;
		}

		break;
	default:
		break;
	}
}

//=====================================================
// 操作処理
//=====================================================
void CPlayer::Input(void)
{
	// 移動操作
	InputMove();

	// 攻撃操作
	InputAttack();
}

//=====================================================
// 移動操作
//=====================================================
void CPlayer::InputMove(void)
{
	// 情報入手
	CInputMouse *pMouse = CInputMouse::GetInstance();
	CInputManager *pInputManager = CInputManager::GetInstance();
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pMouse == nullptr || m_info.pBody == nullptr)
	{
		return;
	}

	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f }, rot = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 vecStick;
	int nMotion = m_info.pBody->GetMotion();
	float fScale = Slow::GetTimeScale();

	{// 攻撃中でなければ
		if (nMotion != MOTION_PARRY ||
			m_info.jump > JUMPSTATE_NONE)
		{// 地上でパリィしてなければ移動
			if (pInputManager->GetPress(CInputManager::BUTTON_MOVE_LEFT))
			{// 左移動
				move.x -= m_param.fSpeedMove * fScale;
				m_info.rotDest.y = D3DX_PI * 0.5f;
			}
			if (pInputManager->GetPress(CInputManager::BUTTON_MOVE_RIGHT))
			{// 右移動
				move.x += m_param.fSpeedMove * fScale;
				m_info.rotDest.y = -D3DX_PI * 0.5f;
			}

			// ジャンプ操作
			if (pInputManager->GetTrigger(CInputManager::BUTTON_JUMP))
			{
				if (m_info.jump == JUMPSTATE_NONE)
				{
					move.y += m_param.fPowJump;

					m_info.jump = JUMPSTATE_NORMAL;

					SetMotion(MOTION_JUMP);

					CAnimManager *pAnim3D = CAnimManager::GetInstance();

					if (pAnim3D != nullptr)
					{
						D3DXVECTOR3 posEffect = GetPosition();
						posEffect.y += 15.0f;
						posEffect.x += move.x;
						posEffect.z -= 5.0f;

						pAnim3D->CreateEffect(posEffect, CAnimManager::TYPE_JUMP);
					}

					CSound *pSound = CSound::GetInstance();

					if (pSound != nullptr)
					{
						pSound->Play(CSound::LABEL_SE_JUMP);
					}
				}
				else if (m_info.jump == JUMPSTATE_NORMAL)
				{// 空中攻撃
					SetMotion(MOTION_AIRATTACK);

					D3DXVECTOR3 move = { GetMove().x,m_param.fPowAttackJump,GetMove().z };

					// 移動量加算
					SetMove(move);

					m_info.jump = JUMPSTATE_ATTACK;

					CAnimManager *pAnim3D = CAnimManager::GetInstance();

					if (pAnim3D != nullptr)
					{
						D3DXVECTOR3 posEffect = GetPosition();

						posEffect.y += 10.0f;

						pAnim3D->CreateEffect(posEffect, CAnimManager::TYPE_AIRSLASH);
					}

					CSound *pSound = CSound::GetInstance();

					if (pSound != nullptr)
					{
						pSound->Play(CSound::LABEL_SE_AIRATTACK);
					}
				}

			}


			// 移動量加算
			SetMove(GetMove() + move);
		}
	}

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_E))
	{// ボス戦までワープ
		m_info.pos = { 2599.0f,204.57f,0.0f };
		m_info.posOld = { 2579.0f,204.57f,0.0f };
	}
#endif
}

//=====================================================
// 攻撃操作
//=====================================================
void CPlayer::InputAttack(void)
{
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager == nullptr || m_info.pBody == nullptr)
		return;

	if (pInputManager->GetTrigger(CInputManager::BUTTON_ATTACK))
	{// 近接攻撃
		if (m_info.pBody->GetMotion() == MOTION_ATTACK || m_info.pBody->GetMotion() == MOTION_ATTACKTURN)
		{
			m_info.bAttack = true;
		}
		else
		{
			SetMotion(MOTION_ATTACK);

			m_info.bAttack = false;

			CSound *pSound = CSound::GetInstance();

			if (pSound != nullptr)
			{
				pSound->Play(CSound::LABEL_SE_ATTACK);
			}
		}
	}

	if (m_info.nCntDash >= m_param.nTimeDash)
	{// ダッシュ
		if (pInputManager->GetTrigger(CInputManager::BUTTON_DASH))
		{
			if (m_info.pBody->GetMotion() != MOTION_DASH)
			{
				m_info.nCntDash = 0;	// ダッシュカウンターをリセット

				// ダッシュの移動量を加算
				D3DXVECTOR3 move = GetMove();
				move.x -= sinf(m_info.rotDest.y) * m_param.fSpeedDash;
				move.y = 0;	// 重力を消す
				SetMove(move);

				// モーションの設定
				SetMotion(MOTION_DASH);

				// サウンド再生
				Sound::Play(CSound::LABEL_SE_DASH);

				// ブラーをかける
				CBlurEvent::Create(TIME_BLUR_DASH, DESITY_BLUR_DASH, SIZE_BLUR_DASH);
			}
		}
	}
	else
	{
		m_info.nCntDash++;
	}

	if (m_info.pBody != nullptr)
	{
		if (m_info.pBody->IsFinish())
		{// 連撃の処理
			if (m_info.bAttack == true)
			{
				if (m_info.pBody->GetMotion() == MOTION_ATTACK)
				{
					SetMotion(MOTION_ATTACKTURN);

					m_info.bAttack = false;
				}
				else
				{
					SetMotion(MOTION_ATTACK);

					m_info.bAttack = false;
				}

				CSound *pSound = CSound::GetInstance();

				if (pSound != nullptr)
				{
					pSound->Play(CSound::LABEL_SE_ATTACK);
				}
			}
		}

		// パリィ
		Parry();
	}
}

//=====================================================
// パリィ
//=====================================================
void CPlayer::Parry(void)
{
	// 情報入手
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (m_info.pBody == nullptr || m_info.pClsnAttack == nullptr)
	{
		return;
	}

	if (pInputManager->GetTrigger(CInputManager::BUTTON_PARRY) &&
		m_info.pBody->GetMotion() != MOTION_PARRY)
	{// パリィ
		SetMotion(MOTION_PARRY);

		m_info.nCntParry = 0;

		CSound *pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(CSound::LABEL_SE_ATTACK);
		}
	}

	if (m_info.nCntParry >= m_info.nTimeParry)
	{// ここから下はパリィ中しか通らない
		return;
	}
	else
	{
		m_info.nCntParry++;
	}

	D3DXMATRIX mtx;
	D3DXVECTOR3 pos;
	bool bHit = false;

	universal::SetOffSet(&mtx, *m_info.pBody->GetMatrix(), m_info.offsetParry);

	pos =
	{
		mtx._41,
		mtx._42,
		mtx._43
	};

	// 位置設定
	m_info.pClsnAttack->SetPosition(pos);
	
	// 半径の設定
	m_info.pClsnAttack->SetRadius(m_info.fRadiusParry);

#ifdef _DEBUG
	//  CEffect3D::Create(pos, m_info.fRadiusParry, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#endif

	// 命中したかの判定
	bHit = m_info.pClsnAttack->SphereCollision(CCollision::TAG_ENEMYBULLET);

	// 命中したオブジェクトの取得
	CObject *pObj = m_info.pClsnAttack->GetOther();

	if (bHit == true && pObj != nullptr)
	{//	パリィ成功
		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		D3DXVECTOR3 posTarget;

		pos = pObj->GetPosition();

		// 敵の取得
		CEnemyManager *pEnemyManager = CEnemyManager::GetInstance();

		CEnemy *pEnemy = nullptr;
		CEnemy *pLockEnemy = nullptr;
		float fLengthDest = FLT_MAX;

		if (pEnemyManager != nullptr)
		{
			pEnemy = pEnemyManager->GetHead();
		}

		int nNum = CEnemy::GetNumAll();

		while (pEnemy != nullptr)
		{
			// 次のアドレスを保存
			CEnemy *pEnemyNext = pEnemy->GetNext();

			// 差分ベクトルから移動量を設定
			posTarget = pEnemy->GetPosition();

			// プレイヤーとの距離を測る
			D3DXVECTOR3 vecDiff;
			vecDiff = posTarget - pos;

			float fLength = D3DXVec3Length(&vecDiff);
			
			if (fLength < fLengthDest)
			{// 近い敵の更新
				fLengthDest = fLength;
				pLockEnemy = pEnemy;
			}

			// 次のアドレスを代入
			pEnemy = pEnemyNext;
		}

		// 差分ベクトルから移動量を設定
		posTarget = pLockEnemy->GetPosPart(0);

		move = posTarget - pos;

		D3DXVec3Normalize(&move, &move);

		move *= BULLET_SPEED;

		pObj->Uninit();

		// 弾いた弾の射出
		CBullet::Create(pos, move, 200, CBullet::TYPE_PLAYER,false, BULLET_SIZE);

		CAnimManager *pAnim3D = CAnimManager::GetInstance();

		if (pAnim3D != nullptr)
		{
			pAnim3D->CreateEffect(pos, CAnimManager::TYPE_SLASH);
			pAnim3D->CreateEffect(pos, CAnimManager::TYPE_FLASH);
		}

		CParticle::Create(pos,CParticle::TYPE_SPARK);

		CSound *pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(CSound::LABEL_SE_PARRY);
		}
	}
}

//=====================================================
// モーションの管理
//=====================================================
void CPlayer::ManageMotion(void)
{
	if (m_info.pBody == nullptr)
	{
		return;
	}

	// 移動量の取得
	D3DXVECTOR3 move = GetMove();

	bool bFinish = m_info.pBody->IsFinish();
	int nMotion = m_info.pBody->GetMotion();

	if (m_info.jump == JUMPSTATE_NONE)
	{
		if (m_info.bAttack == false &&
			(m_info.pBody->GetMotion() != MOTION_ATTACK && 
				m_info.pBody->GetMotion() != MOTION_ATTACKTURN && 
				m_info.pBody->GetMotion() != MOTION_PARRY &&
				m_info.pBody->GetMotion() != MOTION_DASH))
		{// 移動モーション
			if (move.x * move.x > LINE_STOP * LINE_STOP)
			{// ある程度動いていれば歩きモーション
				SetMotion(MOTION_MOVE);
			}
			else
			{// 待機モーションへ移行
				SetMotion(MOTION_NEUTRAL);

				m_info.nCntAfterImage = 0;
			}
		}
		else
		{// 攻撃モーション管理
			if (bFinish == true)
			{
				SetMotion(MOTION_NEUTRAL);
			}
		}
	}
	else
	{
		if (move.y < 0.0f && 
			(nMotion == MOTION_AIRATTACK && bFinish == false) == false &&
			(nMotion == MOTION_PARRY && bFinish == false) == false && 
			(nMotion == MOTION_ATTACK && bFinish == false) == false &&
			(nMotion == MOTION_ATTACKTURN && bFinish == false) == false &&
			(nMotion == MOTION_DASH && bFinish == false) == false)
		{// 落下モーション
			SetMotion(MOTION_FALL);
		}
	}

	// 移動量の計算
	float fSpeed = D3DXVec3Length(&move);

	if (nMotion == MOTION_AIRATTACK || nMotion == MOTION_APPER || nMotion == MOTION_DASH)
	{// 特定モーションの場合に残像を出す
		m_info.nCntAfterImage++;

		if (m_info.nCntAfterImage >= TIME_AFTERIMAGE)
		{
			// 残像の生成
			m_info.pBody->CreateAfterImage(D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f), 20);

			m_info.nCntAfterImage = 0;
		}
	}
}

//=====================================================
// 当たり判定の管理
//=====================================================
void CPlayer::ManageCollision(void)
{
	bool bLandFloor = false;
	bool bLandBlock = false;

	CFade *pFade = CFade::GetInstance();

	if (m_info.pCollisionCube != nullptr)
	{// 当たり判定の管理

		m_info.pCollisionCube->SetPosition(GetPosition());

		D3DXVECTOR3 move = GetMove();

		// 押し出しの当たり判定
		bLandBlock = m_info.pCollisionCube->CollideCube(CCollision::TAG_BLOCK, &move);

		SetMove(move);

		if (m_info.jump != JUMPSTATE_NONE && 
			bLandBlock)
		{
			m_info.jump = JUMPSTATE_NONE;
		}
		else if(bLandBlock == false && 
			m_info.jump == JUMPSTATE_NONE)
		{
			m_info.jump = JUMPSTATE_NORMAL;
		}
	}

	if (m_info.pClsnHit != nullptr)
	{
		if (m_info.pBody != nullptr)
		{
			if (m_info.pBody->GetParts(0) != nullptr)
			{
				D3DXMATRIX mtx = *m_info.pBody->GetParts(0)->m_pParts->GetMatrix();
				D3DXVECTOR3 pos =
				{
					mtx._41,
					mtx._42,
					mtx._43,
				};

				m_info.pClsnHit->SetPositionOld(m_info.pClsnHit->GetPosition());
				m_info.pClsnHit->SetPosition(pos);

				if (m_info.pClsnHit->SphereCollision(CCollision::TAG_ENEMY))
				{
					Hit(5.0f);
				}
			}
		}
	}

	// 落下死判定=============
	if (m_info.pos.y <= -190.0f)
	{
		CFade *pFade = CFade::GetInstance();

		if (pFade != nullptr)
		{
			pFade->SetFade(MODE_DEATH);
		}
	}
	// =======================

	// 攻撃判定の管理
	ManageAttack();
}

//=====================================================
// 攻撃判定の管理
//=====================================================
void CPlayer::ManageAttack(void)
{
	if (m_info.pClsnAttack == nullptr)
	{// 判定のエラー
		return;
	}

	if (m_info.pBody == nullptr)
	{// モーションのエラー
		return;
	}

	for (int i = 0; i < m_info.nNumAttack; i++)
	{
		if (m_info.pBody->GetMotion() == m_info.pAttackInfo[i].nIdxMotion)
		{// 攻撃モーション中の判定
			float fFrame = m_info.pBody->GetFrame();
			int nKey = m_info.pBody->GetKey();
			D3DXVECTOR3 pos;

			if (fFrame == m_info.pAttackInfo[i].nFrame && nKey == m_info.pAttackInfo[i].nKey)
			{// 当たり判定の設定
				SetAttackCollision(m_info.pAttackInfo[i]);
			}
		}
	}
}

//=====================================================
// 攻撃判定の設定
//=====================================================
void CPlayer::SetAttackCollision(S_AttackInfo attackInfo)
{
	bool bHit = false;
	D3DXMATRIX mtx;

	universal::SetOffSet(&mtx, *m_info.pBody->GetMatrix(), attackInfo.pos);

	D3DXVECTOR3 pos =
	{
		mtx._41,
		mtx._42,
		mtx._43
	};

#ifdef _DEBUG
	CEffect3D::Create(pos, attackInfo.fRadius, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// 攻撃判定の可視化
#endif

				// 位置設定
	m_info.pClsnAttack->SetPosition(pos);

	// 半径の設定
	m_info.pClsnAttack->SetRadius(attackInfo.fRadius);

	bHit = m_info.pClsnAttack->SphereCollision(CCollision::TAG_ENEMY);
	CObject *pObj = m_info.pClsnAttack->GetOther();

	if (bHit == true && pObj != nullptr)
	{// 命中時のヒット処理
		// アニメーションエフェクトの再生
		CAnimManager *pAnim3D = CAnimManager::GetInstance();

		if (pAnim3D != nullptr)
		{
			pAnim3D->CreateEffect(pos, CAnimManager::TYPE_FLASH);
		}

		// ヒットストップの発生
		CSlow *pSlow = CSlow::GetInstance();

		if (pSlow != nullptr)
		{
			pSlow->SetSlowTime(attackInfo.fTimeHitStop, attackInfo.fScaleHitStop);
		}

		// 当たったオブジェクトのヒット処理
		pObj->Hit(5.0f);

		// 音の再生
		CSound *pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(CSound::LABEL_SE_HIT_NORMAL);
		}
	}
}

//=====================================================
// 目標方向を向く処理
//=====================================================
void CPlayer::RotDest(void)
{
	D3DXVECTOR3 vecDest;
	D3DXVECTOR3 rot = GetRot();

	float fRotDiff = m_info.rotDest.y - rot.y;

	// 角度の修正
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= 6.28f;
	}
	if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += 6.28f;
	}

	// 角度補正
	SetRot(D3DXVECTOR3(rot.x, rot.y + fRotDiff * m_param.fFactRoll, rot.z));

	// 角度の修正
	rot = GetRot();

	if (GetRot().y > D3DX_PI)
	{
		// 角度補正
		SetRot(D3DXVECTOR3(GetRot().x, GetRot().y - 6.28f, GetRot().z));
	}
	if (GetRot().y < -D3DX_PI)
	{
		// 角度補正
		SetRot(D3DXVECTOR3(GetRot().x, GetRot().y + 6.28f, GetRot().z));
	}
}

//=====================================================
// ヒット処理
//=====================================================
void CPlayer::Hit(float fDamage)
{
	if (m_info.pBody != nullptr)
	{// ダッシュ時はダメージを受けない
		if (m_info.pBody->GetMotion() == MOTION_DASH)
		{
			return;
		}
	}

	if (m_info.state == STATE_NORMAL)
	{// 通常状態ならダメージを受ける
		// ダメージサウンド
		Sound::Play(CSound::LABEL_SE_DAMAGE);

		// 体力を減らす
		m_info.nLife -= (int)fDamage;

		if (m_info.nLife <= 0)
		{// 死亡判定
			m_info.nLife = 0;

			Death();
		}
		else
		{// ダメージ状態にする
			m_info.state = STATE_DAMAGE;

			// ダメージの画面揺れ
			Manager::GetCamera()->SetQuake(0.03f, 10);

			if (m_info.pBody != nullptr)
			{// 体を赤くする
				m_info.pBody->SetAllCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}

			// ブラーイベントの生成
			CBlurEvent::Create(0.2f, 0.5f, 10.0f);
		}
	}
}

//=====================================================
// モーション設定
//=====================================================
void CPlayer::SetMotion(E_MOTION motion)
{
	if (m_info.pBody == nullptr)
	{
		return;
	}

	if (m_info.pBody->GetMotion() != motion)
	{
		// モーション設定
		m_info.pBody->SetMotion(motion);
	}
}

//=====================================================
// 死亡処理
//=====================================================
void CPlayer::Death(void)
{
	CFade *pFade = CFade::GetInstance();

	if (pFade != nullptr)
	{
		pFade->SetFade(MODE_DEATH);
	}

	Uninit();
}

//=====================================================
// 描画処理
//=====================================================
void CPlayer::Draw(void)
{
	if (m_info.pBody != nullptr)
	{
		m_info.pBody->SetMatrix();
	}

#ifdef _DEBUG
	CDebugProc::GetInstance()->Print("\nプレイヤーの位置：[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CDebugProc::GetInstance()->Print("\nプレイヤー体力[%d]", m_info.nLife);
	CDebugProc::GetInstance()->Print("\n攻撃[%d]", m_info.bAttack);
#else
	CDebugProc::GetInstance()->Print("\n");
	CDebugProc::GetInstance()->Print("//----------------------------\n");
	CDebugProc::GetInstance()->Print("// プレイヤー基本操作\n");
	CDebugProc::GetInstance()->Print("//----------------------------\n");
	CDebugProc::GetInstance()->Print("[A D]移動\n");
	CDebugProc::GetInstance()->Print("[LMB]攻撃\n");
	CDebugProc::GetInstance()->Print("[RMB]弾パリィ\n");
	CDebugProc::GetInstance()->Print("[SPACE]ジャンプ\n");
	CDebugProc::GetInstance()->Print("\n");
#endif
}

//=====================================================
// 生成処理
//=====================================================
CPlayer *CPlayer::Create(void)
{
	if (s_pPlayer == nullptr)
	{
		s_pPlayer = new CPlayer;

		if (s_pPlayer != nullptr)
		{
			s_pPlayer->Init();
		}
	}

	return s_pPlayer;
}

//=====================================================
// 情報読込
//=====================================================
void CPlayer::Load(void)
{
	// 変数宣言
	char cTemp[256];
	int nCntAttack = 0;

	// ファイルから読み込む
	FILE *pFile = fopen(PARAM_PATH, "r");

	if (pFile != nullptr)
	{// ファイルが開けた場合
		while (true)
		{
			// 文字読み込み
			fscanf(pFile, "%s", &cTemp[0]);

			// パラメーター読込
			LoadParam(pFile,&cTemp[0]);

			if (strcmp(cTemp, "NUM_ATTACK") == 0)
			{// 攻撃判定読込開始
				// 攻撃判定数読込
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_info.nNumAttack);
				
				if (m_info.pAttackInfo == nullptr)
				{// 判定情報の生成
					m_info.pAttackInfo = new S_AttackInfo[m_info.nNumAttack];

					for (int i = 0; i < m_info.nNumAttack; i++)
					{// 情報のクリア
						ZeroMemory(&m_info.pAttackInfo[i], sizeof(S_AttackInfo));

						// ヒットストップ情報の初期化
						m_info.pAttackInfo[i].fScaleHitStop = 1.0f;
						m_info.pAttackInfo[i].fTimeHitStop = 0.0f;
					}
				}
				else
				{
					break;
				}

				if (m_info.pAttackInfo == nullptr)
				{// 生成できなかった場合
					break;
				}

				while (true)
				{
					// 文字読み込み
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "ATTACKSET") == 0)
					{// パラメーター読込開始
						while (true)
						{
							// 文字読み込み
							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "MOTION") == 0)
							{// モーションの種類
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_info.pAttackInfo[nCntAttack].nIdxMotion);
							}

							if (strcmp(cTemp, "POS") == 0)
							{//位置読み込み
								fscanf(pFile, "%s", &cTemp[0]);

								for (int nCntPos = 0; nCntPos < 3; nCntPos++)
								{
									fscanf(pFile, "%f", &m_info.pAttackInfo[nCntAttack].pos[nCntPos]);
								}
							}

							if (strcmp(cTemp, "KEY") == 0)
							{// キーの番号
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_info.pAttackInfo[nCntAttack].nKey);
							}

							if (strcmp(cTemp, "FRAME") == 0)
							{// フレーム番号
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_info.pAttackInfo[nCntAttack].nFrame);
							}

							if (strcmp(cTemp, "RADIUS") == 0)
							{// 半径
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%f", &m_info.pAttackInfo[nCntAttack].fRadius);
							}

							if (strcmp(cTemp, "SCALE_HITSTOP") == 0)
							{// ヒットストップのタイムスケール
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%f", &m_info.pAttackInfo[nCntAttack].fScaleHitStop);
							}

							if (strcmp(cTemp, "TIME_HITSTOP") == 0)
							{// ヒットストップ継続時間
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%f", &m_info.pAttackInfo[nCntAttack].fTimeHitStop);
							}

							if (strcmp(cTemp, "END_ATTACKSET") == 0)
							{// パラメーター読込終了
								nCntAttack++;

								break;
							}
						}
					}

					if (m_info.nNumAttack <= nCntAttack)
					{
						break;
					}
				}
			}

			if (strcmp(cTemp, "PARRYSET") == 0)
			{// パリィ判定読込開始
				while (true)
				{
					// 文字読み込み
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "POS") == 0)
					{//位置読み込み
						fscanf(pFile, "%s", &cTemp[0]);

						for (int i = 0; i < 3; i++)
						{
							fscanf(pFile, "%f", &m_info.offsetParry[i]);
						}
					}

					if (strcmp(cTemp, "RADIUS") == 0)
					{// 半径
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%f", &m_info.fRadiusParry);
					}

					if (strcmp(cTemp, "TIME") == 0)
					{// パリィ継続時間
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%d", &m_info.nTimeParry);
					}
					
					if (strcmp(cTemp, "END_PARRYSET") == 0)
					{// パラメーター読込終了
						nCntAttack++;

						break;
					}
				}
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// 終了条件
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
}

//=====================================================
// パラメーター読込
//=====================================================
void CPlayer::LoadParam(FILE *pFile, char *pTemp)
{
	if (strcmp(pTemp, "BODY") == 0)
	{// 見た目の読み込み
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%s", pTemp);

		if (m_info.pBody == nullptr)
		{// 体の生成
			m_info.pBody = CMotion::Create(pTemp);

			if (m_info.pBody != nullptr)
			{
				m_info.pBody->EnableShadow(true);
			}
		}
	}

	if (strcmp(pTemp, "LIFE") == 0)
	{// 体力
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%d", &m_param.nInitialLife);

		m_info.nLife = m_param.nInitialLife;
	}

	if (strcmp(pTemp, "SPEED_MOVE") == 0)
	{// 通常移速度
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fSpeedMove);
	}

	if (strcmp(pTemp, "GRAVITY") == 0)
	{// 重力
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fGravity);
	}

	if (strcmp(pTemp, "MOVE_FACT") == 0)
	{// 移動減衰係数
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fFactMove);
	}

	if (strcmp(pTemp, "ROLL_FACT") == 0)
	{// 移動減衰係数
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fFactRoll);
	}

	if (strcmp(pTemp, "TIME_DASH") == 0)
	{// ダッシュのクールタイム
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%d", &m_param.nTimeDash);
	}

	if (strcmp(pTemp, "SPEED_DASH") == 0)
	{// ダッシュの速度
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fSpeedDash);
	}

	if (strcmp(pTemp, "JUMP_POW") == 0)
	{// ジャンプ力
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fPowJump);
	}

	if (strcmp(pTemp, "ATTACKJUMP_POW") == 0)
	{// ジャンプ力
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fPowAttackJump);
	}

	if (strcmp(pTemp, "TIME_DAMAGE") == 0)
	{// 無敵時間
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%d", &m_param.nTimeDamage);
	}
}