#include "../../../../StdAfx.h"
#include "SpriteComponent.h"
#include "../../GameObject.h"
#include "../../../GameManager.h"
#include "../../../Renderer.h"

SpriteComponent::SpriteComponent(GameObject* owner, int drawOrder)
	: RenderComponent(owner)
	, draw_order_(draw_order_)
{
	this->owner_->GetGameManager()->GetRenderer()->AddSprite(this);
	
	object_name_ = std::string("不明なオブジェクト");
}

SpriteComponent::~SpriteComponent(void)
{
}

void SpriteComponent::SetObjectName(std::string objectName)
{
	object_name_ = objectName;
}

void SpriteComponent::Draw(void)
{
	std::cout << object_name_ + "のスプライトが描画された。\n";
}
