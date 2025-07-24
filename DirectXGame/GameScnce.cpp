#include "GameScnce.h"
#include "KamataEngine.h"

using namespace KamataEngine;

void GameScnce::Initialize() {

	// ファイルパスを組み立てて開く
	const std::string fullpath = std::string("Resources/levels/") + "scene.json";

	std::ifstream file;

	file.open(fullpath);

	if (file.fail()) {
		assert(0);
	}

	// JSON文字列から解凍したデータ
	nlohmann::json deserialized;
	// 解凍
	file >> deserialized;
	// 正しいレベルデータファイルかチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());
	// "name"を文字列として取得
	std::string name = deserialized["name"].get<std::string>();
	// 正しいレベルデータファイルかチェック
	assert(name.compare("scene") == 0);

	levelData = new LevelData();

	levelData->name = deserialized["name"].get<std::string>();
	assert(levelData->name == "scene");

	for (nlohmann::json& object : deserialized["objects"]) {

		assert(object.contains("type"));

		if (object["type"].get<std::string>() == "MESH") {

			levelData->objects.push_back(ObjectData());
			ObjectData& objectData = levelData->objects.back();

			objectData.type = object["type"].get<std::string>();
			objectData.name = object["name"].get<std::string>();

			// トランスフォーム
			nlohmann::json transform = object["transform"];
			objectData.transform.translation.x = (float)transform["translation"][0];
			objectData.transform.translation.y = (float)transform["translation"][2];
			objectData.transform.translation.z = (float)transform["translation"][1];

			objectData.transform.rotation.x = -(float)transform["rotation"][0];
			objectData.transform.rotation.y = -(float)transform["rotation"][2];
			objectData.transform.rotation.z = -(float)transform["rotation"][1];

			objectData.transform.scaling.x = (float)transform["scale"][0];
			objectData.transform.scaling.y = (float)transform["scale"][2];
			objectData.transform.scaling.z = (float)transform["scale"][1];

			// file_nameがあれば格納
			if (object.contains("file_name")) {
				objectData.file_name = object["file_name"].get<std::string>();
			}
		}
	}

	// レベルデータからオブジェクトを生成、配置
	for (auto& objectData : levelData->objects) {
		// ファイル名から登録済みモデルを検索
		Model* model = nullptr;
		decltype(models)::iterator it = models.find(objectData.file_name);
		if (it != models.end()) {
			model = it->second;
		} else {
			// モデルが未登録なら新規作成（仮実装: CreateFromOBJ等は適宜修正）
			model = Model::CreateFromOBJ(objectData.file_name);
			models[objectData.file_name] = model;
		}
		// モデルを指定して3Dオブジェクトを生成
		WorldTransform* newObject = new WorldTransform();
		// 座標
		newObject->translation_ = objectData.transform.translation;
		// 回転角
		newObject->rotation_ = objectData.transform.rotation;
		// スケール
		newObject->scale_ = objectData.transform.scaling;

		newObject->Initialize();

		// 配列に登録
		objects.push_back(newObject);
	}

	camera = new Camera();
	camera->Initialize();
}

void GameScnce::Update() {

	for (WorldTransform* object : objects) {
		// ワールド変換行列を更新
		object->UpdateMatarix();
	}

	// 必要に応じてオブジェクトやモデルの更新処理を追加
	// 例: viewProjectionの更新
	camera->UpdateMatrix();
}

void GameScnce::Draw() {


	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Model::PreDraw(dxCommon->GetCommandList());

	int i = 0;
	// モデルの描画処理
	for (auto& ObjectData : levelData->objects) {
		// モデル名からモデルを取得
		Model* model = nullptr;
		decltype(models)::iterator it = models.find(ObjectData.file_name);
		if (it != models.end())
		{
			model = it->second; 
		}

		// cameraはポインタなので参照渡しに修正
		if (model) {
			
			model->Draw(*objects[i], *camera);
		}
		i++;
	}

	Model::PostDraw();
}