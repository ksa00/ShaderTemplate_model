#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

//クラスの前方宣言
class GameObject;
class SphereCollider;


//あたり判定のタイプ
enum ColliderType
{
	COLLIDER_CIRCLE		//球体
};

//-----------------------------------------------------------
//あたり判定を管理するクラス
//-----------------------------------------------------------
class Collider
{
	//それぞれのクラスのprivateメンバにアクセスできるようにする

	friend class SphereCollider;

protected:
	GameObject* pGameObject_;	//この判定をつけたゲームオブジェクト
	ColliderType	type_;			//種類
	XMFLOAT3		center_;		//中心位置（ゲームオブジェクトの原点から見た位置）
	XMFLOAT3		size_;			//判定サイズ（幅、高さ、奥行き）
	

public:
	//コンストラクタ
	Collider();

	//デストラクタ
	virtual ~Collider();
	
	//接触判定（継承先のSphereColliderかBoxColliderでオーバーライド）
	//引数：target	相手の当たり判定
	//戻値：接触してればtrue
	virtual bool IsHit(Collider* target) = 0;


	//球体同士の衝突判定
	//引数：circleA	１つ目の球体判定
	//引数：circleB	２つ目の球体判定
	//戻値：接触していればtrue
	bool IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB);

	//テスト表示用の枠を描画
	//引数：position	オブジェクトの位置
	void Draw(XMFLOAT3 position);

	//セッター
	void SetGameObject(GameObject* gameObject) { pGameObject_ = gameObject; }


};