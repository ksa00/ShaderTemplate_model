#include "TestScene.h"
#include "PlayScene.h"
#include "SceneManager.h"
#include "Stage.h"





TestScene::TestScene(GameObject* parent)
	:GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{
	
	Instantiate<Stage>(this);
}

void TestScene::Update()
{
}

void TestScene::Draw()
{

}

void TestScene::Release()
{
	
}
