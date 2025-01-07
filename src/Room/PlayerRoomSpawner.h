#pragma once

#include "Core/Data.h"
#include "GameObjects/Interactable/EditorInteractable.h"

class PlayerRoomSpawner : public EditorInteractable
{
public:
	enum Direction
	{
		North = 0,
		East = 1,
		South = 2,
		West = 3
	};

public:
	
	PlayerRoomSpawner(Direction dir);

	void init();
	void LoadPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();
	void render();
	Direction direction;

private:

	void SetDirectionText();

private:
	sf::Text text;
};