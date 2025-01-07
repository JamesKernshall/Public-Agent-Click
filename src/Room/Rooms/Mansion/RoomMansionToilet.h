#pragma once

#include "RoomMansionBase.h"

class RoomMansionToilet : public RoomMansionBase
{
public:
	RoomMansionToilet();
	RoomMansionToilet(RoomManager* OwnerRef);

	void init(std::string filePath) override;
	void Start() override;
	void Update() override;
	void Render() override;
};