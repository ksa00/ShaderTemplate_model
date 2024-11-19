#include "GameObject.h"

//コンストラクタ（親も名前もなし）
GameObject::GameObject(void) :
	GameObject(nullptr, "")
{

}


GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name)

{
	childList_.clear();
	state_ = { 0, 1, 1, 0 };

	if (parent)
		transform_.pParent_ = &parent->transform_;
}

GameObject::~GameObject()
{
	for (auto it = colliderList_.begin(); it != colliderList_.end(); it++)
	{
		SAFE_DELETE(*it);
	}
	colliderList_.clear();
}

bool GameObject::isDead_()
{
	return (state_.dead != 0);
}

void GameObject::DrawSub()
{
	Draw();


	//その子オブジェクトの描画処理
	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	Update();
	Transform();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->UpdateSub();
	}

   	for (auto it = childList_.begin(); it != childList_.end();)
	{
		if ((*it)->isDead_() == true)
		{
			(*it)->ReleaseSub();
			SAFE_DELETE(*it);
			it = childList_.erase(it);
		}
		else
		{
			//当たり判定
			(*it)->Collision(GetParent());
			it++;
		}
	}
}

void GameObject::ReleaseSub()
{
	//コライダーを削除
	ClearCollider();


	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->ReleaseSub();
		SAFE_DELETE(*it);
	}

	Release();
}

void GameObject::KillMe()
{
	state_.dead = 1;
}

void GameObject::KillAllChildren()
{
	//子供がいないなら終わり
	if (childList_.empty())
		return;

	//イテレータ
	auto it = childList_.begin();	//先頭
	auto end = childList_.end();	//末尾

	//子オブジェクトを1個ずつ削除
	while (it != end)
	{
		KillObjectSub(*it);
		delete* it;
		it = childList_.erase(it);
	}

	//リストをクリア
	childList_.clear();
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	SetPosition(XMFLOAT3(x, y, z));
}
//子オブジェクトリストを取得
std::list<GameObject*>* GameObject::GetChildList()
{
	return &childList_;
}


GameObject* GameObject::GetParent()
{
	return pParent_;
}

void GameObject::PushBackChild(GameObject* obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_back(obj);

}

void GameObject::PushFrontChild(GameObject* obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_front(obj);
}

GameObject* GameObject::FindChildObject(const string& name)
{
	//子供がいないなら終わり
	if (childList_.empty())
		return nullptr;

	//イテレータ
	auto it = childList_.begin();	//先頭
	auto end = childList_.end();	//末尾

	//子オブジェクトから探す
	while (it != end) {
		//同じ名前のオブジェクトを見つけたらそれを返す
		if ((*it)->GetObjectName() == name)
			return *it;

		//その子供（孫）以降にいないか探す
		GameObject* obj = (*it)->FindChildObject(name);
		if (obj != nullptr)
		{
			return obj;
		}

		//次の子へ
		it++;
	}

	//見つからなかった
	return nullptr;
}




const std::string& GameObject::GetObjectName(void) const
{
	return objectName_;
}

void GameObject::AddCollider(Collider* pCollider)
{
	pCollider->SetGameObject(this);
	colliderList_.push_back(pCollider);
}

void GameObject::ClearCollider()
{
	for (auto it = colliderList_.begin(); it != colliderList_.end(); it++)
	{
		SAFE_DELETE(*it);
	}
	colliderList_.clear();
}




void GameObject::Collision(GameObject* pTarget)
{
	//自分同士の当たり判定はしない
	if (pTarget == nullptr || this == pTarget)
	{
		return;
	}

	//自分とpTargetのコリジョン情報を使って当たり判定
	//1つのオブジェクトが複数のコリジョン情報を持ってる場合もあるので二重ループ
	for (auto i = this->colliderList_.begin(); i != this->colliderList_.end(); i++)
	{
		for (auto j = pTarget->colliderList_.begin(); j != pTarget->colliderList_.end(); j++)
		{
			if ((*i)->IsHit(*j))
			{
				//当たった
				this->OnCollision(pTarget);
			}
		}
	}

	//子供がいないなら終わり
	if (pTarget->childList_.empty())
		return;

	//子供も当たり判定
	for (auto i = pTarget->childList_.begin(); i != pTarget->childList_.end(); i++)
	{
		Collision(*i);
	}
}

GameObject* GameObject::GetRootJob()
{
	if (GetParent() == nullptr)
	{
		return this;
	}
	else return GetParent()->GetRootJob();
}

void GameObject::KillObjectSub(GameObject* obj)
{
	if (!childList_.empty())
	{
		auto list = obj->GetChildList();
		auto it = list->begin();
		auto end = list->end();
		while (it != end)
		{
			KillObjectSub(*it);
			delete* it;
			it = list->erase(it);
		}
		list->clear();
	}
	obj->Release();
}
