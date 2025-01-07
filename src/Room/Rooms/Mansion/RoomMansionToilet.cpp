#include "RoomMansionToilet.h"
#include "GameObjects/Interactable/RoomTransitionInteractable.h"
#include "GameObjects/Interactable/ItemAudioInteractable.h"

RoomMansionToilet::RoomMansionToilet()
{

}

RoomMansionToilet::RoomMansionToilet(RoomManager* OwnerRef) : RoomMansionBase(OwnerRef)
{
}


void RoomMansionToilet::init(std::string filePath)
{
	__super::init(filePath);
	//Setup any additional spawners with RegisterSpawnerDirection
	//North is included by default

	AddBackground("Data/Rooms/Backgrounds/MansionToiletLight_Background.png");
	GameObject::CreateSprite(darkBackground, "Data/Rooms/Backgrounds/MansionToiletDark_Background.png");
	DepthTexture.loadFromFile("Data/Rooms/Backgrounds/MansionToilet_DepthMap.png");

	std::shared_ptr<RoomTransitionInteractable> backTrack = std::make_shared<RoomTransitionInteractable>("back", this);

	backTrack->CreateSprite("Data/EmptyBorder.png");
	backTrack->AssignRoomTransitionName("Mansion", PlayerRoomSpawner::North);
	backTrack->isActive = false;
	interactables.push_back(backTrack);

	std::shared_ptr<ItemAudioInteractable> bucket = std::make_shared<ItemAudioInteractable>("Bucket", this);
	bucket->CreateSprite("Data/Items/Bucket.png");
	bucket->item = Item_Type::BUCKET;
	bucket->AttachAudio("Data/Audio/InteractBucket.mp3");
	bucket->SetCorrectItem(Item_Type::EMPTY, false, false);
	interactables.push_back(bucket);

	std::shared_ptr<AudioInteractable> sink = std::make_shared<AudioInteractable>("Sink", this);
	sink->CreateSprite("Data/EmptyBorder.png");
	sink->isActive = false;
	sink->AttachAudio("Data/Audio/InteractSink.mp3");
	sink->AttachFailAudio(Item_Type::BUCKET, "Data/Audio/InteractSink.mp3");
	sink->AttachFailAudio(Item_Type::BUCKET_WATER, "Data/Audio/WaterBucketSink.mp3");
	interactables.push_back(sink);

}

void RoomMansionToilet::Start()
{
	__super::Start();
}

void RoomMansionToilet::Update()
{
	__super::Update();
}

void RoomMansionToilet::Render()
{
	__super::Render();
}