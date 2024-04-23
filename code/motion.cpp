//*****************************************************
//
// ���[�V�����̏���[motion.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "motion.h"
#include "model.h"
#include <stdio.h>
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "particle.h"
#include "sound.h"
#include "afterimage.h"
#include "universal.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MAX_STRING	(256)	// ������̍ő吔

//=====================================================
// �R���X�g���N�^
//=====================================================
CMotion::CMotion(int nPriority) : CObject(nPriority)
{
	ZeroMemory(&m_aMotionInfo, sizeof(m_aMotionInfo));
	ZeroMemory(&m_aKeyOld, sizeof(m_aKeyOld));
	ZeroMemory(&m_apParts[0], sizeof(m_apParts));
	m_bLoopMotion = false;
	m_motionType = 0;
	m_motionTypeOld = 0;
	m_nCounterMotion = 0;
	m_nKey = 0;
	m_nNumKey = 0;
	m_nNumMotion = 0;
	m_nNumParts = 0;
	m_bFinish = false;
	m_bShadow = false;
	m_pos = { 0.0f,0.0f,0.0f };
	m_posOld = { 0.0f,0.0f,0.0f };
	m_posShadow = { 0.0f,0.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CMotion::~CMotion()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CMotion::Init(void)
{
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CMotion::Uninit(void)
{
	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{// �p�[�e�B�N�����̔j��
		if (m_aMotionInfo[nCntMotion].pParticle != nullptr)
		{
			delete m_aMotionInfo[nCntMotion].pParticle;
			m_aMotionInfo[nCntMotion].pParticle = nullptr;
		}
	}

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CMotion::Update(void)
{
	if (m_apParts[0] == nullptr)
	{
		return;
	}

	// ���݂̈ʒu��ۑ�
	m_posOld = m_pos;

	//�ϐ��錾
	int nNextKey;

	// �p�[�c�̃g�����X�t�H�[��
	D3DXVECTOR3 pos, rot;

	if (m_aMotionInfo[m_motionType].pParticle != nullptr)
	{
		for (int nCntParticle = 0; nCntParticle < m_aMotionInfo[m_motionType].nNumParticle; nCntParticle++)
		{// �S�Ẵp�[�e�B�N�����m�F
			if (m_nKey == m_aMotionInfo[m_motionType].pParticle[nCntParticle].nKey &&
				m_nCounterMotion == m_aMotionInfo[m_motionType].pParticle[nCntParticle].nFrame)
			{// �p�[�e�B�N������
				// �e�p�[�c�̈ʒu�擾
				D3DXMATRIX *pMtx = m_apParts[m_aMotionInfo[m_motionType].pParticle[nCntParticle].nIdxParent]->m_pParts->GetMatrix();
				pos = D3DXVECTOR3(pMtx->_41, pMtx->_42, pMtx->_43) + m_aMotionInfo[m_motionType].pParticle[nCntParticle].offset;

				CParticle::Create(pos, (CParticle::TYPE)m_aMotionInfo[m_motionType].pParticle[nCntParticle].nType);
			}
		}
	}

	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		if (m_nKey >= m_aMotionInfo[m_motionType].nNumKey - 1)
		{
			break;
		}

		// �p�[�c�̃g�����X�t�H�[���擾
		pos = m_apParts[nCntParts]->m_pParts->GetPosOrg();
		rot = m_apParts[nCntParts]->m_pParts->GetRot();

		if (m_nKey < m_aMotionInfo[m_motionType].nNumKey - 1)
		{
			nNextKey = m_nKey + 1;
		}
		else
		{
			nNextKey = m_aMotionInfo[m_motionType].nNumKey - 1;
		}

		//�O��Ǝ��̃L�[�̍����擾
		float DiffPosX = m_aMotionInfo[m_motionType].aKeyInfo[nNextKey].aKey[nCntParts].fPosX -
			m_aKeyOld[nCntParts].fPosX;

		float DiffPosY = m_aMotionInfo[m_motionType].aKeyInfo[nNextKey].aKey[nCntParts].fPosY -
			m_aKeyOld[nCntParts].fPosY;

		float DiffPosZ = m_aMotionInfo[m_motionType].aKeyInfo[nNextKey].aKey[nCntParts].fPosZ -
			m_aKeyOld[nCntParts].fPosZ;

		float DiffRotX = m_aMotionInfo[m_motionType].aKeyInfo[nNextKey].aKey[nCntParts].fRotX -
			m_aKeyOld[nCntParts].fRotX;

		float DiffRotY = m_aMotionInfo[m_motionType].aKeyInfo[nNextKey].aKey[nCntParts].fRotY -
			m_aKeyOld[nCntParts].fRotY;

		float DiffRotZ = m_aMotionInfo[m_motionType].aKeyInfo[nNextKey].aKey[nCntParts].fRotZ -
			m_aKeyOld[nCntParts].fRotZ;

		universal::LimitRot(&DiffRotX);
		universal::LimitRot(&DiffRotY);
		universal::LimitRot(&DiffRotZ);

		//�ړI�̒l=======================================================================================================
		float DestPosX = pos.x + m_aKeyOld[nCntParts].fPosX +
			DiffPosX * (float)(1.0f / (float)m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame) * m_nCounterMotion;

		float DestPosY = pos.y + m_aKeyOld[nCntParts].fPosY +
			DiffPosY * (float)(1.0f / (float)m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame) * m_nCounterMotion;

		float DestPosZ = pos.z + m_aKeyOld[nCntParts].fPosZ +
			DiffPosZ * (float)(1.0f / (float)m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame) * m_nCounterMotion;

		float DestRotX = m_aKeyOld[nCntParts].fRotX +
			DiffRotX * (float)(1.0f / (float)m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame) * m_nCounterMotion;

		float DestRotY = m_aKeyOld[nCntParts].fRotY +
			DiffRotY * (float)(1.0f / (float)m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame) * m_nCounterMotion;

		float DestRotZ = m_aKeyOld[nCntParts].fRotZ +
			DiffRotZ * (float)(1.0f / (float)m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame) * m_nCounterMotion;

		//�p�[�c�̌����E�ʒu�ݒ�
		m_apParts[nCntParts]->m_pParts->SetPosition(D3DXVECTOR3(DestPosX, DestPosY, DestPosZ));

		universal::LimitRot(&DestRotX);
		universal::LimitRot(&DestRotY);
		universal::LimitRot(&DestRotZ);

		rot = D3DXVECTOR3(DestRotX, DestRotY, DestRotZ);

		m_apParts[nCntParts]->m_pParts->SetRot(rot);
	}

	m_nCounterMotion++;

	if (m_nKey >= m_aMotionInfo[m_motionType].nNumKey - 1)
	{// ���[�V�������I�����Ă�����
		m_motionTypeOld = m_motionType;

		// �I��������Ԃɂ���
		m_bFinish = true;

		if (m_aMotionInfo[m_motionType].bLoop)
		{// ���[�v������͍̂Đݒ�
			SetMotion(m_motionType);
		}
	}

	if (m_nCounterMotion > m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame)
	{//�L�[�̃t���[�����ɒB������
		if (m_nKey < m_aMotionInfo[m_motionType].nNumKey)
		{
			m_nKey++;

			m_nCounterMotion = 0;

			SetKeyOld();
		}
	}
}

//=====================================================
// ���[�V�����ݒ�
//=====================================================
void CMotion::SetMotion(int nMotionType)
{
	// �I����Ԃ̉���
	m_bFinish = false;

	// �I�����郂�[�V������ۑ�
	m_motionTypeOld = m_motionType;
	SetKeyOld();

	// ���[�V�������̐ݒ�
	m_motionType = nMotionType;
	m_nKey = 0;
	m_nCounterMotion = 0;
}

//=====================================================
// �I������L�[�̏��ۑ�
//=====================================================
void CMotion::SetKeyOld(void)
{
	for (int nCntPart = 0;nCntPart < m_nNumParts;nCntPart++)
	{
		m_aKeyOld[nCntPart].fPosX = m_apParts[nCntPart]->m_pParts->GetPosition().x - m_apParts[nCntPart]->m_pParts->GetPosOrg().x;
		m_aKeyOld[nCntPart].fPosY = m_apParts[nCntPart]->m_pParts->GetPosition().y - m_apParts[nCntPart]->m_pParts->GetPosOrg().y;
		m_aKeyOld[nCntPart].fPosZ = m_apParts[nCntPart]->m_pParts->GetPosition().z - m_apParts[nCntPart]->m_pParts->GetPosOrg().z;

		m_aKeyOld[nCntPart].fRotX = m_apParts[nCntPart]->m_pParts->GetRot().x;
		m_aKeyOld[nCntPart].fRotY = m_apParts[nCntPart]->m_pParts->GetRot().y;
		m_aKeyOld[nCntPart].fRotZ = m_apParts[nCntPart]->m_pParts->GetRot().z;
	}
}

//=====================================================
// �|�[�Y�̏����ݒ�
//=====================================================
void CMotion::InitPose(int nMotion)
{
	for (int i = 0; i < m_aMotionInfo[nMotion].nNumKey;i++)
	{
		for (int nCntPart = 0; nCntPart < m_nNumParts; nCntPart++)
		{
			m_aKeyOld[nCntPart] = m_aMotionInfo[nMotion].aKeyInfo[i].aKey[nCntPart];
		}
	}
}

//=====================================================
// �����̃}�g���b�N�X�̐ݒ�
//=====================================================
void CMotion::SetMatrix(void)
{
	//�ϐ��錾
	D3DXMATRIX mtxRotModel, mtxTransModel;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRotModel,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTransModel,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//=====================================================
// �}�g���b�N�X���������킹�鏈��
//=====================================================
void CMotion::MultiplyMtx(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	D3DXMATRIX mtxRotModel, mtxTransModel;
	D3DXMATRIX *pMtxParent;
	D3DXMATRIX *pMtx;

	D3DXMATRIX mtxShadow;
	D3DLIGHT9 light;
	D3DXVECTOR4 posLight;
	D3DXVECTOR3 normal;
	D3DXPLANE plane;

	// ���C�g�̈ʒu�ݒ�
	pDevice->GetLight(2, &light);
	posLight = { -light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f };

	// ���ʏ��̐���
	normal = { 0.0f,1.0f,0.0f };
	D3DXPlaneFromPointNormal(&plane, &m_posShadow, &normal);

	for (int nCntParts = 0;nCntParts < m_nNumParts;nCntParts++)
	{
		// �}�g���b�N�X�̎擾
		pMtx = m_apParts[nCntParts]->m_pParts->GetMatrix();

		//���[���h�}�g���b�N�X������
		D3DXMatrixIdentity(pMtx);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel,
			m_apParts[nCntParts]->m_pParts->GetRot().y, m_apParts[nCntParts]->m_pParts->GetRot().x, m_apParts[nCntParts]->m_pParts->GetRot().z);
		D3DXMatrixMultiply(pMtx, pMtx, &mtxRotModel);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel,
			m_apParts[nCntParts]->m_pParts->GetPosition().x, m_apParts[nCntParts]->m_pParts->GetPosition().y, m_apParts[nCntParts]->m_pParts->GetPosition().z);
		D3DXMatrixMultiply(pMtx, pMtx, &mtxTransModel);
		
		if (m_apParts[nCntParts]->nIdxParent != -1)
		{//�e�p�[�c������ꍇ
			// �e�}�g���b�N�X�̎擾
			pMtxParent = m_apParts[m_apParts[nCntParts]->nIdxParent]->m_pParts->GetMatrix();
		}
		else
		{
			pMtxParent = &m_mtxWorld;
		}

		//�e�p�[�c�ƃp�[�c�̃��[���h�}�g���b�N�X���������킹��
		D3DXMatrixMultiply(pMtx, pMtx, pMtxParent);

		if (m_bShadow)
		{
			// �V���h�E�}�g���b�N�X������
			D3DXMatrixIdentity(&mtxShadow);

			// �V���h�E�}�g���b�N�X�̍쐬
			D3DXMatrixShadow(&mtxShadow, &posLight, &plane);
			D3DXMatrixMultiply(&mtxShadow, pMtx, &mtxShadow);

			// �V���h�E�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

			m_apParts[nCntParts]->m_pParts->DrawShadow();
		}

		//���[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, pMtx);

		m_apParts[nCntParts]->m_pParts->Draw();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CMotion::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// �}�g���b�N�X���������킹�鏈��
	MultiplyMtx();
}

//=====================================================
// �Ǎ�����
//=====================================================
void CMotion::Load(char *pPath)
{
	//�ϐ��錾
	char cTemp[MAX_STRING];
	int nCntMotion = 0;
	int nCntModel = 0;

	//�t�@�C������ǂݍ���
	FILE *pFile = fopen(pPath, "r");

	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ
		while(true)
		{
			//�����ǂݍ���
			fscanf(pFile, "%s", &cTemp[0]);

			//�t�@�C�����ǂݍ���=========================================
			if (strcmp(cTemp, "NUM_MODEL") == 0)
			{
				//"="�ǂݍ���
				fscanf(pFile, "%s", &cTemp[0]);

				//���f�����ǂݍ���
				fscanf(pFile, "%d", &m_nNumParts);

				for (int nCntFile = 0; nCntFile < m_nNumParts;)
				{//�t�@�C�����ǂݍ���

					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "MODEL_FILENAME") == 0)
					{//�t�@�C�����ǂݍ���
						fscanf(pFile, "%s", &cTemp[0]);

						char aPath[MAX_STRING];

						// ���f���p�X�Ǎ�
						fscanf(pFile, "%s", &aPath[0]);

						m_apParts[nCntFile] = new Parts;

						m_apParts[nCntFile]->m_pParts = CParts::Create();

						int nIdx = CModel::Load(&aPath[0]);

						// ���f���Ǎ�
						m_apParts[nCntFile]->m_pParts->SetIdxModel(nIdx);
						m_apParts[nCntFile]->m_pParts->BindModel(m_apParts[nCntFile]->m_pParts->GetIdxModel());

						nCntFile++;
					}
				}
			}
			//===========================================================

			//�L�����N�^�[�ݒ�===========================================
			if (strcmp(cTemp, "CHARACTERSET") == 0)
			{//�L�����N�^�[�X�^�[�g
				nCntModel = 0;

				while (strcmp(cTemp, "END_CHARACTERSET") != 0)
				{//�I���܂ŃL�����N�^�[�ݒ�
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "PARTSSET") == 0)
					{//�p�[�c�X�^�[�g
						while (strcmp(cTemp, "END_PARTSSET") != 0)
						{//�I���܂Ńp�[�c�ݒ�
							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "INDEX") == 0)
							{//�ԍ��ǂݍ���
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_apParts[nCntModel]->nIdx);
							}

							if (strcmp(cTemp, "PARENT") == 0)
							{//�e�ԍ��ǂݍ���
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_apParts[nCntModel]->nIdxParent);
							}

							if (strcmp(cTemp, "POS") == 0)
							{//�ʒu�ǂݍ���
								D3DXVECTOR3 pos;

								fscanf(pFile, "%s", &cTemp[0]);

								for (int nCntPos = 0; nCntPos < 3; nCntPos++)
								{
									fscanf(pFile, "%f", &pos[nCntPos]);
								}

								m_apParts[nCntModel]->m_pParts->SetPosition(pos);

								m_apParts[nCntModel]->m_pParts->SetPosOrg(pos);
							}

							if (strcmp(cTemp, "ROT") == 0)
							{//�����ǂݍ���
								D3DXVECTOR3 rot;

								fscanf(pFile, "%s", &cTemp[0]);

								for (int nCntRot = 0; nCntRot < 3; nCntRot++)
								{
									fscanf(pFile, "%f", &rot[nCntRot]);
								}

								m_apParts[nCntModel]->m_pParts->SetRot(rot);
							}

						}//END_PART

						nCntModel++;
					}
				}//END_CHAR
			}
			//===========================================================

			//�ϐ��錾
			int nCntKey = 0;
			int nCntPart = 0;
			int nCntParticle = 0;

			//���[�V�����ݒ�===========================================
			if (strcmp(cTemp, "MOTIONSET") == 0)
			{//���[�V�����X�^�[�g
				while (strcmp(cTemp, "END_MOTIONSET") != 0)
				{//�I���܂ŃL�����N�^�[�ݒ�

					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "LOOP") == 0)
					{//���[�v���f
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%d", (int*)&m_aMotionInfo[nCntMotion].bLoop);
					}

					if (strcmp(cTemp, "NUM_KEY") == 0)
					{//�L�[�����f
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].nNumKey);
					}

					if (strcmp(cTemp, "NUM_PARTICLE") == 0)
					{//�p�[�e�B�N�������f
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].nNumParticle);

						if (m_aMotionInfo[m_nNumMotion].nNumParticle != 0)
						{
							// �p�[�e�B�N�����𐶐�
							m_aMotionInfo[m_nNumMotion].pParticle = new PARTICLE_INFO[m_aMotionInfo[m_nNumMotion].nNumParticle];

							// �p�[�e�B�N����񏉊���
							ZeroMemory(m_aMotionInfo[m_nNumMotion].pParticle, sizeof(PARTICLE_INFO) * m_aMotionInfo[m_nNumMotion].nNumParticle);
						}
					}

					if (strcmp(cTemp, "PARTICLESET") == 0 && m_aMotionInfo[m_nNumMotion].pParticle != 0)
					{// �p�[�e�B�N�����ݒ�
						while (strcmp(cTemp, "END_PARTICLESET") != 0)
						{//�I���܂Ńp�[�e�B�N���ݒ�
							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "KEY") == 0)
							{// �Đ��L�[�擾
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].nKey);
							}

							if (strcmp(cTemp, "FRAME") == 0)
							{// �Đ��t���[���擾
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].nFrame);
							}

							if (strcmp(cTemp, "TYPE") == 0)
							{// ��ގ擾
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].nType);
							}

							if (strcmp(cTemp, "POS") == 0)
							{//�ʒu�ǂݍ���
								D3DXVECTOR3 pos;

								fscanf(pFile, "%s", &cTemp[0]);

								for (int nCntPos = 0; nCntPos < 3; nCntPos++)
								{
									fscanf(pFile, "%f", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].offset[nCntPos]);
								}
							}

							if (strcmp(cTemp, "PARENT") == 0)
							{// �e�p�[�c�ԍ��擾
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].nIdxParent);
							}
						}

						nCntParticle++;
					}

					//if (strcmp(cTemp, "NUM_COLLISION") == 0)
					//{// �����蔻�萔���f
					//	fscanf(pFile, "%s", &cTemp[0]);

					//	fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].nNumCollision);

					//	if (m_aMotionInfo[m_nNumMotion].nNumCollision != 0)
					//	{
					//		// �����蔻����𐶐�
					//		m_aMotionInfo[m_nNumMotion].pCollision = new COLLISION_INFO[m_aMotionInfo[m_nNumMotion].nNumCollision];

					//		// �����蔻���񏉊���
					//		ZeroMemory(m_aMotionInfo[m_nNumMotion].pCollision, sizeof(COLLISION_INFO) * m_aMotionInfo[m_nNumMotion].nNumCollision);
					//	}
					//}

					//if (strcmp(cTemp, "COLLISIONSET") == 0 && m_aMotionInfo[m_nNumMotion].pCollision != 0)
					//{// �����蔻����ݒ�
					//	while (strcmp(cTemp, "END_COLLISIONSET") != 0)
					//	{//�I���܂œ����蔻��ݒ�
					//		fscanf(pFile, "%s", &cTemp[0]);

					//		if (strcmp(cTemp, "KEY") == 0)
					//		{// �Đ��L�[�擾
					//			fscanf(pFile, "%s", &cTemp[0]);

					//			fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].nKey);
					//		}

					//		if (strcmp(cTemp, "FRAME") == 0)
					//		{// �Đ��t���[���擾
					//			fscanf(pFile, "%s", &cTemp[0]);

					//			fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].nFrame);
					//		}

					//		if (strcmp(cTemp, "POS") == 0)
					//		{//�ʒu�ǂݍ���
					//			D3DXVECTOR3 pos;

					//			fscanf(pFile, "%s", &cTemp[0]);

					//			for (int nCntPos = 0; nCntPos < 3; nCntPos++)
					//			{
					//				fscanf(pFile, "%f", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].offset[nCntPos]);
					//			}
					//		}

					//		if (strcmp(cTemp, "PARENT") == 0)
					//		{// �e�p�[�c�ԍ��擾
					//			fscanf(pFile, "%s", &cTemp[0]);

					//			fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].nIdxParent);
					//		}
					//	}

					//	nCntParticle++;
					//}

					if (strcmp(cTemp, "KEYSET") == 0)
					{//�L�[�X�^�[�g
						while (strcmp(cTemp, "END_KEYSET") != 0)
						{//�I���܂ŃL�[�ݒ�

							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "FRAME") == 0)
							{//�t���[�����擾
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
							}

							if (strcmp(cTemp, "KEY") == 0)
							{//�t���[�����擾
								while (strcmp(cTemp, "END_KEY") != 0)
								{//�I���܂ŃL�[�ݒ�
									fscanf(pFile, "%s", &cTemp[0]);

									if (strcmp(cTemp, "POS") == 0)
									{//�ʒu�擾
										fscanf(pFile, "%s", &cTemp[0]);

										fscanf(pFile, "%f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPart].fPosX);
										fscanf(pFile, "%f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPart].fPosY);
										fscanf(pFile, "%f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPart].fPosZ);
									}

									if (strcmp(cTemp, "ROT") == 0)
									{//�����擾
										fscanf(pFile, "%s", &cTemp[0]);

										fscanf(pFile, "%f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPart].fRotX);
										fscanf(pFile, "%f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPart].fRotY);
										fscanf(pFile, "%f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPart].fRotZ);
									}
								}

								nCntPart++;

							}//KEYif
						}//ENDKEYwhile

						nCntKey++;
						nCntPart = 0;
					}
				}//MOTIONwhile

				nCntMotion++;
				m_nNumMotion++;
			}
			//===========================================================

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{
				break;
			}
		}//while��

		fclose(pFile);
	}
	else
	{
	}
}

//=====================================================
// �p�[�c�̍ő唼�a�擾
//=====================================================
float CMotion::GetRadiusMax(void)
{
	float fRadiusMax = 0.0f;
	float fTemp;

	for (int nCntParts = 0;nCntParts < m_nNumParts;nCntParts++)
	{
		if (m_apParts[nCntParts] != nullptr)
		{// �p�[�c�̔��a�擾
			fTemp = m_apParts[nCntParts]->m_pParts->GetRadius();

			if (fTemp > fRadiusMax)
			{// �ő唼�a�ݒ�
				fRadiusMax = fTemp;
			}
		}
	}

	return fRadiusMax;
}

//=====================================================
// �p�[�c�̐�Έʒu�擾
//=====================================================
D3DXVECTOR3 CMotion::GetMtxPos(int nIdx)
{
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

	if (nIdx < 0 && 
		nIdx >= m_nNumParts)
	{// �͈͊O����
		return pos;
	}

	if (m_apParts[nIdx] != nullptr)
	{
		if (m_apParts[nIdx]->m_pParts != nullptr)
		{
			D3DXMATRIX mtx = *m_apParts[nIdx]->m_pParts->GetMatrix();

			pos = 
			{
				mtx._41,
				mtx._42,
				mtx._43,
			};
		}
	}

	return pos;
}

//=====================================================
// �c���̐ݒ�
//=====================================================
void CMotion::SetAfterImage(D3DXCOLOR col, int m_nLife)
{
	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		if (m_apParts[nCntParts] != nullptr)
		{// �c���ݒ�
			D3DXMATRIX *pMtx = m_apParts[nCntParts]->m_pParts->GetMatrix();
			CModel::Model *model = m_apParts[nCntParts]->m_pParts->GetModel();

			CAfterImage::Create(*m_apParts[nCntParts]->m_pParts->GetMatrix(), m_apParts[nCntParts]->m_pParts->GetIdxModel(),col,m_nLife);
		}
	}
}

//=====================================================
// �S�p�[�c�̐F�ݒ�
//=====================================================
void CMotion::SetAllCol(D3DXCOLOR col)
{
	for (int i = 0; i < m_nNumParts; i++)
	{
		if (m_apParts[i] != nullptr)
		{
			if (m_apParts[i]->m_pParts != nullptr)
			{
				m_apParts[i]->m_pParts->SetEmissiveCol(col);
			}
		}
	}
}

//=====================================================
// �S�p�[�c�̐F���Z�b�g
//=====================================================
void CMotion::ResetAllCol(void)
{
	for (int i = 0; i < m_nNumParts; i++)
	{
		if (m_apParts[i] != nullptr)
		{
			if (m_apParts[i]->m_pParts != nullptr)
			{
				m_apParts[i]->m_pParts->ResetColor();
			}
		}
	}
}

//=====================================================
// ��������
//=====================================================
CMotion *CMotion::Create(char *pPath)
{
	CMotion *pCMotion = nullptr;

	if (pCMotion == nullptr)
	{
		// �C���X�^���X����
		pCMotion = new CMotion;

		// �Ǎ�����
		pCMotion->Load(pPath);

		// ����������
		pCMotion->Init();
	}

	return pCMotion;
}