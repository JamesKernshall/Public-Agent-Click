#pragma once

#include "RoomMansionBase.h"

class RoomMansionGarage : public RoomMansionBase
{
public:
	RoomMansionGarage();
	RoomMansionGarage(RoomManager* OwnerRef);

	void init(std::string filePath) override;
	void Start() override;
	void Update() override;
	void Render() override;
};