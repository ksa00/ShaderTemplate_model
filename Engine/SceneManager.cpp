#include "SceneManager.h"
#include "Model.h"
#include "TestScene.h"
#include "PlayScene.h"
#include "GameOver.h"

SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		KillAllChildren();

	

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_GAMEOVER: Instantiate<GameOver>(this); break;
		}
	
		currentSceneID_ = nextSceneID_;
	}

}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

/// <summary>
/// 指定したシーンをnextSceneID_に設定する（＝次のUpdateでシーンが変わる）
/// </summary>
/// <param name="_next">次に移行するシーンID(次のフレームで更新）</param>
void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next;
}