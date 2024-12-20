//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D g_texture : register(t0); // テクスチャー
SamplerState g_sampler : register(s0); // サンプラー

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer gModel : register(b0)
{
    float4x4 matWVP; // ワールド・ビュー・プロジェクションの合成行列
    float4x4 matW; // ワールド行列
    float4x4 matNormal; // 法線変換行列
    float4 diffuseColor; // ディフューズカラー（マテリアルの色）
    float4 factor;
    float4 ambientColor;
    float4 specularColor;
    float4 shininess;
    bool isTextured; // テクスチャ貼ってあるかどうか
};

cbuffer gStage : register(b1)
{
    float4 lightPosition;
    float4 eyePosition;
};
//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
    float4 pos : SV_POSITION; // 位置
    float4 wpos : POSITION1; // ワールド座標
    float2 uv : TEXCOORD; // UV座標
    float4 normal : NORMAL; // 法線
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
    VS_OUT outData;

    // スクリーン座標に変換し、ピクセルシェーダーへ
    outData.pos = mul(pos, matWVP);
    outData.uv = uv.xy;

    // 法線をワールド座標系に変換
    outData.normal = mul(normal, matNormal);
    outData.wpos = mul(pos, matW);

    return outData;
}
//───────────────────────────────────────
// ピクセルシェーダ
float4 PS(VS_OUT inData) : SV_Target
{
    float4 ambientSource = float4(0.2, 0.2, 0.2, 1.0);
    float4 diffuse;
    float4 ambient;

 //   float3 dir = normalize(lightPosition.xyz - inData.wpos.xyz); // 光源からピクセル位置へのベクトルを計算
  //  float4 dir = normalize(lightPosition);
    float color = saturate(dot(normalize(inData.normal), normalize(lightPosition)));

    if (!isTextured)
    {
        diffuse = diffuseColor * color * factor.x;
        ambient = diffuseColor * ambientSource * factor.x;
    }
    else
    {
        diffuse = g_texture.Sample(g_sampler, inData.uv) * color * factor.x;
        ambient = g_texture.Sample(g_sampler, inData.uv) * ambientSource * factor.x;
    }

    return diffuse + ambient;
}