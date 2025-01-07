#include "BaseRoom.h"
#include "Pathfinding/FindClosestPixel.h"

BaseRoom::BaseRoom()
{
}

BaseRoom::BaseRoom(RoomManager* OwnerRef)
{
	Owner = OwnerRef;
}

BaseRoom::~BaseRoom()
{
}

void BaseRoom::init(std::string filePath)
{
	jsonFilePath = filePath;
	
	RegisterSpawnerDirection(PlayerRoomSpawner::North);
}

void BaseRoom::Start()
{
	for (int i = 0; i < interactables.size(); i++)
	{
		interactables[i]->Start();
	}
}

void BaseRoom::Update()
{
	for (int i = 0; i < interactables.size(); i++)
	{
		interactables[i]->Update();
	}
}

void BaseRoom::Render()
{
	for (sf::Sprite& BG : backgrounds)
	{
		Data::RenderBackground(BG);
	}

	for (int i = 0; i < interactables.size(); i++)
	{
		interactables[i]->Render();
	}

	for (sf::Sprite& FG : foregrounds)
	{
		Data::RenderBackground(FG);
	}
}

sf::Vector2u BaseRoom::ConvertWorldToDepthPixelPosition(sf::Vector2f world_pos)
{
	return ConvertWorldToDepthPixelPosition(world_pos, DepthTexture.getSize());
}

sf::Vector2f BaseRoom::ConvertDepthPixelToWorldPosition(sf::Vector2u pixel_pos)
{
	return ConvertDepthPixelToWorldPosition(pixel_pos, DepthTexture.getSize());
}

sf::Vector2u BaseRoom::ConvertWorldToDepthPixelPosition(sf::Vector2f world_pos, sf::Vector2u depth_size)
{
	sf::Vector2f scale = sf::Vector2f(
		Data::WindowGetSize().x / depth_size.x,
		Data::WindowGetSize().y / depth_size.y);
	return  sf::Vector2u(world_pos.x / scale.x, world_pos.y / scale.y);
}

sf::Vector2f BaseRoom::ConvertDepthPixelToWorldPosition(sf::Vector2u pixel_pos, sf::Vector2u depth_size)
{
	sf::Vector2f scale = sf::Vector2f(
		Data::WindowGetSize().x / depth_size.x,
		Data::WindowGetSize().y / depth_size.y);
	return  sf::Vector2f(pixel_pos.x * scale.x, pixel_pos.y * scale.y);
}

std::vector<InteractableBase*> BaseRoom::GetInteractables()
{
	std::vector<InteractableBase*> interactablePointers;
	
	for(int i = 0; i < interactables.size(); i++)
	{
		interactablePointers.push_back(interactables[i].get());
	}

	return interactablePointers;
}

std::vector<PlayerRoomSpawner*> BaseRoom::GetSpawners()
{
	std::vector<PlayerRoomSpawner*> playerSpawners;
	for(auto& spawner : spawners)
	{
		playerSpawners.push_back(spawner.second.get());
	}

	return playerSpawners;
}

void BaseRoom::AddBackground(std::string fileName)
{
	sf::Sprite bg = sf::Sprite();
	GameObject::CreateSprite(bg, fileName);
	backgrounds.push_back(bg);
}

void BaseRoom::AddForeground(std::string fileName)
{
	sf::Sprite bg = sf::Sprite();
	GameObject::CreateSprite(bg, fileName);
	foregrounds.push_back(bg);
}

void BaseRoom::EditorTintBackground(bool EditorEnabled)
{
	for (auto& background : backgrounds)
	{
		if (EditorEnabled)
			background.setColor(sf::Color(100, 100, 100));
		else
			background.setColor(sf::Color::White);
	}
}

sf::Vector2i BaseRoom::GenerateInteractPosition(EditorInteractable* interactable)
{
	//Get pixel point of the middle of the interactable
	sf::Vector2u center_pixel_pos = ConvertWorldToDepthPixelPosition((interactable->sprite->getGlobalBounds().getPosition() + sf::Vector2f(
		interactable->sprite->getGlobalBounds().getSize().x / 2,
		interactable->sprite->getGlobalBounds().getSize().y / 2)));

	FindClosestPixel pathPixel = FindClosestPixel(&DepthTexture);

	return pathPixel.ClosetPixel(center_pixel_pos);
}

void BaseRoom::RegisterSpawnerDirection(PlayerRoomSpawner::Direction dir)
{
	spawners.emplace(dir, std::make_unique<PlayerRoomSpawner>(dir));
}
