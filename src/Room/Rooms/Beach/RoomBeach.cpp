#include "RoomBeach.h"
#include "GameObjects/Interactable/RoomTransitionInteractable.h"
#include "GameObjects/Interactable/ItemAudioInteractable.h"

RoomBeach::RoomBeach()
{
	
}

RoomBeach::RoomBeach(RoomManager* OwnerRef) : BaseRoom(OwnerRef)
{
}


void RoomBeach::init(std::string filePath)
{
	__super::init(filePath);
	//Setup any additional spawners with RegisterSpawnerDirection
	//North is included by default

	AddBackground("Data/Rooms/Backgrounds/BeachVent_Background.png");
	DepthTexture.loadFromFile("Data/Rooms/Backgrounds/BeachVent_DepthMap.png");
	RegisterSpawnerDirection(PlayerRoomSpawner::East);

	std::shared_ptr<RoomTransitionInteractable> vent = std::make_shared<RoomTransitionInteractable>("Vent", this);

	vent->CreateSprite("Data/EmptyBorder.png");
	vent->AssignRoomTransitionName("Jail", PlayerRoomSpawner::South);
	vent->isActive = false;
	interactables.push_back(vent);

	std::shared_ptr<RoomTransitionInteractable> open_area = std::make_shared<RoomTransitionInteractable>("open_area", this);

	open_area->CreateSprite("Data/EmptyBorder.png");
	open_area->AssignRoomTransitionName("BeachDecide", PlayerRoomSpawner::South);
	open_area->isActive = false;
	interactables.push_back(open_area);


	std::shared_ptr<ItemAudioInteractable> rock = std::make_shared<ItemAudioInteractable>("rock", this);
	rock->CreateSprite("Data/Items/Rock.png");
	rock->item = Item_Type::ROCK;
	rock->AttachAudio("Data/Audio/InteractRock.mp3");
	rock->SetCorrectItem(Item_Type::EMPTY, false, false);
	interactables.push_back(rock);

}

void RoomBeach::Start()
{
	__super::Start();
}

void RoomBeach::Update()
{
	__super::Update();
}

void RoomBeach::Render()
{
	__super::Render();
}
