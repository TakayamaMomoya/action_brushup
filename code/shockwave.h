//*****************************************************
//
// ���[�_�[�̏���[rader.h]
// Author:���R����
//
//*****************************************************

#ifndef _SHOCKWAVE_H_
#define _SHOCKWAVE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "meshcylinder.h"

//*****************************************************
// �N���X��`
//*****************************************************
class CShockWave : public CMeshCylinder
{
public:
	CShockWave(void);	// �R���X�g���N�^
	~CShockWave();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CShockWave *Create(void);

private:
	void Wave(void);
};
#endif