
#include "SphereCollider.h"
#include "GameObject.h"
#include "Model.h"
#include "Transform.h"
#include"Collider.h"
//コンストラクタ
Collider::Collider() :
	pGameObject_(nullptr)
{
}

//デストラクタ
Collider::~Collider()
{
}



//球体同士の衝突判定
//引数：circleA	１つ目の球体判定
//引数：circleB	２つ目の球体判定
//戻値：接触していればtrue
bool Collider::IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB)
{//ここをgetworldposition()をgetposition()に変えたら動きました理由わからなかったんです
	XMFLOAT3 centerA = circleA->center_;
	XMFLOAT3 positionA = circleA->pGameObject_->GetWorldPosition();
	XMFLOAT3 centerB = circleB->center_;
	XMFLOAT3 positionB = circleB->pGameObject_->GetWorldPosition();

	XMVECTOR v = (XMLoadFloat3(&centerA) + XMLoadFloat3(&positionA))
		- (XMLoadFloat3(&centerB) + XMLoadFloat3(&positionB));


	// Calculate the squared distance between the centers
	float distanceSquared = XMVector3LengthSq(v).m128_f32[0];

	// Compare squared distance to the sum of the radii squared
	float radiusSum = circleA->size_.x + circleB->size_.x;
	return distanceSquared <= (radiusSum * radiusSum);
}

//テスト表示用の枠を描画
//引数：position	オブジェクトの位置
void Collider::Draw(XMFLOAT3 position)
{

}