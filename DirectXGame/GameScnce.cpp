#include "GameScnce.h"
#include "Model2.h" // 念のため

GameScnce::~GameScnce() 
{ 
    delete camera_;

    Model2::StaticFinalize(); // 追加
}

void GameScnce::Initialize() {

	Model2::StaticInitialize(); // 追加

    model2_ = Model2::CreateSquare(5.0f, 5.0f, 5); //四角形


	camera_ = new Camera();
	camera_->Initialize();

	worldTransform_.Initialize();
}


void GameScnce::Update() {
    camera_->UpdateMatrix();
    worldTransform_.UpdateMatarix();
    worldTransform_.TransferMatrix();
}

void GameScnce::Draw() 
{
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();

    Model2::PreDraw(dxCommon->GetCommandList());

    model2_->Draw(worldTransform_, *camera_);
    
    Model2::PostDraw();

}
