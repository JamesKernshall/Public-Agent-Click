#pragma once

#include "Room/BaseRoom.h"
#include "GameObjects/AnimatedGameObject.h"

class RoomBeachDocks : public BaseRoom
{
public:
	RoomBeachDocks();
	RoomBeachDocks(RoomManager* OwnerRef);

	void init(std::string filePath) override;
	void Start() override;
	void Update() override;
	void Render() override;

	AnimatedGameObject animated_background;
};