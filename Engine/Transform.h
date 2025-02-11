#pragma once
#include <DirectXMath.h>

using namespace DirectX;

//位置、向き、拡大率などを管理するクラス
class Transform
{public:
	XMMATRIX matTranslate_;	//移動行列
	XMMATRIX matRotate_;	//回転行列	
	XMMATRIX matScale_;	//拡大行列


	XMFLOAT3 position_;	//位置
	XMFLOAT3 rotate_;	//向き
	XMFLOAT3 scale_;	//拡大率
	Transform* pParent_;	//親オブジェクトのトランスフォーム

	//コンストラクタ
	Transform();

	//デストラクタ
	~Transform();

	//各行列の計算
	void Calculation();

	//ワールド行列を取得
	XMMATRIX GetWorldMatrix();

	//法線変形用行列を取得
	XMMATRIX GetNormalMatrix();

	void SetWorldPosition(const XMFLOAT3& position);

	XMFLOAT3 GetWorldPosition() const;

	static XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}
};