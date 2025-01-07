#pragma once

#include "Room/BaseRoom.h"

class DebugRoom : public BaseRoom
{
public:
	DebugRoom();
	DebugRoom(RoomManager* OwnerRef);
	~DebugRoom();

public:

	void init(std::string filePath) override;
	void Start() override;
	void Update() override;
	void Render() override;


private:
	sf::Texture texture;
	sf::Sprite depthsprite;

};