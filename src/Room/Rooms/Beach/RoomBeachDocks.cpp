#include "RoomBeachDocks.h"
#include "GameObjects/Interactable/RoomTransitionInteractable.h"
#include "GameObjects/Interactable/ItemAudioInteractable.h"
#include "Core/DeltaTime.h"

RoomBeachDocks::RoomBeachDocks()
{
	
}

RoomBeachDocks::RoomBeachDocks(RoomManager* OwnerRef) : BaseRoom(OwnerRef)
{
}


void RoomBeachDocks::init(std::string filePath)
{
	__super::init(filePath);
	//Setup any additional spawners with RegisterSpawnerDirection
	//North is included by default

	//AddBackground("Data/Rooms/Backgrounds/BeachDocks_Background.png");
	AddForeground("Data/Rooms/Backgrounds/BeachDocks_Foreground.png");

	animated_background.SetupAnimatedSprite("Data/Rooms/Backgrounds/BeachDocksSeaSprite_sheet.png", sf::Vector2i(216, 144), 1);
	animated_background.SetFrameRate(5);
	DepthTexture.loadFromFile("Data/Rooms/Backgrounds/BeachDocks_DepthMap.png");

	std::shared_ptr<RoomTransitionInteractable> backTrack = std::make_shared<RoomTransitionInteractable>("back", this);

	backTrack->CreateSprite("Data/EmptyBorder.png");
	backTrack->AssignRoomTransitionName("BeachDecide", PlayerRoomSpawner::East);
	backTrack->isActive = false;
	interactables.push_back(backTrack);

	std::shared_ptr<AudioInteractable> background = std::make_shared<AudioInteractable>("background", this);
	background->AttachAudio("Data/Audio/InteractBackground.mp3");
	background->CreateSprite("Data/EmptyBorder.png");
	background->isActive = false;
	interactables.push_back(background);

	std::shared_ptr<ItemAudioInteractable> key = std::make_shared<ItemAudioInteractable>("key", this);
	key->CreateSprite("Data/Items/Keycard.png");
	key->item = Item_Type::KEY;
	key->AttachFailAudio(Item_Type::EMPTY, "Data/Audio/InteractKeyCard.mp3");
	key->AttachFailAudio(Item_Type::ROCK, "Data/Audio/RockKeyCard.mp3");
	key->AttachFailAudio(Item_Type::SCREWDRIVER, "Data/Audio/ScrewDriverKeyCard.mp3");
	key->AttachAudio("Data/Audio/ShardKeyCard.mp3");
	key->SetCorrectItem(Item_Type::GLASS, true, false);
	interactables.push_back(key);

	std::shared_ptr<ItemAudioInteractable> water = std::make_shared<ItemAudioInteractable>("water", this);
	water->CreateSprite("Data/Items/Bucket_water.png");
	water->isActive = false;
	water->AttachFailAudio(Item_Type::EMPTY, "Data/Audio/InteractOcean.mp3");
	water->AttachFailAudio(Item_Type::ROCK, "Data/Audio/RockOcean.mp3");
	water->AttachAudio("Data/Audio/BucketWater.mp3");
	water->item = Item_Type::BUCKET_WATER;
	water->SetCorrectItem(Item_Type::BUCKET, true);
	interactables.push_back(water);
}

void RoomBeachDocks::Start()
{
	__super::Start();
}

void RoomBeachDocks::Update()
{
	__super::Update();
	animated_background.Animate(Time::DeltaTime());
}

void RoomBeachDocks::Render()
{
	Data::RenderBackground(animated_background.sprite);
	__super::Render();
}
