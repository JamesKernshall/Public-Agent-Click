#pragma once

#include "Room/BaseRoom.h"

class RoomMansionBase : public BaseRoom
{
public:
	RoomMansionBase();
	RoomMansionBase(RoomManager* OwnerRef);

	virtual void Render() override;


protected:
	sf::Sprite darkBackground;
};