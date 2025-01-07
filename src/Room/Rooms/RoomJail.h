#pragma once

#include "Room/BaseRoom.h"

class RoomJail : public BaseRoom
{
public:
	RoomJail();
	RoomJail(RoomManager* OwnerRef);

	void init(std::string filePath) override;
	void Start() override;
	void Update() override;
	void Render() override;

};