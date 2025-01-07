#include "PlayerRoomSpawner.h"

PlayerRoomSpawner::PlayerRoomSpawner(Direction dir) : EditorInteractable()
{
	direction = dir;
	init();
}

void PlayerRoomSpawner::init()
{
	sprite->setTexture(Data::GetInstance()->LoadTexture("Data/Cursors/EditorSpawn.png"));
	text.setFont(Data::GetInstance()->LoadFont("Data/Fonts/OpenSans-Bold.ttf"));
	SetDirectionText();
}

void PlayerRoomSpawner::LoadPosition(sf::Vector2f position)
{
	sprite->setPosition(position);
}

sf::Vector2f PlayerRoomSpawner::GetPosition()
{
	return sprite->getPosition();
}

void PlayerRoomSpawner::render()
{
	Data::RenderGameObject(*sprite);
	text.setPosition(sf::Vector2f(sprite->getPosition().x + sprite->getGlobalBounds().width / 2, sprite->getPosition().y + sprite->getGlobalBounds().height / 2));
	Data::GetInstance()->window->draw(text);
}

void PlayerRoomSpawner::SetDirectionText()
{
	switch (direction)
	{
	case PlayerRoomSpawner::North:
		text.setString("N");
		break;
	case PlayerRoomSpawner::East:
		text.setString("E");
		break;
	case PlayerRoomSpawner::South:
		text.setString("S");
		break;
	case PlayerRoomSpawner::West:
		text.setString("W");
		break;
	default:
		break;
	}
}
