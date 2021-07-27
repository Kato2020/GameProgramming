#include "CXEnemy.h"
#include "CCollider.h"

//コライダの初期化
CXEnemy::CXEnemy()
:mColSphereBody(this, nullptr, CVector(), 0.5f)
, mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
, mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{}

void CXEnemy::Init(CModelX *model){
	CXCharacter::Init(model);
	//合成行列の設定
	//体
	mColSphereBody.mpMatrix = &mpCombinedMatrix[8];
	//頭
	mColSphereHead.mpMatrix = &mpCombinedMatrix[11];
	//剣
	mColSphereSword.mpMatrix = &mpCombinedMatrix[21];
}
//課題26
//衝突処理
void CXEnemy::Collision(CCollider *m, CCollider *o){
	//自身のコライダタイプの判定
	switch (m->mType){
		//球コライダの時
	case CCollider::ESPHERE:
		//相手のコライダが球コライダの時
		if (o->mType == CCollider::ESPHERE){
			//相手のコライダの親がプレイヤーの時
			if (o->mpParent->mTag == EPLAYER){
				//相手のコライダが剣先であれば
				if (o->mTag == CCollider::ESWORD){
					//衝突しているか判定
					if (CCollider::Collision(m, o)){
						//倒れるアニメーションに変更
						ChangeAnimation(11, false, 30);
					}
				}
			}
		}
		break;
	}
}