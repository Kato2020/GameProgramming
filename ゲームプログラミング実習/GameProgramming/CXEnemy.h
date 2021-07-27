#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy :public CXCharacter{
public:
	//�R���C�_�̐錾
	CCollider mColSphereBody;  //��
	CCollider mColSphereHead;  //��
	CCollider mColSphereSword; //��
	//�f�t�H���g�R���X�g���N�^
	CXEnemy();
	//��x�������s
	void Init(CModelX *model);
	//�Փˏ���
	void Collision(CCollider *m, CCollider *o);
};

#endif