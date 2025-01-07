#pragma once

#include "Room/BaseRoom.h"

class RoomBeachDecide : public BaseRoom
{
public:
	RoomBeachDecide();
	RoomBeachDecide(RoomManager* OwnerRef);

	void init(std::string filePath) override;
	void Start() override;
	void Update() override;
	void Render() override;
};