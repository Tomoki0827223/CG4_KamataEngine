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
	
	Model* modelParticle_ = nullptr;
	Camera* camera_ = nullptr;
	WorldTransform worldTransform_;

};
