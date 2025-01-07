#pragma once

#include "AudioInteractable.h"
#include "Room/PlayerRoomSpawner.h"

class RoomTransitionInteractable : public AudioInteractable
{
public:
	RoomTransitionInteractable(std::string InteractableName, BaseRoom* OwnerRefernce);

	virtual void Render() override;

	virtual void SucceedInteract(class Inventory* inv) override;

public:
	void AssignRoomTransitionName(std::string room, PlayerRoomSpawner::Direction direction);


private:
	std::string roomName;
	PlayerRoomSpawner::Direction direction;
};