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

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

private:
	// �񋓌^��`
	enum MOTION
	{// ���[�V����
		MOTION_NEUTRAL = 0,	// �ҋ@���[�V����
		MOTION_SHOT,	// �ˌ����[�V����
		MOTION_MAX
	};

	// �����o�֐�
	void ManageAttack(void);	// �U���̊Ǘ�
};

#endif
