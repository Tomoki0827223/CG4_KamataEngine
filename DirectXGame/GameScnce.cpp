#include "GameScnce.h"
#include "Model2.h" // 念のため

GameScnce::~GameScnce() 
{ 
    delete camera_;

    Model2::StaticFinalize(); // 追加
}

void GameScnce::Initialize() {

	Model2::StaticInitialize(); // 追加


	model2_ = Model2::CreateRing(5, 8.0f, 6.0f);

	camera_ = new Camera();
	camera_->Initialize();

	worldTransform_.Initialize();

	sprite_ = new Sprite();
	sprite_->Create(textureHandle_, {0, 0});


    stage_ = std::make_unique<Stage>();
	stage_->Initialize();

}


void GameScnce::Update() {
	camera_->UpdateMatrix();
	worldTransform_.UpdateMatarix();
	worldTransform_.TransferMatrix();

	if (stage_) {
		stage_->Update();

		// 例: スクロールスプライトの色を変更
		auto bg1 = stage_->GetBgSprite1();
		if (bg1) {
			bg1->SetColor({1, 0.5f, 0.5f, 1}); // 赤っぽく
		}
	}
}

void GameScnce::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 背景スプライトを先に描画
	if (stage_) {
		auto bg1 = stage_->GetBgSprite1();
		auto bg2 = stage_->GetBgSprite2();
		if (bg1)
			bg1->Draw();
		if (bg2)
			bg2->Draw();
	}

	// 3Dモデル描画
	Model2::PreDraw(dxCommon->GetCommandList());
	model2_->Draw(worldTransform_, *camera_);
	Model2::PostDraw();
}