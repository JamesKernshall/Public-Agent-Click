#include "RoomMansionGarage.h"
#include "GameObjects/Interactable/RoomTransitionInteractable.h"
#include "GameObjects/Interactable/PowerInteractable.h"

RoomMansionGarage::RoomMansionGarage()
{

}

RoomMansionGarage::RoomMansionGarage(RoomManager* OwnerRef) : RoomMansionBase(OwnerRef)
{
}


void RoomMansionGarage::init(std::string filePath)
{
	__super::init(filePath);
	//Setup any additional spawners with RegisterSpawnerDirection
	//North is included by default

	AddBackground("Data/Rooms/Backgrounds/MansionGarageLight_Background.png");
	GameObject::CreateSprite(darkBackground, "Data/Rooms/Backgrounds/MansionGarageDark_Background.png");
	DepthTexture.loadFromFile("Data/Rooms/Backgrounds/MansionGarage_DepthMap.png");

	std::shared_ptr<RoomTransitionInteractable> backTrack = std::make_shared<RoomTransitionInteractable>("back", this);

	backTrack->CreateSprite("Data/EmptyBorder.png");
	backTrack->AssignRoomTransitionName("Mansion", PlayerRoomSpawner::East);
	backTrack->isActive = false;
	interactables.push_back(backTrack);

	std::shared_ptr<PowerInteractable> power = std::make_shared<PowerInteractable>("power", this);
	power->CreateSprite("Data/EmptyBorder.png");
	power->AttachAudio("Data/Audio/InteractPower.mp3");
	power->isActive = false;
	interactables.push_back(power);
}

void RoomMansionGarage::Start()
{
	__super::Start();
}

void RoomMansionGarage::Update()
{
	__super::Update();
}

void RoomMansionGarage::Render()
{
	__super::Render();
}
