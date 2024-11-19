#include "Childoden.h"
#include"Model.h"
#include"SphereCollider.h"
#include"Enemy.h"

Childoden::Childoden(GameObject* parent)
	:GameObject(parent, "Childoden"),hModel_(-1)
{
}

Childoden::~Childoden()
{
}

void Childoden::Initialize()
{
hModel_=Model::Load("Asset//pacman.fbx");
//transform_.scale_= { 0.25,0.25,0.25 };
	SphereCollider* collider = new SphereCollider(XMFLOAT3(0,0.0, 0), 0.2f);
     	AddCollider(collider);
}

void Childoden::Update()  
{
	transform_.rotate_.y += 3.0f;
	//transform_.position_.z += 0.05f;
	transform_.position_.y += 0.05f;
	
	if (transform_.position_.y > 4.0f)KillMe();
	
	
}

void Childoden::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

}

void Childoden::Release()
{
	

}

void Childoden::OnCollision(GameObject* pTarget)
{
  	if (pTarget->GetObjectName() == "Enemy") {
		pTarget->KillMe();
	}
	this->KillMe();
}
