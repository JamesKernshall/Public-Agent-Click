#pragma once

#include "Core/Data.h"
#include "GameObjects/Interactable/InteractableBase.h"
#include "PlayerRoomSpawner.h"

class RoomManager;

class BaseRoom
{
public:
	BaseRoom();
	BaseRoom(RoomManager* OwnerRef);
	~BaseRoom();

public:

	virtual void init(std::string filePath);
	virtual void Start();
	virtual void Update();
	virtual void Render();

public:
	sf::Vector2u ConvertWorldToDepthPixelPosition(sf::Vector2f world_pos);
	sf::Vector2f ConvertDepthPixelToWorldPosition(sf::Vector2u pixel_pos);
	static sf::Vector2u ConvertWorldToDepthPixelPosition(sf::Vector2f world_pos, sf::Vector2u depth_size);
	static sf::Vector2f ConvertDepthPixelToWorldPosition(sf::Vector2u pixel_pos, sf::Vector2u depth_size);

	std::vector<InteractableBase*> GetInteractables();
	std::vector<PlayerRoomSpawner*> GetSpawners();
	void AddBackground(std::string fileName);
	void AddForeground(std::string fileName);

	//Editor Stuff
	void EditorTintBackground(bool EditorEnabled);
	sf::Vector2i GenerateInteractPosition(EditorInteractable* interactable);

protected:
	void RegisterSpawnerDirection(PlayerRoomSpawner::Direction dir);

private:
	// Visuals
	std::list<sf::Sprite> backgrounds;
	std::list<sf::Sprite> foregrounds;

public:
	//Depth Texture
	sf::Image DepthTexture;

private:
	// SFXs
	sf::SoundBuffer sfx;

public:
	// Functionality
	RoomManager* Owner;
	std::vector<std::shared_ptr<InteractableBase>> interactables;
	std::string jsonFilePath;
	std::map<PlayerRoomSpawner::Direction, std::unique_ptr<PlayerRoomSpawner>> spawners;
};