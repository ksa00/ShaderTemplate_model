#include "Stage.h"
#include "Model.h"
#include "Input.h"
#include "Camera.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    hModel_[0] = -1;
    hModel_[1] = -1;
    hGround = -1;
    hModel_[2] = -1;
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
    hGround = Model::Load("Asset/dodai.fbx");

    Camera::SetPosition(XMFLOAT3{ 0, 0.5, -1 });
    Camera::SetTarget(XMFLOAT3{ 0,0,0 });
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
    tr.position_ = { 0, 0, 0 };  // Position of the ground
    //tr.scale_ = { 5.0f, 5.0f, 5.0f };  // Uncomment if scaling is needed
    tr.rotate_ = { 0, 0, 0 };  // No rotation
    Model::SetTransform(hGround, tr);  // Set ground transform
    Model::Draw(hGround);  // Draw the ground
}


//開放
void Stage::Release()
{
}