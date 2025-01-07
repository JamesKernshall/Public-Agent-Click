#include "RoomMansionDining.h"
#include "GameObjects/Interactable/RoomTransitionInteractable.h"
#include "GameObjects/Interactable/FirePlaceInteractable.h"
#include "Core/DeltaTime.h"

RoomMansionDining::RoomMansionDining()
{

}

RoomMansionDining::RoomMansionDining(RoomManager* OwnerRef) : RoomMansionBase(OwnerRef)
{
}


void RoomMansionDining::init(std::string filePath)
{
	__super::init(filePath);
	//Setup any additional spawners with RegisterSpawnerDirection
	//North is included by default

	AddBackground("Data/Rooms/Backgrounds/MansionDiningLight_Background.png");
	GameObject::CreateSprite(darkBackground, "Data/Rooms/Backgrounds/MansionDiningDark_Background.png");
	DepthTexture.loadFromFile("Data/Rooms/Backgrounds/MansionDining_DepthMap.png");

	std::shared_ptr<RoomTransitionInteractable> backTrack = std::make_shared<RoomTransitionInteractable>("back", this);

	backTrack->CreateSprite("Data/EmptyBorder.png");
	backTrack->AssignRoomTransitionName("MansionCorridor", PlayerRoomSpawner::North);
	backTrack->isActive = false;
	interactables.push_back(backTrack);

	fire.SetupAnimatedSprite("Data/Items/Campfire.png", sf::Vector2i(32, 32));
	fire.sprite.setPosition(sf::Vector2f(376, 362));
	fire.sprite.setScale(3, 3);

	std::shared_ptr<FirePlaceInteractable> fireplace = std::make_shared<FirePlaceInteractable>("fireplace", this);
	fireplace->CreateSprite("Data/Items/Bucket.png");
	fireplace->isActive = false;
	fireplace->AttachFailAudio(Item_Type::BUCKET, "Data/Audio/BucketFire.mp3");
	fireplace->AttachFailAudio(Item_Type::KEY, "Data/Audio/KeyCardFire.mp3");
	fireplace->AttachFailAudio(Item_Type::SCREWDRIVER, "Data/Audio/ScrewDriverFire.mp3");
	fireplace->AttachFailAudio(Item_Type::EMPTY, "Data/Audio/InteractFire.mp3");
	fireplace->failWaterBucket.loadFromFile("Data/Audio/WaterBucketFireFail.mp3");
	fireplace->successWaterBucket.loadFromFile("Data/Audio/WaterBucketFireSuccess.mp3");
	fireplace->SetCorrectItem(Item_Type::BUCKET_WATER, true);
	fireplace->item = Item_Type::BUCKET;
	interactables.push_back(fireplace);
}

void RoomMansionDining::Start()
{
	__super::Start();
}

void RoomMansionDining::Update()
{
	__super::Update();
	fire.Animate(Time::DeltaTime());
}

void RoomMansionDining::Render()
{
	__super::Render();
	if (isLit)
	{
		Data::RenderGameObject(fire.sprite);
	}
}

bool RoomMansionDining::TryExtinguish()
{
	if(!Data::GetInstance()->mansion_power)
	{
		isLit = false;
		return true;
	}
	return false;
}
