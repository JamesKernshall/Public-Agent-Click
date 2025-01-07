#pragma once

#include "GameObjects/GameObject.h"

class EditorInteractable : public GameObject
{
public:
	EditorInteractable();

	sf::Vector2u interact_from_pos;
};