#include "DebugRoom.h"
#include "GameObjects/Interactable/AudioInteractable.h"

DebugRoom::DebugRoom()
{
}

DebugRoom::DebugRoom(RoomManager* OwnerRef) : BaseRoom(OwnerRef)
{
}

DebugRoom::~DebugRoom()
{
}

void DebugRoom::init(std::string filePath)
{
	__super::init(filePath);
	
	AddBackground("Data/Debug/Jail_Background.png");
	DepthTexture.loadFromFile("Data/Debug/Jail_DepthMap.png");

	texture.loadFromImage(DepthTexture);
	depthsprite.setTexture(texture);


	std::shared_ptr<AudioInteractable> BasicInteractable = std::make_shared<AudioInteractable>("DebugMichi", this);

	BasicInteractable->CreateSprite("Data/Debug/devArtMichi.png");
	BasicInteractable->AttachAudio("Data/Debug/message.mp3");

	BasicInteractable->sprite->setPosition(Data::WindowGetSize().x / 2, Data::WindowGetSize().y / 2);

	interactables.push_back(BasicInteractable);

	std::shared_ptr<AudioInteractable> VentInteractable = std::make_shared<AudioInteractable>("DebugVent", this);

	VentInteractable->CreateSprite("Data/EmptyBorder.png");
	VentInteractable->AttachAudio("Data/Debug/message.mp3");

	VentInteractable->sprite->setPosition(367, 85);
	VentInteractable->sprite->setScale(4.125f, 2.59375f);
	VentInteractable->sprite->setRotation(0.5f);
	
	interactables.push_back(VentInteractable);
}

void DebugRoom::Start()
{
	__super::Start();
}

void DebugRoom::Update()
{
	__super::Update();
}

void DebugRoom::Render()
{
	__super::Render();
	Data::RenderGameObject(depthsprite);
}
