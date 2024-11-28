#include "Stage.h"
#include"Model.h"


Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage")

{
		hmodel_[0] = -1;
		hmodel_[1] = -1;
		hmodel_[2] = -1;

}
Stage::~Stage()
{
}

void Stage::Initialize()
{
	hmodel_[0] = Model::Load("Asset/NUMBALL.fbx");
	hmodel_[1] = Model::Load("Asset/tama.fbx");
	hmodel_[2] = Model::Load("Asset/tamatamatama.fbx");
}

void Stage::Update()
{
	transform_.position_.x = -2.0f;
	transform_.rotate_.y += 0.5f;
transform_.rotate_.x += 0.5f;

}

void Stage::Draw()
{
	for (int i = 0; i < 3; i++) {
		Transform tr;
		tr.position_ = { transform_.position_.x + (float)i * 2.0f,transform_.position_.y,transform_.position_.z };
		tr.scale_ = transform_.scale_;
		tr.rotate_ = transform_.rotate_;
		Model::SetTransform(hmodel_[i], tr);
		Model::Draw(hmodel_[i]);
	}
}


void Stage::Release()
{

}
