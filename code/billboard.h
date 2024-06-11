//*****************************************************
//
// �r���{�[�h�̏���[billboard.h]
// Author:���R����
//
//*****************************************************
#ifndef _BILLBOARD_H_	// ��d�C���N���[�h�h�~
#define _BILLBOARD_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object3D.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CBillboard : public CObject3D
{
public:
	CBillboard(int nPriority = 5);	// �R���X�g���N�^
	~CBillboard();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	// �ÓI�����o�֐�
	static CBillboard *Create(D3DXVECTOR3 pos, float width, float height);

private:
};

#endif