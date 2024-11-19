#include "GameOver.h"
#include "Sprite.h"
#include "Input.h"
#include "SceneManager.h"
GameOver::GameOver(GameObject* parent)
	:GameObject(parent,"GameOver")
{
}

void GameOver::Initialize()
{
	over.Load("Asset/GameOver.png");

}

void GameOver::Update()
{
	if (Input::IsKeyDown(DIK_RETURN)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
	if (Input::IsKeyDown(DIK_ESCAPE)) {
		exit(0);
	}
}

void GameOver::Draw()
{
	
	over.Draw(transform_);
}

void GameOver::Release()
{
}
