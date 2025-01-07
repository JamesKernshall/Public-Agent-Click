#pragma once

#include "AudioInteractable.h"

class PowerInteractable : public AudioInteractable 
{
public:
	PowerInteractable(std::string InteractableName, BaseRoom* OwnerRefernce);

	virtual void SucceedInteract(class Inventory* inv);
};