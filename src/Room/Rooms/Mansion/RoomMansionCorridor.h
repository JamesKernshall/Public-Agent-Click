#pragma once

#include "RoomMansionBase.h"

class RoomMansionCorridor : public RoomMansionBase
{
public:
	RoomMansionCorridor();
	RoomMansionCorridor(RoomManager* OwnerRef);

	void init(std::string filePath) override;
	void Start() override;
	void Update() override;
	void Render() override;
};