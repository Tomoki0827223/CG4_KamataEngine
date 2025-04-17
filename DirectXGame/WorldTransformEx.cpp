#include "3d/WorldTransform.h"
#include <KamataEngine.h>
#include <math/MathUtility.h>

using namespace KamataEngine;
using namespace MathUtility;


void WorldTransform::UpdateMatarix() {

	Matrix4x4 matScale = MakeScaleMatrix(scale_);

	Matrix4x4 matRotateX = MakeRotateXMatrix(rotation_.x);
	Matrix4x4 matRotateY = MakeRotateYMatrix(rotation_.y);
	Matrix4x4 matRotateZ = MakeRotateZMatrix(rotation_.z);
	Matrix4x4 matRot = matRotateZ * matRotateX * matRotateY;

	Matrix4x4 matTranslate = MakeTranslateMatrix(translation_);

	matWorld_ = matScale * matRot * matTranslate;

	// 定数バッファに転送する
	TransferMatrix();
}