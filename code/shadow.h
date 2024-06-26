//*****************************************************
//
// �e�̏���[shadow.h]
// Author:���R����
//
//*****************************************************
#ifndef _SHADOW_H_	// ��d�C���N���[�h�h�~
#define _SHADOW_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "polygon3D.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CShadow : public CPolygon3D
{
public:
	CShadow(int nPriority = 6);	// �R���X�g���N�^
	~CShadow();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	// �ÓI�����o�֐�
	static CShadow *Create(D3DXVECTOR3 pos,float width,float height);	// ��������

private:
};

#endif
