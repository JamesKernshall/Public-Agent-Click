#include "ItemAudioInteractable.h"
#include "GameObjects/Inventory.h"

ItemAudioInteractable::ItemAudioInteractable(std::string InteractableName, BaseRoom* OwnerRefernce) : AudioInteractable(InteractableName, OwnerRefernce)
{
	item = Item_Type::EMPTY;
}

void ItemAudioInteractable::SucceedInteract(Inventory* inv)
{
	if (override_sprite != nullptr)
	{
		inv->AddItem(*override_sprite, item);
	}
	else
	{
		inv->AddItem(*sprite, item);
	}
	if (!repeatable)
	{
		isInteractable = false;
		isActive = false;
	}
}
