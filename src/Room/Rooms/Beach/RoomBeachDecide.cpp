#include "RoomBeachDecide.h"
#include "GameObjects/Interactable/RoomTransitionInteractable.h"

RoomBeachDecide::RoomBeachDecide()
{
	
}

RoomBeachDecide::RoomBeachDecide(RoomManager* OwnerRef) : BaseRoom(OwnerRef)
{
}


void RoomBeachDecide::init(std::string filePath)
{
	__super::init(filePath);
	//Setup any additional spawners with RegisterSpawnerDirection
	//North is included by default

	AddBackground("Data/Rooms/Backgrounds/BeachDecide_Background.png");
	DepthTexture.loadFromFile("Data/Rooms/Backgrounds/BeachDecide_DepthMap.png");
	RegisterSpawnerDirection(PlayerRoomSpawner::South);
	RegisterSpawnerDirection(PlayerRoomSpawner::East);

	std::shared_ptr<RoomTransitionInteractable> backTrack = std::make_shared<RoomTransitionInteractable>("back", this);

	backTrack->CreateSprite("Data/EmptyBorder.png");
	backTrack->AssignRoomTransitionName("Beach", PlayerRoomSpawner::North);
	backTrack->isActive = false;
	interactables.push_back(backTrack);

	std::shared_ptr<RoomTransitionInteractable> docks = std::make_shared<RoomTransitionInteractable>("docks", this);

	docks->CreateSprite("Data/EmptyBorder.png");
	docks->AssignRoomTransitionName("Docks", PlayerRoomSpawner::South);
	docks->isActive = false;
	interactables.push_back(docks);

	std::shared_ptr<RoomTransitionInteractable> mansion = std::make_shared<RoomTransitionInteractable>("mansion", this);

	mansion->CreateSprite("Data/EmptyBorder.png");
	mansion->AssignRoomTransitionName("BeachMansion", PlayerRoomSpawner::South);
	mansion->isActive = false;
	interactables.push_back(mansion);

}

void RoomBeachDecide::Start()
{
	__super::Start();
}

void RoomBeachDecide::Update()
{
	__super::Update();
}

void RoomBeachDecide::Render()
{
	__super::Render();
}
