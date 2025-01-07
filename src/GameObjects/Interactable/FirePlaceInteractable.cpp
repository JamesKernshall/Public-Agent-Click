#include "FirePlaceInteractable.h"
#include "Room/Rooms/Mansion/RoomMansionDining.h"
#include "GameObjects/Inventory.h"

FirePlaceInteractable::FirePlaceInteractable(std::string InteractableName, BaseRoom* OwnerRefernce) : ItemAudioInteractable(InteractableName, OwnerRefernce)
{

}


void FirePlaceInteractable::SucceedInteract(Inventory* inv)
{
	RoomMansionDining* dining = dynamic_cast<RoomMansionDining*>(Owner);

	if (dining != nullptr)
	{
		if (!dining->isLit)
		{
			Data::GetInstance()->gamestate = Data::Winner;
			Data::GetInstance()->OnGameStateSwitch();
			return;
		}
		else
		{
			if (dining->TryExtinguish())
			{
				SetCorrectItem(Item_Type::EMPTY);
				TryPlayNewSound(&successWaterBucket);
			}
			else
			{
				inv->AddItem(*sprite, Item_Type::BUCKET);
				TryPlayNewSound(&failWaterBucket);
			}
		}
	}
}
