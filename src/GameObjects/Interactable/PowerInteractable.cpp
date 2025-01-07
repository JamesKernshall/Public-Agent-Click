#include "PowerInteractable.h"
#include "Core/Data.h"

PowerInteractable::PowerInteractable(std::string InteractableName, BaseRoom* OwnerRefernce) : AudioInteractable(InteractableName, OwnerRefernce)
{
	
}


void PowerInteractable::SucceedInteract(Inventory* inv)
{
	Data::GetInstance()->mansion_power = !Data::GetInstance()->mansion_power;
}
