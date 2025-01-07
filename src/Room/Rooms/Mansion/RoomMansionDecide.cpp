#include "RoomMansionDecide.h"
#include "GameObjects/Interactable/RoomTransitionInteractable.h"

RoomMansionDecide::RoomMansionDecide()
{

}

RoomMansionDecide::RoomMansionDecide(RoomManager* OwnerRef) : RoomMansionBase(OwnerRef)
{
}


void RoomMansionDecide::init(std::string filePath)
{
	__super::init(filePath);
	//Setup any additional spawners with RegisterSpawnerDirection
	//North is included by default

	AddBackground("Data/Rooms/Backgrounds/MansionDecideLight_Background.png");
	GameObject::CreateSprite(darkBackground, "Data/Rooms/Backgrounds/MansionDecideDark_Background.png");
	DepthTexture.loadFromFile("Data/Rooms/Backgrounds/MansionDecide_DepthMap.png");
	RegisterSpawnerDirection(PlayerRoomSpawner::South);
	RegisterSpawnerDirection(PlayerRoomSpawner::East);
	RegisterSpawnerDirection(PlayerRoomSpawner::West);

	std::shared_ptr<RoomTransitionInteractable> backTrack = std::make_shared<RoomTransitionInteractable>("back", this);

	backTrack->CreateSprite("Data/EmptyBorder.png");
	backTrack->AssignRoomTransitionName("BeachMansion", PlayerRoomSpawner::North);
	backTrack->isActive = false;
	interactables.push_back(backTrack);

	std::shared_ptr<RoomTransitionInteractable> toilet = std::make_shared<RoomTransitionInteractable>("toilet", this);

	toilet->CreateSprite("Data/EmptyBorder.png");
	toilet->AssignRoomTransitionName("MansionToilet", PlayerRoomSpawner::North);
	toilet->isActive = false;
	interactables.push_back(toilet);


	std::shared_ptr<RoomTransitionInteractable> corridor = std::make_shared<RoomTransitionInteractable>("corridor", this);

	corridor->CreateSprite("Data/EmptyBorder.png");
	corridor->AssignRoomTransitionName("MansionCorridor", PlayerRoomSpawner::South);
	corridor->isActive = false;
	interactables.push_back(corridor);


	std::shared_ptr<RoomTransitionInteractable> garage = std::make_shared<RoomTransitionInteractable>("garage", this);

	garage->CreateSprite("Data/EmptyBorder.png");
	garage->AssignRoomTransitionName("MansionGarage", PlayerRoomSpawner::North);
	garage->isActive = false;
	interactables.push_back(garage);




}

void RoomMansionDecide::Start()
{
	__super::Start();
}

void RoomMansionDecide::Update()
{
	__super::Update();
}

void RoomMansionDecide::Render()
{
	__super::Render();
}
