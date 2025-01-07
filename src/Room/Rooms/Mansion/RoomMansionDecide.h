#pragma once

#include "Room/Rooms/Mansion/RoomMansionBase.h"

class RoomMansionDecide : public RoomMansionBase
{
public:
	RoomMansionDecide();
	RoomMansionDecide(RoomManager* OwnerRef);

	void init(std::string filePath) override;
	void Start() override;
	void Update() override;
	void Render() override;
};