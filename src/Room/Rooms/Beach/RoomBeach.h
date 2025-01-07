#pragma once

#include "Room/BaseRoom.h"

class RoomBeach : public BaseRoom
{
public:
	RoomBeach();
	RoomBeach(RoomManager* OwnerRef);

	void init(std::string filePath) override;
	void Start() override;
	void Update() override;
	void Render() override;
};