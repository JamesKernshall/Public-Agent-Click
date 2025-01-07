#include "RoomMansionBase.h"
#include "GameObjects/Interactable/RoomTransitionInteractable.h"

RoomMansionBase::RoomMansionBase()
{

}

RoomMansionBase::RoomMansionBase(RoomManager* OwnerRef) : BaseRoom(OwnerRef)
{
}

void RoomMansionBase::Render()
{
	if (Data::GetInstance()->mansion_power)
	{
		__super::Render();
	}
	else
	{
		Data::RenderBackground(darkBackground);

		for (int i = 0; i < interactables.size(); i++)
		{
			interactables[i]->Render();
		}
	}
}
