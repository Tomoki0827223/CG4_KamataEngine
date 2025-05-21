#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Effect {

public:
	
	void Initialize(Model* model);
	void Update();
	void Draw(Camera* camera);

	// 追加：ワールド変換を設定する関数
	void SetWorldTransform(const WorldTransform& wt);

private:
	Model* model_ = nullptr;
	WorldTransform worldTransform_;

	// ランダム値を保持する
	float randomScaleY_ = 1.0f;
	float randomRotZ_ = 0.0f;

};
