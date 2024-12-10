#include "Stage.h"
#include "Model.h"
#include "Input.h"
#include "Camera.h"

void Stage::InitConstantBuffer()
{
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CONSTBUFFER_STAGE);
    cb.Usage = D3D11_USAGE_DYNAMIC;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;

    // コンスタントバッファの作成
    HRESULT hr;
    hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
    if (FAILED(hr))
    {
        MessageBox(NULL, "ステージーコンスタントバッファの作成に失敗しました", "エラー", MB_OK);
    }
}

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),pConstantBuffer_(nullptr)
{
    hModel_[0] = -1;
    hModel_[1] = -1;
    hGround = -1;
    hModel_[2] = -1;
    hDonut = -1;
}

//デストラクタ
Stage::~Stage()
{
}



//初期化
void Stage::Initialize()
{
    hModel_[0] = Model::Load("Asset/NUMBALL.fbx");
    hModel_[1] = Model::Load("Asset/tama.fbx");
    hModel_[2] = Model::Load("Asset/tamatamatama.fbx");
    hGround = Model::Load("Asset/Plane.fbx");
    hDonut = Model::Load("Asset/DonutT_Ph.fbx");
    
    transform_.position_.y = -0.25f;
    transform_.scale_ = { 0.25f, 0.25f, 0.25f };
    
    Camera::SetPosition(XMFLOAT3{ 0, 0.5, -1.5 });
    Camera::SetTarget(XMFLOAT3{ 0,0,0 });
    InitConstantBuffer();
}

//更新
void Stage::Update()
{
    transform_.rotate_.y += 0.5f;

    // Handle light position updates based on key inputs
    XMFLOAT4 lightPos = Direct3D::GetLightPos();  // Get current light position

    if (Input::IsKey(DIK_A))  // Move light left
    {
        lightPos.x -= 0.01f;
    }
    if (Input::IsKey(DIK_D))  // Move light right
    {
        lightPos.x += 0.01f;
    }
    if (Input::IsKey(DIK_W))  // Move light forward (in Z)
    {
        lightPos.z += 0.01f;
    }
    if (Input::IsKey(DIK_S))  // Move light backward (in Z)
    {
        lightPos.z -= 0.01f;
    }
    if (Input::IsKey(DIK_UP))  // Move light up (in Y)
    {
        lightPos.y += 0.01f;
    }
    if (Input::IsKey(DIK_DOWN))  // Move light down (in Y)
    {
        lightPos.y -= 0.01f;
    }

    // Update light position
    Direct3D::SetLightPos(lightPos);
    //constant buffer setting
    CONSTBUFFER_STAGE cb;
    cb.lightPosition = Direct3D::GetLightPos();
    XMStoreFloat4(&cb.eyePosition, Camera::GetPosition());
    D3D11_MAPPED_SUBRESOURCE pdata;
    Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
    memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
    Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開
    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pConstantBuffer_);	//頂点シェーダー用	
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pConstantBuffer_);	//ピクセルシェーダー用

}






//描画
void Stage::Draw()
{
    // Render the light position as a small model
    Transform ltr;
    ltr.position_ = { Direct3D::GetLightPos().x, Direct3D::GetLightPos().y, Direct3D::GetLightPos().z };
    ltr.scale_ = { 0.1f, 0.1f, 0.1f };  // Small scale to represent the light
    Model::SetTransform(hModel_[0], ltr);  // Set light transform
    Model::Draw(hModel_[0]);  // Draw the light representation

    // Render the ground (or other models in the scene)
    Transform tr;
    tr.position_ = { 0,- 0.5, 0 };  // Position of the ground
    //tr.scale_ = { 5.0f, 5.0f, 5.0f };  // Uncomment if scaling is needed
    tr.rotate_ = { 0, 0, 0 };  // No rotation
    Model::SetTransform(hGround, tr);  // Set ground transform
    Model::Draw(hGround);  // Draw the ground

    Model::SetTransform(hDonut, transform_);
    Model::Draw(hDonut);
}


//開放
void Stage::Release()
{
}