#pragma once
#include"Quad.h"
#include"GameObject.h"

class Stage:public GameObject
{
	int hmodel_;
	int tama_;
	int tama_tama;
	int tama_tama_tama;
public:
	Stage(GameObject* parent);
	~Stage();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Release()override;

};
