//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	float4x4	matW;			// ワールド行列
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos  : SV_POSITION;	//位置
	float2 uv	: TEXCOORD;		//UV座標
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	//ローカル座標に、ワールド行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	//outData.pos = mul(pos, matW);
    outData.pos = pos;
	outData.uv = uv;

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
    float4 output;
	//if (inData.uv.y < 1 / 3.0f)
    //    output = float4(0, 0, 0, 0);
    //else if (inData.uv.y < 2 / 3.0f)
    //    output = float4(221 / 225.0f, 0, 0, 0);
    //else
    //    output = float4(1.0, 206 / 255.0f, 0, 0);
  
            output = g_texture.Sample(g_sampler, inData.uv);
      
    return output;
}