#include "Stage.h"
#include"Model.h"


Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage"),hmodel_(-1)
{
	

}
Stage::~Stage()
{
}

void Stage::Initialize()
{
	hmodel_ = Model::Load("Asset/NUMBALL.fbx");
	

}

void Stage::Update()
{
	transform_.rotate_.y += 0.5f;
	transform_.rotate_.x += 0.5f;

}

void Stage::Draw()
{
	Model::SetTransform(hmodel_, transform_);
	Model::Draw(hmodel_);
}


void Stage::Release()
{

}
