//*****************************************************
//
// �^���b�g[enemyTurret.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _ENEMYTURRET_H_
#define _ENEMYTURRET_H_

#include "enemyNormal.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyTurret : public CEnemyNormal
{// �����Ă���G
public:
	CEnemyTurret();	// �R���X�g���N�^
	~CEnemyTurret();	// �f�X�g���N�^

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
