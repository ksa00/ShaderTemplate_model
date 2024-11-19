#pragma once
#include "GameObject.h"
#include"Sprite.h"
//テストシーンを管理するクラス
class GameOver : public GameObject
{
	Sprite over;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameOver(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

