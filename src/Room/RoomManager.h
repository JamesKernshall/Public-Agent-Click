#pragma once

#include "BaseRoom.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
using json = nlohmann::json;

class Player;

class RoomManager
{
public:

	RoomManager(Player* player);


	void init();
	void Start();
	void Update();
	void Render(bool editor);


	//Getters
	sf::Image* current_depth();

	//Statics
	static void LoadRoomData(BaseRoom* baseRoom, std::string fileLocation);
	static void SaveRoomData(BaseRoom* baseRoom, std::string fileLocation);

	//Functions
	void ScalePlayer(Player* player);
	void LoadCurrentRoom();
	void SaveCurrentRoom();

	void LoadNewRoom(std::string room_name, PlayerRoomSpawner::Direction direction = PlayerRoomSpawner::North);
	
private:
	static sf::Vector2f TryLoadVector(json vectorJson);

	void OnEnterNewRoom(PlayerRoomSpawner::Direction direction);

public:
	//Public Variables
	BaseRoom* current_room;
	std::map<std::string,std::unique_ptr<BaseRoom>> rooms;


private:
	class Player* player;

};