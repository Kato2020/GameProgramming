#ifndef CMODELX_H //インクルードガード
#define CMODELX_H

#define MODEL_FILE "ラグナ.x"//入力ファイル名

//領域開放をマクロ化
#define SAFE_DELETE_ARRAY(a){if(a)delete[]a;a=0;}

//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a)(sizeof(a)/sizeof(a[0]))

#include<vector> //vectorクラスのインクルード(動的配列)
#include"CMatrix.h" //マトリクスクラスのインクルード
class CModelX; //CModelXクラスの宣言


#include "CVector.h"

class CMaterial; //クラスの宣言


/*
CSkinWeights
スキンウェイト
*/
class CSkinWeights{
public:
	char *mpFrameName; //フレーム名
	int mFrameIndex; //フレーム番号
	int mIndexNum; //頂点番号
	int *mpIndex; //頂点番号配列
	float *mpWeight; //頂点ウェイト配列
	CMatrix mOffset; //オフセットマトリクス

	CSkinWeights(CModelX *model);

	~CSkinWeights(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
};

/*
CAnimationKey
アニメーションキークラス
*/
class CAnimationKey{
public:
	//時間
	float mTime;
	//行列
	CMatrix mMatrix;
};

/*
CAnimation
アニメーションクラス
*/
class CAnimation{
public:
	char*mpFrameName;//フレーム名
	int mFrameIndex; //フレーム番号

	CAnimation(CModelX*model);

	~CAnimation(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}

	int mKeyNum;  //キー数(時間数)
	CAnimationKey *mpKey;  //キーの配列
};

/*
CAnimationSet
アニメーションセット
*/
class CAnimationSet{
public:
	//アニメーションセット名
	char *mpName;

	//アニメーション
	std::vector<CAnimation*>mAnimation;

	CAnimationSet(CModelX *model);

	~CAnimationSet(){
		SAFE_DELETE_ARRAY(mpName);
		//アニメーションの削除
		for (int i = 0; i < mAnimation.size(); i++){
			delete mAnimation[i];
		}
	}

	float mTime;    //現在時間
	float mWeight;  //重み
	float mMaxTime; //最大時間
};


//CMeshクラスの定義
class CMesh{
public:
	int mVertexNum; //頂点数
	CVector*mpVertex; //頂点データ
	int mFaceNum; //面数
	int *mpVertexIndex; //面を構成する頂点番号
	int mNormalNum; //法線数
	CVector*mpNormal; //法線データ 
	int mMaterialNum; //マテリアル数
	int mMaterialIndexNum; //マテリアル番号(面数)
	int *mpMaterialIndex; //マテリアル番号
	std::vector<CMaterial*>mMaterial; //マテリアルデータ
	//スキンウェイト
	std::vector<CSkinWeights*>mSkinWeights;
	CVector*mpAnimateVertex; //アニメーション用頂点
	CVector*mpAnimateNormal; //アニメーション用法線
	//テクスチャ座標データ
	float *mpTextureCoords;
	//コンストラクタ
	CMesh()
		:mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(nullptr)
		, mNormalNum(0)
		, mpNormal(nullptr)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(nullptr)
		, mpAnimateVertex(nullptr)
		, mpAnimateNormal(nullptr)
		, mpTextureCoords(nullptr)
	{}
	//デストラクタ
	~CMesh(){
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		//スキンウェイトの削除
		for (int i = 0; i < mSkinWeights.size(); i++){
			delete mSkinWeights[i];
		}
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		SAFE_DELETE_ARRAY(mpTextureCoords);
	}
	//アニメーションの頂点計算を、指定した合成行列を使って計算
	void AnimateVertex(CMatrix*);
	//頂点にアニメーションを適用
	void AnimateVertex(CModelX*model);
	//読み込み処理
	void Init(CModelX*model);
	//描画メソッド
	void Render();
};

//CModelXFrameクラスの定義
class CModelXFrame{
public:
	std::vector<CModelXFrame*>mChild; //子フレームの配列
	CMatrix mTransformMatrix; //変換行列
	char*mpName; //フレーム名前
	int mIndex;  //フレーム番号
	CMesh mMesh; //Meshデータ
	//コンストラクタ
	CModelXFrame(CModelX*model);
	//デストラクタ
	~CModelXFrame(){
		//子フレームを全て開放する
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++){
			delete*itr;
		}
		//名前のエリアを解放する
		SAFE_DELETE_ARRAY(mpName);
	}
	CMatrix mCombinedMatrix; //合成行列
	//合成行列の作成
	void AnimationCombined(CMatrix*parent);

	//描画メソッド
	void Render();
};

/*
CModelX
Xファイル形式の3Dモデルデータをプログラムで認識する
*/
class CModelX{
public:
	char*mpPointer; //読み取り位置
	char mToken[1024]; //取り出した単語の領域
    std::vector<CModelXFrame*>mFrame; //フレームの配列
	//アニメーションセットの配列
	std::vector<CAnimationSet*>mAnimationSet;
	std::vector<CMaterial*>mMaterial; //マテリアルの配列

	CModelX()
		:mpPointer(nullptr)

	{}

	~CModelX(){
		if (mFrame.size() > 0)
		{
			delete mFrame[0];
		}
		for (int i = 0; i < mAnimationSet.size(); i++){
			delete mAnimationSet[i];
		}
		//マテリアルの解放
		for (int i = 0; i < mMaterial.size(); i++){
			delete mMaterial[i];
		}
	}

	//ファイル読み込み
	void Load(char*file);
	//単語の取り出し
	void GetToken();
	//浮動小数点データの取得
	float GetFloatToken();
	//ノードの読み飛ばし
	void SkipNode();
	//整数データの取得
	int GetIntToken();
	//フレーム名に該当するフレームのアドレスを返す
	CModelXFrame*FindFrame(char*name);
	/*
	AnimateFrame
	フレームの変換行列をアニメーションデータで更新する
	*/
	void CModelX::AnimateFrame(){
		//アニメーションで適用されるフレームの
		//変換行列をゼロクリアする
		for (int i = 0; i < mAnimationSet.size(); i++){
			CAnimationSet*anim = mAnimationSet[i];
			//重みが0は読み飛ばす
			if (anim->mWeight == 0)continue;
			//フレーム分(Animation分)繰り返す
			for (int j = 0; j < anim->mAnimation.size(); j++){
				CAnimation*animation = anim->mAnimation[j];
				//該当するフレームの変換行列をゼロクリアする
				memset(&mFrame[animation->mFrameIndex]->mTransformMatrix, 0, sizeof(CMatrix));
			}
		}
		//アニメーションに該当するフレームの変換行列を
		//アニメーションのデータで設定する
		for (int i = 0; i < mAnimationSet.size(); i++){
			CAnimationSet*anim = mAnimationSet[i];
			//重みが0は飛ばす
			if (anim->mWeight == 0)continue;
			//フレーム分(Animation分)繰り返す
			for (int j = 0; j < anim->mAnimation.size(); j++){
				//フレームを取得する
				CAnimation*animation = anim->mAnimation[j];
				CModelXFrame*frame = mFrame[animation->mFrameIndex];
				//キーがない場合は飛ばす
				if (animation->mpKey == 0)continue;
				//時間を取得
				float time = anim->mTime;
				//最初の時間より小さい場合
				if (time < animation->mpKey[0].mTime){
					//変換行列を0コマ目の行列で更新
					frame->mTransformMatrix += animation->mpKey[0].mMatrix*anim->mWeight;
				}
		        //最後の時間より大きい場合
				else if (time >= animation->mpKey[animation->mKeyNum - 1].mTime){
					//変換行列を最後のコマの行列で更新
					frame->mTransformMatrix += animation->mpKey[animation->mKeyNum - 1].mMatrix*anim->mWeight;
				}
				else{
					//時間の途中の場合
					for (int k = 1; k < animation->mKeyNum; k++){
						//変換行列を、線形補間にて更新
						if (time < animation->mpKey[k].mTime &&
							animation->mpKey[k - 1].mTime != animation->mpKey[k].mTime){
							float r = (animation->mpKey[k].mTime - time) /
								(animation->mpKey[k].mTime - animation->mpKey[k - 1].mTime);
							frame->mTransformMatrix +=
								(animation->mpKey[k - 1].mMatrix*r + animation->mpKey[k].mMatrix*(1 - r))*anim->mWeight;
							break;
						}
					}
				}
			}
		}
	}

	//スキンウェイトのフレーム番号設定
	void SetSkinWeightFrameIndex();
	//頂点にアニメーションを適用する
	void AnimateVertex();
	//マテリアルの検索
	CMaterial*FindMaterial(char*name);
	//アニメーションの頂点計算を、指定した合成行列を使って計算
	void AnimateVertex(CMatrix*);

	//描画メソッド
	void Render();
};

#endif