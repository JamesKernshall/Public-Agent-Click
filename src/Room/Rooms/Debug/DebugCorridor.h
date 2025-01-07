#pragma once

#include "Room/BaseRoom.h"

class DebugCorridor : public BaseRoom
{
public:
	DebugCorridor();
	DebugCorridor(RoomManager* OwnerRef);

	void init(std::string filePath) override;
	void Start() override;
	void Update() override;
	void Render() override;

};