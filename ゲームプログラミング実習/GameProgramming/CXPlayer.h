#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXPlayer:public CXCharacter{
public:
	//コライダの宣言
	CCollider mColSphereBody;  //体
	CCollider mColSphereHead;  //頭
	CCollider mColSphereSword; //剣
	//モーション中か判定
	bool mMotion;
	//デフォルトコンストラクタ
	CXPlayer();
	//一度だけ実行
	void Init(CModelX *model);
	//更新処理
	void Update();
};

#endif