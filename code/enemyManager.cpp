//*****************************************************
//
// 敵マネージャー[enemyManager.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "enemyManager.h"
#include "manager.h"
#include "enemyshot.h"
#include "enemydrone.h"
#include "enemyboss.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const char* FILE_PATH = "data\\MAP\\enemies.txt";	// 配置データのパス
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CEnemyManager *CEnemyManager::s_pEnemyManager = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CEnemyManager::CEnemyManager() : m_pHead(nullptr),m_pTail(nullptr)
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemyManager::~CEnemyManager()
{

}

//=====================================================
// 生成処理
//=====================================================
CEnemyManager *CEnemyManager::Create(void)
{
	if (s_pEnemyManager == nullptr)
	{
		s_pEnemyManager = new CEnemyManager;

		if (s_pEnemyManager != nullptr)
			s_pEnemyManager->Init();
	}

	return s_pEnemyManager;
}

//=====================================================
// 敵の生成処理
//=====================================================
CEnemy *CEnemyManager::CreateEnemy(D3DXVECTOR3 pos, CEnemy::E_TYPE type)
{
	char *apPath[CEnemy::TYPE_MAX] = 
	{
		nullptr,
		"data\\MOTION\\robot00.txt",
		"data\\MOTION\\drone00.txt",
		"data\\MOTION\\robot01.txt",
		"data\\MOTION\\robot00.txt",
	};

	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{// インスタンス生成
		switch (type)
		{
		case CEnemy::TYPE_SHOT:

			pEnemy = new CEnemyShot;

			break;
		case CEnemy::TYPE_DRONE:

			pEnemy = new CEnemyDrone;

			break;
		case CEnemy::TYPE_BOSS:

			pEnemy = CEnemyBoss::Create();

			break;
		default:
			break;
		}

		if (pEnemy != nullptr)
		{
			// モーション読込
			pEnemy->CMotion::Load(apPath[type]);
			pEnemy->SetMotion(0);

			// 位置設定
			pEnemy->SetPosition(pos);

			// 初期化処理
			pEnemy->Init();
		}
	}

	return pEnemy;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemyManager::Init(void)
{
	// 読込処理
	Load();

	return S_OK;
}

//=====================================================
// 読込処理
//=====================================================
void CEnemyManager::Load(void)
{
	char cTemp[256];
	int nCntAttack = 0;

	// ファイルから読み込む
	FILE *pFile = fopen(FILE_PATH, "r");

	if (pFile != nullptr)
	{// ファイルが開けた場合
		while (true)
		{
			// 文字読み込み
			fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "ENEMYSET") == 0)
			{
				CEnemy::E_TYPE type;
				D3DXVECTOR3 pos;

				while (true)
				{
					// 文字読み込み
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "POS") == 0)
					{// 位置
						fscanf(pFile, "%s", &cTemp[0]);

						for (int nCntPos = 0; nCntPos < 3; nCntPos++)
						{
							fscanf(pFile, "%f", &pos[nCntPos]);
						}
					}

					if (strcmp(cTemp, "TYPE") == 0)
					{// 種類
						fscanf(pFile, "%s", &cTemp[0]);
						
						fscanf(pFile, "%d", &type);
					}

					if (strcmp(cTemp, "END_ENEMYSET") == 0)
					{
						CreateEnemy(pos,type);

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
// 終了処理
//=====================================================
void CEnemyManager::Uninit(void)
{
	s_pEnemyManager = nullptr;

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemyManager::Update(void)
{

}

//=====================================================
// 描画処理
//=====================================================
void CEnemyManager::Draw(void)
{

}