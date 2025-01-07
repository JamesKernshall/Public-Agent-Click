#pragma once

#include "Room/BaseRoom.h"

class RoomBeachMansion : public BaseRoom
{
public:
	RoomBeachMansion();
	RoomBeachMansion(RoomManager* OwnerRef);

	void init(std::string filePath) override;
	void Start() override;
	void Update() override;
	void Render() override;
};