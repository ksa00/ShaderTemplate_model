#include "Enemy.h"
#include "Model.h"
#include "SphereCollider.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"),hModel(-1)
{
}

void Enemy::Initialize()
{
	hModel = Model::Load("Asset/enemy.fbx");

	transform_.position_.y = 3.0f;
transform_.scale_ = { 0.1f,0.1f,0.1f };
	SphereCollider* col = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
	AddCollider( col);
	
}

void Enemy::Update()
{
	static int dt;
	dt++;
	float nTime = dt / (10.0f * 10.0f) - 2.0f;
	transform_.position_.x = 4.0 * sin(nTime);

}

void Enemy::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
	
}

void Enemy::Release()
{
}
