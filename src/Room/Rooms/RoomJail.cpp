#include "RoomJail.h"

#include "GameObjects/Interactable/RoomTransitionInteractable.h"
#include "GameObjects/Interactable/ItemAudioInteractable.h"

RoomJail::RoomJail()
{
}

RoomJail::RoomJail(RoomManager* OwnerRef) : BaseRoom(OwnerRef)
{
}

void RoomJail::init(std::string filePath)
{
	__super::init(filePath);
	//Setup any additional spawners with RegisterSpawnerDirection
	//North is included by default

	AddBackground("Data/Rooms/Backgrounds/Jail_Background.png");
	DepthTexture.loadFromFile("Data/Rooms/Backgrounds/Jail_DepthMap.png");
	RegisterSpawnerDirection(PlayerRoomSpawner::South);

	std::shared_ptr<RoomTransitionInteractable> vent = std::make_shared<RoomTransitionInteractable>("Vent", this);

	vent->CreateSprite("Data/EmptyBorder.png");
	vent->AssignRoomTransitionName("Beach", PlayerRoomSpawner::East);
	vent->SetCorrectItem(Item_Type::SCREWDRIVER, false);
	vent->AttachFailAudio(Item_Type::EMPTY, "Data/Audio/InteractVent.mp3");
	vent->isActive = false;
	interactables.push_back(vent);

	std::shared_ptr<AudioInteractable> actualbars = std::make_shared<AudioInteractable>("actualbars", this);
	actualbars->CreateSprite("Data/EmptyBorder.png");
	actualbars->isActive = false;
	actualbars->AttachAudio("Data/Audio/InteractBars.mp3");
	actualbars->AttachFailAudio(Item_Type::SCREWDRIVER, "Data/Audio/ScrewBars.mp3");
	interactables.push_back(actualbars);


	std::shared_ptr<ItemAudioInteractable> bars = std::make_shared<ItemAudioInteractable>("Bars", this);
	bars->CreateSprite("Data/Items/ScrewDriver.png");
	bars->AttachAudio("Data/Audio/InteractScrewDriver.mp3");
	bars->item = Item_Type::SCREWDRIVER;
	bars->SetCorrectItem(Item_Type::EMPTY, false, false);
	interactables.push_back(bars);

	std::shared_ptr<AudioInteractable> bed = std::make_shared<AudioInteractable>("Bed", this);
	bed->CreateSprite("Data/EmptyBorder.png");
	bed->AttachAudio("Data/Audio/InteractBed.mp3");
	bed->AttachFailAudio(Item_Type::SCREWDRIVER, "Data/Audio/ScrewBed.mp3");
	bed->isActive = false;
	interactables.push_back(bed);

}

void RoomJail::Start()
{
	__super::Start();
}

void RoomJail::Update()
{
	__super::Update();
}

void RoomJail::Render()
{
	__super::Render();
}
