#include "Inventory.h"
#include "Interactable/ItemDB.h"
#include "Core/Data.h"
#include "Core/DeltaTime.h"

Inventory::Inventory() : GameObject()
{
	init();
}

void Inventory::init()
{
	CreateSprite("Data/UI/InventoryBackDrop.png");
	targetY = Data::WindowGetSize().y - 30;
	oldTargetY = targetY;
	sprite->setPosition(0, targetY);

	GameObject::CreateSprite(enter_sprite, "Data/UI/InventoryArrow.png");
	enter_sprite_offset_pos = sf::Vector2f(524, 5);

	GameObject::CreateSprite(exit_sprite, "Data/UI/InventoryCross.png");
	exit_sprite_offset_pos = sf::Vector2f(524, 8);
}

void Inventory::Update()
{
	sf::Vector2f mouse_pos = Data::GetInstance()->GetRelativeMousePosition();


	// Handling Open/Close detection
	if (!open)
	{
		if (mouse_pos.y > Data::WindowGetSize().y - 30 &&
			mouse_pos.x > Data::WindowGetSize().x / 2 - Data::WindowGetSize().x / 10 &&
			mouse_pos.x < Data::WindowGetSize().x / 2 + Data::WindowGetSize().x / 10)
		{
			open = true;
			oldTargetY = targetY;
			current_time = 0;
			targetY = Data::WindowGetSize().y - 122;
		}
	}
	else
	{
		if (mouse_pos.y < Data::WindowGetSize().y - 102)
		{
			open = false;
			oldTargetY = targetY;
			current_time = 0;
			targetY = Data::WindowGetSize().y - 30;
		}
	}
	if (current_time < 1)
	{
		sprite->setPosition(0, Data::Lerp(oldTargetY, targetY, current_time));
		current_time += Time::DeltaTime() * popupSpeedMultipler;
	}
}

void Inventory::Render()
{
	Data::RenderGameObject(*this);
	if (open)
	{
		exit_sprite.setPosition(sprite->getPosition() + exit_sprite_offset_pos);
		Data::RenderGameObject(exit_sprite);

	}
	else
	{
		enter_sprite.setPosition(sprite->getPosition() + enter_sprite_offset_pos);
		Data::RenderGameObject(enter_sprite);
	}

	if (open || current_time < 1)
	{
		sf::Vector2f item_pos = sf::Vector2f(30, sprite->getPosition().y + sprite->getGlobalBounds().getSize().y - 82);
		for (int i = 0; i < items.size(); i++)
		{
			if (i == currently_held_number)
			{
				continue;
			}
			items[i]->sprite->setPosition(item_pos);
			Data::RenderGameObject(*items[i]);
			item_pos.x += 72;
		}
	}

	if (currently_held_item != nullptr)
	{
		currently_held_item->sprite->setPosition(Data::GetInstance()->GetRelativeMousePosition() + grab_offset);
		Data::RenderGameObject(*currently_held_item);
	}
}

void Inventory::OnMouseClick()
{
	sf::Vector2f mouse_pos = Data::GetInstance()->GetRelativeMousePosition();
	if (currently_held_item != nullptr)
	{
		DeselectHeldItem();
		return;
	}

	for (int i = 0; i < items.size(); i++)
	{
		if (items[i]->sprite->getGlobalBounds().contains(mouse_pos))
		{
			currently_held_item = items[i].get();
			currently_held_number = i;
			grab_offset = currently_held_item->sprite->getPosition() - mouse_pos;
			break;
		}
	}
}

void Inventory::AddItem(sf::Sprite& ref, Item_Type type)
{
	sf::Sprite* sprite = items.emplace_back(std::make_shared<Item>(type))->sprite.get();

	sprite->setTexture(*ref.getTexture());

	float finalScaleFactor;
	{
		float scaleX = 72 / sprite->getGlobalBounds().getSize().x;
		float scaleY = 72 / sprite->getGlobalBounds().getSize().y;

		if (scaleX < scaleY)
		{
			finalScaleFactor = scaleX;
		}
		else
		{
			finalScaleFactor = scaleY;
		}

	}
	sprite->setScale(finalScaleFactor, finalScaleFactor);
}

Item_Type Inventory::GetHeldItemType()
{
	if (currently_held_item != nullptr)
	{
		return currently_held_item->item_type;
	}

	return Item_Type::EMPTY;
}

void Inventory::DeselectHeldItem()
{
	currently_held_item = nullptr;
	currently_held_number = -1;
}

void Inventory::RemoveHeldItem()
{
	if (currently_held_item != nullptr)
	{
		//std::vector<Item>::iterator iterator = std::find(items.begin(), items.end(), *currently_held_item);
		//std::remove(items.begin(), items.end(), *currently_held_item);
		items.erase(items.begin() + currently_held_number);
		//items.erase(items.begin(), std::find(items.begin(), items.end(), *currently_held_item));
		//items.pop_back();
		DeselectHeldItem();
	}
}
