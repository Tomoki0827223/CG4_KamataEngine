#include "GameScnce.h"
#include "Model2.h" // 念のため

GameScnce::~GameScnce() 
{ 
    delete modelParticle_;
    delete camera_;

    Model2::StaticFinalize(); // 追加
}

void GameScnce::Initialize() {

    Model2::StaticInitialize(); // 追加

    modelParticle_ = new Model();
	modelParticle_ = Model::CreateFromOBJ("ddd", true);

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

    Model::PreDraw(dxCommon->GetCommandList());

    modelParticle_->Draw(worldTransform_, *camera_);

    Model::PostDraw();
}
