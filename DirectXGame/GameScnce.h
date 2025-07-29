#pragma once
#include <KamataEngine.h>
#include "Model2.h" // 追加
#include "Stage.h"

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

	std::unique_ptr<Stage> stage_;

	uint32_t textureHandle_ = 0; // テクスチャハンドル
	Sprite* sprite_ = nullptr;   // スプライト
};
