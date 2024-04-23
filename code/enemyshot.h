//*****************************************************
//
// �����Ă���G�̏���[enemyshot.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _ENEMYSHOT_H_
#define _ENEMYSHOT_H_

#include "enemyNormal.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyShot : public CEnemyNormal
{// �����Ă���G
public:
	CEnemyShot();	// �R���X�g���N�^
	~CEnemyShot();	// �f�X�g���N�^

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
