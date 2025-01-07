#include "RoomBeachMansion.h"
#include "GameObjects/Interactable/RoomTransitionInteractable.h"
#include "GameObjects/Interactable/ItemAudioInteractable.h"

RoomBeachMansion::RoomBeachMansion()
{
	
}

RoomBeachMansion::RoomBeachMansion(RoomManager* OwnerRef) : BaseRoom(OwnerRef)
{
}


void RoomBeachMansion::init(std::string filePath)
{
	__super::init(filePath);
	//Setup any additional spawners with RegisterSpawnerDirection
	//North is included by default

	AddBackground("Data/Rooms/Backgrounds/BeachMansion_Background.png");
	DepthTexture.loadFromFile("Data/Rooms/Backgrounds/BeachMansion_DepthMap.png");
	RegisterSpawnerDirection(PlayerRoomSpawner::South);

	std::shared_ptr<RoomTransitionInteractable> backTrack = std::make_shared<RoomTransitionInteractable>("back", this);

	backTrack->CreateSprite("Data/EmptyBorder.png");
	backTrack->AssignRoomTransitionName("BeachDecide", PlayerRoomSpawner::North);
	backTrack->isActive = false;
	interactables.push_back(backTrack);

	std::shared_ptr<RoomTransitionInteractable> mansion = std::make_shared<RoomTransitionInteractable>("mansion", this);

	mansion->CreateSprite("Data/EmptyBorder.png");
	mansion->AssignRoomTransitionName("Mansion", PlayerRoomSpawner::South);
	mansion->AttachFailAudio(Item_Type::EMPTY, "Data/Audio/InteractDoor.mp3");
	mansion->AttachFailAudio(Item_Type::ROCK, "Data/Audio/RockDoor.mp3");
	mansion->SetCorrectItem(Item_Type::KEY, false, false);
	mansion->isActive = false;
	interactables.push_back(mansion);

	std::shared_ptr<ItemAudioInteractable> glass = std::make_shared<ItemAudioInteractable>("glass", this);
	glass->CreateSprite("Data/Items/Glass Shard.png");
	glass->isActive = false;
	glass->AttachFailAudio(Item_Type::EMPTY, "Data/Audio/InteractGlass.mp3");
	glass->AttachAudio("Data/Audio/RockGlass.wav");
	glass->SetCorrectItem(Item_Type::ROCK, true);
	glass->item = Item_Type::GLASS;
	interactables.push_back(glass);



}

void RoomBeachMansion::Start()
{
	__super::Start();
}

void RoomBeachMansion::Update()
{
	__super::Update();
}

void RoomBeachMansion::Render()
{
	__super::Render();
}
