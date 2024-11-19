#pragma once

#include <list>
#include <string>
#include "Transform.h"
#include "Direct3D.h"

#include"Collider.h"
using std::string;
using std::list;



class GameObject
{
private:
	//フラグ
	struct OBJECT_STATE
	{
		unsigned initialized : 1;	//初期化済みか
		unsigned entered : 1;		//更新するか
		unsigned visible : 1;		//描画するか
		unsigned dead : 1;			//削除するか
	};
	OBJECT_STATE state_;
	GameObject* pParent_;
	list<GameObject*>	childList_;
protected:
	
	Transform			transform_;
	
	string				objectName_; //オブジェクトの名前の文字列
	//衝突判定リスト
	std::list<Collider*>	colliderList_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	virtual  ~GameObject();

	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw() = 0;
	virtual void Release(void) = 0;

	bool isDead_();
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();
	void KillMe();
	//子オブジェクトを全て削除
	void KillAllChildren();
	void SetPosition(XMFLOAT3 position);
	void SetPosition(float x, float y, float z);
	XMFLOAT3 GetWorldPosition() { return transform_.GetWorldPosition(); }

	//各アクセス関数
	XMFLOAT3 GetPosition() { return transform_.position_; }
	//親オブジェクトを取得
//戻値：親オブジェクトのアドレス
	GameObject* GetParent();
	//子オブジェクトリストを取得
	//戻値：子オブジェクトリスト
	std::list<GameObject*>* GetChildList();
	//子オブジェクトを追加（リストの最後へ）
	//引数：追加するオブジェクト
	void PushBackChild(GameObject* obj);

	//子オブジェクトを追加（リストの先頭へ）
	//引数：obj 追加するオブジェクト
	void PushFrontChild(GameObject* obj);
	GameObject* FindChildObject(const string& name);


	//名前でオブジェクトを検索（対象は全体）
	//引数：検索する名前
	//戻値：見つけたオブジェクトのアドレス
	GameObject* FindObject(const std::string& name) { return GetRootJob()->FindChildObject(name); }

	//オブジェクトの名前を取得
	//戻値：名前
	const std::string& GetObjectName(void) const;



	void AddCollider(Collider* pCollider);
	void ClearCollider();
	void Collision(GameObject* pTarget);
	//RootJobを取得
	GameObject* GetRootJob();
	//何かと衝突した場合に呼ばれる（オーバーライド用）
	//引数：pTarget	衝突した相手
	virtual void OnCollision(GameObject* pTarget) {};


private:

	//オブジェクト削除（再帰）
	//引数：obj　削除するオブジェクト
	void KillObjectSub(GameObject* obj);


};

//テンプレートの定義
template <class T>
T* Instantiate(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}