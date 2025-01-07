#include "RoomManager.h"
#include "GameObjects/Player.h"

// ALL Rooms
#include "Rooms/RoomJail.h"

#include "Rooms/Beach/RoomBeach.h"
#include "Rooms/Beach/RoomBeachDecide.h"
#include "Rooms/Beach/RoomBeachDocks.h"
#include "Rooms/Beach/RoomBeachMansion.h"

#include "Rooms/Mansion/RoomMansionCorridor.h"
#include "Rooms/Mansion/RoomMansionDecide.h"
#include "Rooms/Mansion/RoomMansionDining.h"
#include "Rooms/Mansion/RoomMansionGarage.h"
#include "Rooms/Mansion/RoomMansionToilet.h"

//Debug Rooms UNUSED
#include "Rooms/Debug/DebugCorridor.h"
#include "Rooms/Debug/DebugRoom.h"

RoomManager::RoomManager(Player* play)
{
	player = play;
	init();
}

void RoomManager::init()
{
	//Spawn ALL rooms

	rooms.emplace("Jail", std::make_unique<RoomJail>(this));
	rooms["Jail"]->init("Data/Rooms/JailTutorial.json");

	rooms.emplace("Beach", std::make_unique<RoomBeach>(this));
	rooms["Beach"]->init("Data/Rooms/Beach.json");

	rooms.emplace("BeachDecide", std::make_unique<RoomBeachDecide>(this));
	rooms["BeachDecide"]->init("Data/Rooms/BeachDecide.json");

	rooms.emplace("Docks", std::make_unique<RoomBeachDocks>(this));
	rooms["Docks"]->init("Data/Rooms/BeachDocks.json");

	rooms.emplace("BeachMansion", std::make_unique<RoomBeachMansion>(this));
	rooms["BeachMansion"]->init("Data/Rooms/BeachMansion.json");

	rooms.emplace("Mansion", std::make_unique<RoomMansionDecide>(this));
	rooms["Mansion"]->init("Data/Rooms/MansionDecide.json");

	rooms.emplace("MansionCorridor", std::make_unique<RoomMansionCorridor>(this));
	rooms["MansionCorridor"]->init("Data/Rooms/MansionCorridor.json");

	rooms.emplace("MansionDining", std::make_unique<RoomMansionDining>(this));
	rooms["MansionDining"]->init("Data/Rooms/MansionDining.json");

	rooms.emplace("MansionGarage", std::make_unique<RoomMansionGarage>(this));
	rooms["MansionGarage"]->init("Data/Rooms/MansionGarage.json");

	rooms.emplace("MansionToilet", std::make_unique<RoomMansionToilet>(this));
	rooms["MansionToilet"]->init("Data/Rooms/MansionToilet.json");

	rooms.emplace("Debug_Corridor", std::make_unique<DebugCorridor>(this));
	rooms["Debug_Corridor"]->init("Data/Rooms/DebugRoom.json");

	rooms.emplace("Debug_Room", std::make_unique<DebugRoom>(this));
	rooms["Debug_Room"]->init("Data/Rooms/DebugCorridor_DepthMap.png");

	Data::GetInstance()->generic_item_fail.loadFromFile("Data/Audio/GenericFail.mp3");
}

void RoomManager::Start()
{	
	LoadNewRoom("Jail");
	//LoadNewRoom("Mansion");
}

void RoomManager::Update()
{
	current_room->Update();
}

void RoomManager::Render(bool editor)
{
	current_room->Render();

	if (editor)
	{
		for(auto& spawn : current_room->spawners)
		{
			spawn.second->render();
		}

		std::vector<InteractableBase*> interactables = current_room->GetInteractables();
		for (InteractableBase* interactable : interactables)
		{
			if (interactable->isActive == false)
			{
				Data::RenderGameObject(*interactable->sprite);

				sf::Text debugText = sf::Text(interactable->name, Data::GetInstance()->LoadFont("Data/Fonts/OpenSans-Bold.ttf"));
				debugText.setPosition(interactable->sprite->getPosition());
				Data::GetInstance()->window->draw(debugText);
			}
		}
	}
}

sf::Image* RoomManager::current_depth()
{
	return &current_room->DepthTexture;
}

void RoomManager::LoadRoomData(BaseRoom* baseRoom, std::string fileLocation)
{
	std::string jsonParsed;
	{
		// Create and open a text file
		std::ifstream LoadJson(fileLocation);

		jsonParsed = { std::istreambuf_iterator<char>(LoadJson), std::istreambuf_iterator<char>() };

		// Close the file
		LoadJson.close();
	}

	json Doc;
	try
	{
		Doc = { json::parse(jsonParsed) };
	}
	catch (json::parse_error e)
	{
		std::cout << "Bad Json File at " << fileLocation << std::endl;
		std::cout << e.what() << std::endl;
		return;
	}


	//Parse list into dictionary Map to ensure objects are correctly mapped
	std::map<std::string, InteractableBase*> roomInteractableTable;
	{
		std::vector<InteractableBase*> roomInteractables = baseRoom->GetInteractables();
		for (int i = 0; i < roomInteractables.size(); i++)
		{
			roomInteractableTable.emplace(roomInteractables[i]->name, roomInteractables[i]);
		}
	}

	for (auto const& interactableLookUp : roomInteractableTable)
	{
		json data = Doc[interactableLookUp.first];

		interactableLookUp.second->sprite->setPosition(TryLoadVector(data["Position"]));
		interactableLookUp.second->sprite->setScale(TryLoadVector(data["Scale"]));

		if (data["Rotation"] != nullptr)
		{
			interactableLookUp.second->sprite->setRotation(std::stof(data["Rotation"].get<std::string>()));
		}

		interactableLookUp.second->interact_from_pos = static_cast<sf::Vector2u>(TryLoadVector(data["InteractPosition"]));

		//Error Checking
		if (interactableLookUp.second->interact_from_pos == sf::Vector2u(0,0))
		{
			std::cout << "Interactable " << interactableLookUp.second->name << " is missing an interact position, Please Middle click to set!\n";
		}
	}


	for(auto& spawnerLookup : baseRoom->spawners)
	{
		json vectorPosition = Doc["Spawner" + spawnerLookup.first]["Position"];
		if (vectorPosition[0] == nullptr)
		{
			continue;
		}
		spawnerLookup.second->LoadPosition(sf::Vector2f(std::stof(vectorPosition[0].get<std::string>()), std::stof(vectorPosition[1].get<std::string>())));
	}


}

void RoomManager::SaveRoomData(BaseRoom* baseRoom, std::string fileLocation)
{
	json Doc;

	std::vector<InteractableBase*> interactables = baseRoom->GetInteractables();

	for (int i = 0; i < interactables.size(); i++)
	{
		Doc[interactables[i]->name]["Position"][0] = std::to_string(interactables[i]->sprite->getPosition().x);
		Doc[interactables[i]->name]["Position"][1] = std::to_string(interactables[i]->sprite->getPosition().y);

		Doc[interactables[i]->name]["Rotation"] = std::to_string(interactables[i]->sprite->getRotation());

		Doc[interactables[i]->name]["Scale"][0] = std::to_string(interactables[i]->sprite->getScale().x);
		Doc[interactables[i]->name]["Scale"][1] = std::to_string(interactables[i]->sprite->getScale().y);

		Doc[interactables[i]->name]["InteractPosition"][0] = std::to_string(interactables[i]->interact_from_pos.x);
		Doc[interactables[i]->name]["InteractPosition"][1] = std::to_string(interactables[i]->interact_from_pos.y);
	}

	std::vector<PlayerRoomSpawner*> spawners = baseRoom->GetSpawners();

	for (int i = 0; i < spawners.size(); i++)
	{
		Doc["Spawner" + spawners[i]->direction]["Position"][0] = std::to_string(spawners[i]->GetPosition().x);
		Doc["Spawner" + spawners[i]->direction]["Position"][1] = std::to_string(spawners[i]->GetPosition().y);
	}

	// Create and open a text file
	std::ofstream SaveJson(fileLocation);

	// Write to the file
	SaveJson << Doc.dump(2);

	// Close the file
	SaveJson.close();
}

void RoomManager::ScalePlayer(Player* player)
{
	sf::Vector2f world_position = player->sprite->getPosition();

	sf::Vector2u pixelPosition = current_room->ConvertWorldToDepthPixelPosition(world_position);

	sf::Color color = current_room->DepthTexture.getPixel(pixelPosition.x, pixelPosition.y);

	if (color.a > 0)
	{
		float totalFloat;
		std::memcpy(&totalFloat, &color, sizeof(color));

		player->AdjustScale(totalFloat);
	}

}

void RoomManager::LoadCurrentRoom()
{
	LoadRoomData(current_room, current_room->jsonFilePath);
}

void RoomManager::SaveCurrentRoom()
{
	SaveRoomData(current_room, current_room->jsonFilePath);
}

void RoomManager::LoadNewRoom(std::string room_name, PlayerRoomSpawner::Direction direction)
{
	current_room = rooms[room_name].get();
	OnEnterNewRoom(direction);
}

sf::Vector2f RoomManager::TryLoadVector(json vectorJson)
{
	if (vectorJson == nullptr || vectorJson[0] == nullptr || vectorJson[1] == nullptr)
	{
		return sf::Vector2f(1,1);
	}

	return sf::Vector2f(std::stof(vectorJson[0].get<std::string>()), std::stof(vectorJson[1].get<std::string>()));
}

void RoomManager::OnEnterNewRoom(PlayerRoomSpawner::Direction direction)
{
	LoadCurrentRoom();
	sf::Vector2f playerPos;
	if (current_room->spawners.contains(direction))
	{
		playerPos = current_room->spawners[direction]->GetPosition();
	}
	else
	{
		playerPos = current_room->spawners[PlayerRoomSpawner::Direction::North]->GetPosition();
	}
	
	//Sets player position and depth scales
	player->EnterRoom(playerPos, current_depth()->getSize());
	ScalePlayer(player);
	current_room->Start();
}
