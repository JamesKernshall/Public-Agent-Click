#pragma once

#include "GameObject.h"
#include "Item.h"

class Inventory : public GameObject
{
public:
	Inventory();

	void init();

	void Update();
	void Render();
	void OnMouseClick();

	void AddItem(sf::Sprite& ref, Item_Type type);

	Item_Type GetHeldItemType();
	void DeselectHeldItem();
	void RemoveHeldItem();


private:
	//Icons
	sf::Vector2f enter_sprite_offset_pos, exit_sprite_offset_pos;
	sf::Sprite enter_sprite, exit_sprite;

	//Popup calculation variables
	const float popupSpeedMultipler = 3;

	float targetY = 0;
	float oldTargetY = targetY;
	float current_time = 0;

	bool open = false;
	std::vector<std::shared_ptr<Item>> items;

	sf::Vector2f grab_offset = sf::Vector2f(0, 0);
	Item* currently_held_item = nullptr;
	int currently_held_number = -1;
};