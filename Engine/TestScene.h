#pragma once
#include "GameObject.h"
#include"Sprite.h"

class TestScene :
    public GameObject
{
    Sprite Title_spr;
public:
    TestScene(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

