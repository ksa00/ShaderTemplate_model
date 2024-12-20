//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D g_texture : register(t0); // テクスチャー
SamplerState g_sampler : register(s0); // サンプラー

Texture2D g_toon_texture : register(t1); // toon テクスチャー
SamplerState g_toon_sampler : register(s1); // toonサンプラー

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
    float4 color : COLOR;//色明るさ
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
    outData.uv = uv;

    // 法線をワールド座標系に変換
    outData.normal = mul(normal, matNormal);
    float4 light = lightPosition;
    light = normalize(light);
    outData.color = clamp(dot(normal, light), 0, 1);
    outData.wpos = mul(pos, matW);

    return outData;
}

////───────────────────────────────────────
//// ピクセルシェーダ
//float4 PS(VS_OUT inData) : SV_Target
//{
//    float4 ambientSource = float4(0.2, 0.2, 0.2, 1.0);
//    float4 diffuse;
//    float4 ambient;

//    float3 dir = normalize(lightPosition.xyz - inData.wpos.xyz); // 光源からピクセル位置へのベクトルを計算
//    float NdotL = saturate(dot(normalize(inData.normal.xyz), dir));
    
//    // Quantize the lighting to create distinct bands (toon shading)
//    float toonLevels = 3.0; // Number of distinct shades
//    float quantizedNdotL = floor(NdotL * toonLevels) / toonLevels;

//    if (!isTextured)
//    {
//        diffuse = diffuseColor * quantizedNdotL * factor.x;
//        ambient = diffuseColor * ambientSource * factor.x;
//    }
//    else
//    {
//        diffuse = g_texture.Sample(g_sampler, inData.uv) * quantizedNdotL * factor.x;
//        ambient = g_texture.Sample(g_sampler, inData.uv) * ambientSource * factor.x;
//    }

  
//    float2 uv = float2(quantizedNdotL, 0.0);
//    return g_toon_texture.Sample(g_toon_sampler,uv);
//}

//ネットにあったやつ
//float4 PS(VS_OUT inData) : SV_Target
//{
//    float4 ambientSource = float4(0.2, 0.2, 0.2, 1.0);
//    float4 diffuse;
//    float4 ambient;

//    float3 dir = normalize(lightPosition.xyz - inData.wpos.xyz);
//    float NdotL = saturate(dot(normalize(inData.normal.xyz), dir));

//    // Define thresholds for toon levels using step function
//    float toonLevel1 = 0.2;
//    float toonLevel2 = 0.4;
//    float toonLevel3 = 0.6;
//    float toonLevel4 = 0.8;

//    // Create quantized levels
//    float toonShading = step(toonLevel1, NdotL) * 0.25 +
//                        step(toonLevel2, NdotL) * 0.25 +
//                        step(toonLevel3, NdotL) * 0.25 +
//                        step(toonLevel4, NdotL) * 0.25;

//    if (!isTextured)
//    {
//        diffuse = diffuseColor * toonShading * factor.x;
//        ambient = diffuseColor * ambientSource * factor.x;
//    }
//    else
//    {
//        diffuse = g_texture.Sample(g_sampler, inData.uv) * toonShading * factor.x;
//        ambient = g_texture.Sample(g_sampler, inData.uv) * ambientSource * factor.x;
//    }
//    return ambient+diffuse;
//}


//先生、 のやつ
float4 PS(VS_OUT inData) : SV_Target
{
    float4 ambientSource = float4(0.2, 0.2, 0.2, 1.0);
    float4 diffuse;
    float4 ambient;
  //  float3 dir = normalize(lightPosition.xyz - inData.wpos.xyz); // 光源からピクセル位置へのベクトルを計算
    //float color = saturate(dot(normalize(inData.normal.xyz), dir));
    float4 NL = saturate(dot(inData.normal, normalize(lightPosition)));
    float4 n1 = float4(1 / 4.0, 1 / 4.0, 1 / 4.0, 1);
    float4 n2 = float4(2 / 4.0, 2 / 4.0, 2 / 4.0, 1);
    float4 n3 = float4(3 / 4.0, 3 / 4.0, 3 / 4.0, 1);
    float4 n4 = float4(4 / 4.0, 4 / 4.0, 4 / 4.0, 1);
    float4 tI = 0.1 * step(n1, inData.color)
               + 0.2 * step(n2, inData.color) 
               + 0.3 * step(n3, inData.color) 
               + 0.4 * step(n4, inData.color);
    if (!isTextured)
    {
        diffuse = diffuseColor * tI * factor.x;
        ambient = diffuseColor * ambientSource;
    }
    else
    {
        diffuse = g_texture.Sample(g_sampler, inData.uv) * tI * factor.x;
        ambient = g_texture.Sample(g_sampler, inData.uv) * ambientSource ;
    }
  //  return diffuse + ambient;
    float2 uv = float2(tI.x, 0);
    return g_toon_texture.Sample(g_toon_sampler, uv);
}
