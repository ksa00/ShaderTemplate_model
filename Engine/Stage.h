#pragma once
#include"Quad.h"
#include"GameObject.h"

class Stage:public GameObject
{
	int hmodel_[3];
	
public:
	Stage(GameObject* parent);
	~Stage();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Release()override;

};
