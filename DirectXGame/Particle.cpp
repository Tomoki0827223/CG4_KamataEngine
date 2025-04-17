#include "Particle.h"
#include "math/MathUtility.h"

using namespace MathUtility;

void Particle::Initialize(Model* model) 
{ 
	assert(model);
	model_ = model;
	worldTransform_.Initialize();

	objectcolor_.Initialize();
	color_ = {1, 1, 0, 1}; // RGBA形式で色を指定
}

void Particle::Update() 
{
	worldTransform_.translation_ += {0.0f, 0.1f, 0.0f}; // ワールド変形の位置を初期化
	worldTransform_.TransferMatrix();                   // ワールド変形の転送
	worldTransform_.UpdateMatarix(); // ワールド変形の更新

	objectcolor_.SetColor(color_); // 色を設定
}

void Particle::Draw(Camera* camera) {

	model_->Draw(worldTransform_, *camera, &objectcolor_); // 必要な引数を渡す
}
