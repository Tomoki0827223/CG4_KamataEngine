#pragma once
#include <KamataEngine.h>
#include "Model2.h" // 追加

using namespace KamataEngine;

class GameScnce {
public:
	~GameScnce();
	void Initialize();
	void Update();
	void Draw();

private:
	
	//Model* modelParticle_ = nullptr;
	Model2* model2_ = nullptr; // 追加
	Camera* camera_ = nullptr;
	WorldTransform worldTransform_;

};
