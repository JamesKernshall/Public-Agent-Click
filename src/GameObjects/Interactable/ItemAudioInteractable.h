#pragma once

#include "AudioInteractable.h"

class ItemAudioInteractable : public AudioInteractable
{
public:
	ItemAudioInteractable(std::string InteractableName, BaseRoom* OwnerRefernce);

	std::unique_ptr<sf::Sprite>(override_sprite);
	Item_Type item;

	virtual void SucceedInteract(class Inventory* inv);
};