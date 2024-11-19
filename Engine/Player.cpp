#include "Player.h"
#include"Childoden.h"
#include"Input.h"
#include"Model.h"
Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hModel_(-1)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
hModel_	=Model::Load("Asset//oden.fbx");
	transform_.position_ = { 0,-5,0 };
	transform_.scale_ = { 0.5,0.5,0.5 };
	
}

void Player::Update()
{
	//transform_.rotate_.y += 1.0f;
	if (Input::IsKey(DIK_A)) {
		transform_.position_.x -= 0.1f;
	}
	if (Input::IsKey(DIK_D)) {
		transform_.position_.x += 0.1f;
	}
	if (Input::IsKeyDown(DIK_SPACE)) {
		
		GameObject* coden=Instantiate<Childoden>(this);
		coden->SetPosition(transform_.position_);
		
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

}

void Player::Release()
{
	
}
