#pragma once
#include "GameObject.h"

struct CONSTBUFFER_STAGE {
    XMFLOAT4 lightPosition;//光源位置
    XMFLOAT4 eyePosition;//視点位置

};

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[3];    //モデル番号
    int hGround;
    int hDonut;
    ID3D11Buffer* pConstantBuffer_;
    void InitConstantBuffer();

public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};
