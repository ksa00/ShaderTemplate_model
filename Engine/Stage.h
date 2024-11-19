#pragma once
#include"Quad.h"
#include"GameObject.h"

class Stage:public GameObject
{
	int hmodel_;
	Quad* q;
public:
	Stage(GameObject* parent);
	~Stage();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Release()override;

};
