//*****************************************************
//
// ���b�V���V�����_�[�̏���[meshcylinder.h]
// Author:���R����
//
//*****************************************************
#ifndef _MESHCYLINDER_H_	// ��d�C���N���[�h�h�~
#define _MESHCYLINDER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace MeshCylinder
{
const float  MESH_RADIUS = 100.0f;	// ���a
const int MESH_U = 16;	// ���̕�����
const int MESH_V = 1;	// �c�̕�����
const int SPLIT_TEX_U = 3;	// ���̃e�N�X�`��������
const int SPLIT_TEX_V = 1;	// �c�̃e�N�X�`��������
const float MESH_HEIGHT = 50.0f;	// ���b�V���̍���
}

//*****************************************************
// �N���X��`
//*****************************************************
class CMeshCylinder : public CObject
{
public:
	CMeshCylinder(int nPriority = 2);	// �R���X�g���N�^
	~CMeshCylinder();	// �f�X�g���N�^

	// �\���̒�`
	struct S_MeshCylinder
	{// ���g�̏��
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
		D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
		int nNumIdx;	//�C���f�b�N�X��
		int nNumVtx;	//���_��
		float fRadius;	// ���a
		float fHeight;	// ����
		int nMeshU;	// ���̕�����
		int nMeshV;	// �c�̕�����
		int nTexU;	// �e�N�X�`���̉��̕�����
		int nTexV;	// �e�N�X�`���̏c�̕�����
		// �R���X�g���N�^
		S_MeshCylinder() : pos{}, rot{}, mtxWorld{}, nNumIdx(0), nNumVtx(0),fRadius(0.0f), fHeight(0.0f), nMeshU(0), nMeshV(0), nTexU(0), nTexV(0) {}
	};

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void SetVtx(void);	// ���_�̐ݒ�

	// �ϐ��擾�E�ݒ�֐�
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }	// ���_�o�b�t�@
	void SetPosition(D3DXVECTOR3 pos) { m_meshCylinder.pos = pos; }	// �ʒu
	D3DXVECTOR3 GetPosition(void) { return m_meshCylinder.pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_meshCylinder.rot = rot; }	// ����
	D3DXVECTOR3 GetRotation(void) { return m_meshCylinder.rot; }
	int GetNumVtx(void) { return m_meshCylinder.nNumVtx; }	// ���_��
	void SetRadius(float fRadius) { m_meshCylinder.fRadius = fRadius; }	// ���a
	void SetHeight(float fHeight) { m_meshCylinder.fHeight = fHeight; }	// ����
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }	// �e�N�X�`���ԍ�
	void SetNumMeshU(int nNumMesh) { m_meshCylinder.nMeshU = nNumMesh; }	// ���b�V���̉��̕�����
	void SetNumMeshV(int nNumMesh) { m_meshCylinder.nMeshV = nNumMesh; }	// ���b�V���̏c�̕�����
	S_MeshCylinder *GetMeshCylinder(void) { return &m_meshCylinder; }	// ���g�̏��̍\����
	void SetCol(D3DXCOLOR col);	// �F
	D3DXCOLOR GetCol(void) { return m_col; }
	void SetMtx(D3DXMATRIX mtx) { m_meshCylinder.mtxWorld = mtx; }	// �}�g���b�N�X

	// �ÓI�����o�֐�
	static CMeshCylinder *Create	// ��������
	(
		int nMeshU = MeshCylinder::MESH_U,
		int nMeshV = MeshCylinder::MESH_V,
		int nTexU = MeshCylinder::SPLIT_TEX_U,
		int nTexV = MeshCylinder::SPLIT_TEX_V
	);

private:
	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	S_MeshCylinder m_meshCylinder;	//�\���̂̏��
	D3DXCOLOR m_col;	// �F
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
};

#endif