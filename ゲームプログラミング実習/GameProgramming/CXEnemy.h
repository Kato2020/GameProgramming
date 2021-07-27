#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy :public CXCharacter{
public:
	//コライダの宣言
	CCollider mColSphereBody;  //体
	CCollider mColSphereHead;  //頭
	CCollider mColSphereSword; //剣
	//デフォルトコンストラクタ
	CXEnemy();
	//一度だけ実行
	void Init(CModelX *model);
	//衝突処理
	void Collision(CCollider *m, CCollider *o);
};

#endif