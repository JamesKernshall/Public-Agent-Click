#include "DebugCorridor.h"

#include "GameObjects/Interactable/AudioInteractable.h"
#include "GameObjects/Interactable/RoomTransitionInteractable.h"

DebugCorridor::DebugCorridor() : BaseRoom()
{
}

DebugCorridor::DebugCorridor(RoomManager* OwnerRef) : BaseRoom(OwnerRef)
{
}

void DebugCorridor::init(std::string filePath)
{
	__super::init(filePath);

	RegisterSpawnerDirection(PlayerRoomSpawner::South);

	AddBackground("Data/Debug/DebugCorridor_Background.png");
	DepthTexture.loadFromFile("Data/Debug/DebugCorridor_DepthMap.png");

	std::shared_ptr<AudioInteractable> BasicInteractable = std::make_shared<AudioInteractable>("DevArtMichi", this);

	BasicInteractable->CreateSprite("Data/Debug/devArtMichi.png");
	BasicInteractable->AttachAudio("Data/Debug/message.mp3");

	interactables.push_back(BasicInteractable);

	std::shared_ptr<AudioInteractable> VentInteractable = std::make_shared<AudioInteractable>("DebugHollow", this);

	VentInteractable->CreateSprite("Data/EmptyBorder.png");
	VentInteractable->AttachAudio("Data/Debug/message.mp3");

	interactables.push_back(VentInteractable);


	std::shared_ptr<RoomTransitionInteractable> roomTransition = std::make_shared<RoomTransitionInteractable>("DebugTransition", this);
	roomTransition->CreateSprite("Data/EmptyBorder.png");
	roomTransition->AssignRoomTransitionName("Debug_Room", PlayerRoomSpawner::North);
	interactables.push_back(roomTransition);

}

void DebugCorridor::Start()
{
	__super::Start();
}

void DebugCorridor::Update()
{
	__super::Update();
}

void DebugCorridor::Render()
{
	__super::Render();
}
