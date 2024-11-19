#include "Transform.h"

Transform::Transform() : pParent_(nullptr)
{
    position_ = XMFLOAT3(0, 0, 0);
    rotate_ = XMFLOAT3(0, 0, 0);
    scale_ = XMFLOAT3(1, 1, 1);
    matTranslate_ = XMMatrixIdentity();
    matRotate_ = XMMatrixIdentity();
    matScale_ = XMMatrixIdentity();

}

Transform::~Transform()
{
}

void Transform::Calculation()
{
    //ˆÚ“®s—ñì¬
    matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

    //‰ñ“]s—ñì¬
    XMMATRIX rotateX, rotateY, rotateZ;
    rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
    rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
    rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
    matRotate_ = rotateZ * rotateX * rotateY;

    //Šg‘ås—ñì¬
    matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
    //e‚ª‚¢‚éê‡‚Íe‚Ì‰e‹¿‚ðŽó‚¯‚é
    if (pParent_)
    {
        return  matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
    }

    //e‚ª‚¢‚È‚¢ê‡
    return  matScale_ * matRotate_ * matTranslate_;
}

XMMATRIX Transform::GetNormalMatrix()
{
    return( matRotate_ * XMMatrixInverse(nullptr, matScale_));
}
void Transform::SetWorldPosition(const XMFLOAT3& position) {
    if (pParent_) 
    { // Calculate the world matrix 
        XMMATRIX parentWorld = pParent_->GetWorldMatrix(); 
        XMMATRIX invParentWorld = XMMatrixInverse(nullptr, parentWorld); 
        // Transform the desired world position to the local space 
        XMVECTOR worldPosition = XMLoadFloat3(&position);
        XMVECTOR localPosition = XMVector3TransformCoord(worldPosition, invParentWorld); XMStoreFloat3(&position_, localPosition);
    } else {
        position_ = position;
    } Calculation(); 
} 
XMFLOAT3 Transform::GetWorldPosition() const 
{ 
    if (pParent_) 
{ 
    XMVECTOR worldPos = XMVector3TransformCoord(XMLoadFloat3(&position_), pParent_->GetWorldMatrix());
    XMFLOAT3 result; 
    XMStoreFloat3(&result, worldPos); 
    return result;
    }
    return position_; 
    }