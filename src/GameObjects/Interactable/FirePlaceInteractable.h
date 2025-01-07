#pragma once

#include "ItemAudioInteractable.h"

class FirePlaceInteractable : public ItemAudioInteractable
{
public:
	FirePlaceInteractable(std::string InteractableName, BaseRoom* OwnerRefernce);

	virtual void SucceedInteract(class Inventory* inv);

	sf::SoundBuffer failWaterBucket;
	sf::SoundBuffer successWaterBucket;
};