#include "Sprite.h"
#include "Camera.h"
#include<filesystem>
#include"assert.h"
//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
Sprite::Sprite() :
	vertexNum_(0), vertices_(0), pVertexBuffer_(nullptr),
	indexNum_(0), indices_(0), pIndexBuffer_(nullptr),
	pConstantBuffer_(nullptr),
	pTexture_(nullptr)
{
}

//ƒfƒXƒgƒ‰ƒNƒ^
Sprite::~Sprite()
{
	Release();
}



HRESULT Sprite::Load(std::string fileName)
{
	//頂点情報
	InitVertexData();//データを用意して
	if (FAILED(CreateVertexBuffer()))//頂点バッファ作成
	{
		return E_FAIL;
	}
	//インデックス情報
	InitIndexData();					//データを用意して
	if (FAILED(CreateIndexBuffer()))	//インデックスバッファ作成
	{
		return E_FAIL;
	}

	//コンスタントバッファ作成
	if (FAILED(CreateConstantBuffer()))//コンスタントバッファ作成
	{
		return E_FAIL;
	}

	//テクスチャのロード
	if (FAILED(LoadTexture(fileName)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//•`‰æ
void Sprite::Draw(Transform& transform)
{
	Direct3D::SetShader(SHADER_2D);


	transform.Calculation();//ƒgƒ‰ƒ“ƒXƒtƒH[ƒ€‚ðŒvŽZ
	//ƒRƒ“ƒXƒ^ƒ“ƒgƒoƒbƒtƒ@‚Éî•ñ‚ð“n‚·
	
	PassDataToCB(transform);

	//’¸“_ƒoƒbƒtƒ@AƒCƒ“ƒfƒbƒNƒXƒoƒbƒtƒ@AƒRƒ“ƒXƒ^ƒ“ƒgƒoƒbƒtƒ@‚ðƒpƒCƒvƒ‰ƒCƒ“‚ÉƒZƒbƒg
	SetBufferToPipeline();

	//•`‰æ
	Direct3D::pContext->DrawIndexed(indexNum_, 0, 0);
}

//‰ð•ú
void Sprite::Release()
{
	
	SAFE_DELETE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

///////////////‚±‚±‚©‚ç‚ÍprivateŠÖ”///////////////

//’¸“_î•ñ‚Ì€”õ
void Sprite::InitVertexData()
{
	// ’¸“_î•ñ
	vertices_=
	{
{	XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)},// ŽlŠpŒ`‚Ì’¸“_i¶ãj,
{	XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),  XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// ŽlŠpŒ`‚Ì’¸“_i‰Eãj
{	XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)},// ŽlŠpŒ`‚Ì’¸“_i‰E‰ºj
{	XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// ŽlŠpŒ`‚Ì’¸“_i¶‰ºj		
	};

	//’¸“_‚Ì”
	vertexNum_ = vertices_.size();	//‘Sƒf[ƒ^‚ÌƒTƒCƒY@€@1’¸“_•ª‚ÌƒTƒCƒY@@’¸“_”

	
}

//’¸“_ƒoƒbƒtƒ@‚ðì¬
HRESULT Sprite::CreateVertexBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexNum_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices_.data();
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, "’¸“_ƒoƒbƒtƒ@‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½", "ƒGƒ‰[", MB_OK);
		return hr;
	}
	return S_OK;
}

//ƒCƒ“ƒfƒbƒNƒXî•ñ‚ð€”õ
void Sprite::InitIndexData()
{
indices_ = { 0,2,3, 0,1,2 };

	//ƒCƒ“ƒfƒbƒNƒX”
	indexNum_ = indices_.size();

	
}

//ƒCƒ“ƒfƒbƒNƒXƒoƒbƒtƒ@‚ðì¬
HRESULT Sprite::CreateIndexBuffer()
{
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * indexNum_;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = indices_.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	HRESULT hr;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, "ƒCƒ“ƒfƒbƒNƒXƒoƒbƒtƒ@‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½", "ƒGƒ‰[", MB_OK);
		return hr;
	}
	return S_OK;
}

//ƒRƒ“ƒXƒ^ƒ“ƒgƒoƒbƒtƒ@ì¬
HRESULT Sprite::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// ƒRƒ“ƒXƒ^ƒ“ƒgƒoƒbƒtƒ@‚Ìì¬
	HRESULT hr;
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, "ƒRƒ“ƒXƒ^ƒ“ƒgƒoƒbƒtƒ@‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½", "ƒGƒ‰[", MB_OK);
		return hr;
	}
	return S_OK;
}

HRESULT Sprite::LoadTexture(std::string fileName)
{
	namespace fs = std::filesystem;

	pTexture_ = new Texture;
	assert(fs::is_regular_file(fileName));


	HRESULT hr;
	hr = pTexture_->Load(fileName);
	if (FAILED(hr))
	{
		MessageBox(NULL, "テクスチャの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}
	return S_OK;
}



//ƒRƒ“ƒXƒ^ƒ“ƒgƒoƒbƒtƒ@‚ÉŠeŽíî•ñ‚ð“n‚·
void Sprite::PassDataToCB(Transform& transform)
{
	CONSTANT_BUFFER cb;
	cb.matW = XMMatrixTranspose(transform.GetNormalMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU‚©‚ç‚Ìƒf[ƒ^ƒAƒNƒZƒX‚ðŽ~‚ß‚é
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// ƒf[ƒ^‚ð’l‚ð‘—‚é

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//ÄŠJ
}

//Šeƒoƒbƒtƒ@‚ðƒpƒCƒvƒ‰ƒCƒ“‚ÉƒZƒbƒg
void Sprite::SetBufferToPipeline()
{
	//’¸“_ƒoƒbƒtƒ@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// ƒCƒ“ƒfƒbƒNƒXƒoƒbƒtƒ@[‚ðƒZƒbƒg
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//ƒRƒ“ƒXƒ^ƒ“ƒgƒoƒbƒtƒ@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//’¸“_ƒVƒF[ƒ_[—p	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ƒsƒNƒZƒ‹ƒVƒF[ƒ_[—p
}