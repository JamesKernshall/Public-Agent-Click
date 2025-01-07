#pragma once

#include "RoomMansionBase.h"
#include "GameObjects/AnimatedGameObject.h"

class RoomMansionDining : public RoomMansionBase
{
public:
	RoomMansionDining();
	RoomMansionDining(RoomManager* OwnerRef);

	void init(std::string filePath) override;
	void Start() override;
	void Update() override;
	void Render() override;

	bool TryExtinguish();

	bool isLit = true;
private:
	AnimatedGameObject fire;
};