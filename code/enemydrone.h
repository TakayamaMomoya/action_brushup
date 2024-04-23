//*****************************************************
//
// �h���[���G�̏���[enemydrone.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _ENEMYDRONE_H_
#define _ENEMYDRONE_H_

#include "enemyNormal.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyDrone : public CEnemyNormal
{
public:
	CEnemyDrone();	// �R���X�g���N�^
	~CEnemyDrone();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	enum MOTION
	{// ���[�V����
		MOTION_NEUTRAL = 0,	// �ҋ@���[�V����
		MOTION_SHOT,	// �ˌ����[�V����
		MOTION_MAX
	};

	void ManageAttack(void);
};

#endif
