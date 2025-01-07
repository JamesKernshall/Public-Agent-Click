#include "RoomTransitionInteractable.h"
#include "Room/BaseRoom.h"
#include "Room/RoomManager.h"

RoomTransitionInteractable::RoomTransitionInteractable(std::string InteractableName, BaseRoom* OwnerRefernce) : AudioInteractable(InteractableName, OwnerRefernce)
{
	direction = PlayerRoomSpawner::North;
}

void RoomTransitionInteractable::Render()
{
	__super::Render();
}

void RoomTransitionInteractable::SucceedInteract(class Inventory* inv)
{
	Owner->Owner->LoadNewRoom(roomName, direction);
}

void RoomTransitionInteractable::AssignRoomTransitionName(std::string room, PlayerRoomSpawner::Direction dir)
{
	roomName = room;
	direction = dir;
}
