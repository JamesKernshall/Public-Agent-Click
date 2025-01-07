#include "RoomMansionCorridor.h"
#include "GameObjects/Interactable/RoomTransitionInteractable.h"

RoomMansionCorridor::RoomMansionCorridor()
{

}

RoomMansionCorridor::RoomMansionCorridor(RoomManager* OwnerRef) : RoomMansionBase(OwnerRef)
{
}


void RoomMansionCorridor::init(std::string filePath)
{
	__super::init(filePath);
	//Setup any additional spawners with RegisterSpawnerDirection
	//North is included by default

	AddBackground("Data/Rooms/Backgrounds/MansionCorridorLight_Background.png");
	GameObject::CreateSprite(darkBackground, "Data/Rooms/Backgrounds/MansionCorridorDark_Background.png");
	DepthTexture.loadFromFile("Data/Rooms/Backgrounds/MansionCorridor_DepthMap.png");
	RegisterSpawnerDirection(PlayerRoomSpawner::South);

	std::shared_ptr<RoomTransitionInteractable> backTrack = std::make_shared<RoomTransitionInteractable>("back", this);

	backTrack->CreateSprite("Data/EmptyBorder.png");
	backTrack->AssignRoomTransitionName("Mansion", PlayerRoomSpawner::West);
	backTrack->isActive = false;
	interactables.push_back(backTrack);

	std::shared_ptr<RoomTransitionInteractable> dining = std::make_shared<RoomTransitionInteractable>("dining", this);

	dining->CreateSprite("Data/EmptyBorder.png");
	dining->AssignRoomTransitionName("MansionDining", PlayerRoomSpawner::North);
	dining->isActive = false;
	interactables.push_back(dining);

	std::shared_ptr<AudioInteractable> window = std::make_shared<AudioInteractable>("window", this);
	window->CreateSprite("Data/EmptyBorder.png");
	window->AttachAudio("Data/Audio/InteractWindow.mp3");
	window->isActive = false;
	interactables.push_back(window);


}

void RoomMansionCorridor::Start()
{
	__super::Start();
}

void RoomMansionCorridor::Update()
{
	__super::Update();
}

void RoomMansionCorridor::Render()
{
	__super::Render();
}


