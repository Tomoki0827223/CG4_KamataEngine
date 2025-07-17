#include "TitleScnce.h"
#include <numbers>

TitleScnce::~TitleScnce() {
	delete titlemodel_;
	delete titlemodelFont_;
	delete TitleSkydome_;
}

void TitleScnce::Initialize() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();
	audio_ = KamataEngine::Audio::GetInstance();

	textureHandle_ = KamataEngine::TextureManager::Load("Title/Title1.png");
	sprite_ = KamataEngine::Sprite::Create(textureHandle_, {0, 0});

	textureHandle2_ = KamataEngine::TextureManager::Load("Title/ShotGame.png");
	sprite2_ = KamataEngine::Sprite::Create(textureHandle2_, {0, 0});

	textureHandle3_ = KamataEngine::TextureManager::Load("Title/HitEnter.png");
	sprite3_ = KamataEngine::Sprite::Create(textureHandle3_, {0, 0});

	titleskydome.Initialize();
	Camera_.Initialize();

	Timer_ = 0.0f;

	// タイトルを中央に寄せるために調整
	titleWorldTransform_.translation_ = {0.0f, 30.0f, -40.0f}; // x, y, zの値を調整

	titleWorldTransformFont_.translation_ = {-18.0f, -10.0f, 0.0f}; // x, y, zの値を調整

	titleskydome.translation_ = {0.0f, 0.0f, 0.0f};

	//TitleSEHandle_ = audio_->LoadWave("Sounds/wind.wav");
	//TitleSEHandle2_ = audio_->LoadWave("Sounds/windBell.wav");
	//TitleSEHandle3_ = audio_->LoadWave("Sounds/start.wav");

	//voiceHandle_ = audio_->PlayWave(TitleSEHandle_, true);
	//voiceHandle2_ = audio_->PlayWave(TitleSEHandle2_, true);

	// スプライトの初期化
	InitializeSprites();
}

void TitleScnce::InitializeSprites() {
	sprites.push_back(sprite_);
	sprites.push_back(sprite2_);
	sprites.push_back(sprite3_);
	sprites.push_back(sprite4_);
}

void TitleScnce::Update() {
	Timer_ += 1.0f; // フレームごとに加算

	// Enterキーでタイトル終了
	if (input_->TriggerKey(DIK_RETURN) || input_->TriggerKey(DIK_SPACE)) {
		//audio_->PlayWave(TitleSEHandle3_, false); // スタートSE
		isFinished_ = true;
	}
}

void TitleScnce::Draw() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 3Dオブジェクト描画
	KamataEngine::Model::PreDraw(commandList);
	KamataEngine::Model::PostDraw();

	// スプライト描画
	KamataEngine::Sprite::PreDraw(commandList);

	// タイトル画像（中央に表示）
	if (sprite2_) {
		sprite2_->SetPosition({320, 180}); // 画面中央に調整（例: 1280x720なら）
		sprite2_->Draw();
	}

	// 「Hit Enter」点滅（30フレームごとにON/OFF）
	if (sprite3_ && static_cast<int>(Timer_) % 60 < 30) {
		sprite3_->SetPosition({400, 400}); // 好きな位置に調整
		sprite3_->Draw();
	}

	KamataEngine::Sprite::PostDraw();
}