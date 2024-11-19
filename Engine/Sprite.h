#pragma once
#include "Direct3D.h"
#include "Texture.h"
#include "Transform.h"
#include<vector>

using std::vector;

//#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ delete[] p; p = nullptr;}



//ŽlŠpŒ`ƒ|ƒŠƒSƒ“iŽOŠpŒ`‚ð‚Q–‡j‚ð•`‰æ‚·‚éƒNƒ‰ƒX
class Sprite
{
	//ƒRƒ“ƒXƒ^ƒ“ƒgƒoƒbƒtƒ@[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;		//ƒ[ƒ‹ƒhs—ñ
	};

	//’¸“_î•ñ
	struct VERTEX
	{
		XMVECTOR position;	//ˆÊ’u
		XMVECTOR uv;		//UV
	};
protected:
	uint64_t vertexNum_;
	vector<VERTEX>vertices_;
	uint64_t indexNum_;
	vector<int>indices_;
	ID3D11Buffer* pIndexBuffer_;		//ƒCƒ“ƒfƒbƒNƒXƒoƒbƒtƒ@
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//ƒRƒ“ƒXƒ^ƒ“ƒgƒoƒbƒtƒ@

	Texture* pTexture_;		//ƒeƒNƒXƒ`ƒƒ


public:
	Sprite();
	~Sprite();

	//‰Šú‰»iƒ|ƒŠƒSƒ“‚ð•\Ž¦‚·‚é‚½‚ß‚ÌŠeŽíî•ñ‚ð€”õj
	//–ß’lF¬Œ÷^Ž¸”s

	HRESULT Load(std::string fileName);//初期化用（コンストラクタでできない奴はこっちで初期化）
	//•`‰æ
	//ˆø”Ftransform	ƒgƒ‰ƒ“ƒXƒtƒH[ƒ€ƒIƒuƒWƒFƒNƒg
	void Draw(Transform& transform);

	//‰ð•ú
	void Release();

private:
	//---------Initialize‚©‚çŒÄ‚Î‚ê‚éŠÖ”---------
	virtual void InitVertexData();		//’¸“_î•ñ‚Ì€”õ
	HRESULT CreateVertexBuffer();		//’¸“_ƒoƒbƒtƒ@‚ðì¬

	virtual void InitIndexData();		//ƒCƒ“ƒfƒbƒNƒXî•ñ‚ð€”õ
	HRESULT CreateIndexBuffer();		//ƒCƒ“ƒfƒbƒNƒXƒoƒbƒtƒ@‚ðì¬

	HRESULT CreateConstantBuffer();		//ƒRƒ“ƒXƒ^ƒ“ƒgƒoƒbƒtƒ@ì¬

	HRESULT LoadTexture(std::string fileName);			//テクスチャをロード


	//---------DrawŠÖ”‚©‚çŒÄ‚Î‚ê‚éŠÖ”---------
	void PassDataToCB(Transform& transform);	//ƒRƒ“ƒXƒ^ƒ“ƒgƒoƒbƒtƒ@‚ÉŠeŽíî•ñ‚ð“n‚·
	void SetBufferToPipeline();

};