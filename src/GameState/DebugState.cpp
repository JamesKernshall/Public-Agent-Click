#include "DebugState.h"
#include "GameObjects/Interactable/AudioInteractable.h"


bool DebugState::init()
{
	//Cursors Loading
	generic_cursor_tex.loadFromFile("Data/Cursors/Cursor.png");
	interact_cursor_tex.loadFromFile("Data/Cursors/CursorInteract.png");

	generic_cursor.loadFromPixels(generic_cursor_tex.getPixelsPtr(), generic_cursor_tex.getSize(), sf::Vector2u(generic_cursor_tex.getSize().x /  2, generic_cursor_tex.getSize().y / 2));

	interact_cursor.loadFromPixels(interact_cursor_tex.getPixelsPtr(), interact_cursor_tex.getSize(), sf::Vector2u(interact_cursor_tex.getSize().x /  2, interact_cursor_tex.getSize().y / 2));
	
	player = std::make_unique<Player>();
	randomItem1.CreateSprite("Data/Debug/devArtMichi.png");
	randomItem2.CreateSprite("Data/Items/Keycard.png");

	inventory = std::make_unique<Inventory>();
	
	inventory->AddItem(*randomItem1.sprite, Item_Type::SCREWDRIVER);

	room_manager = std::make_unique<RoomManager>(player.get());

	return false;
}

void DebugState::start()
{
	Data::GetInstance()->window->setMouseCursor(generic_cursor);
	room_manager->Start();
	player->Start();
	room_manager->ScalePlayer(player.get());
}

void DebugState::update(float dt)
{
	room_manager->Update();
	player->Update();
	inventory->Update();
	if (player->IsPlayerMoving())
	{
		room_manager->ScalePlayer(player.get());
	}

	sf::Vector2f mouse_pos = Data::GetInstance()->window->mapPixelToCoords(sf::Mouse::getPosition(*Data::GetInstance()->window));
	//std::cout << mouse_pos.x << " " << mouse_pos.y << "\n";


	bool anyInteractions = false;
	std::vector<InteractableBase*> roomInteractables = room_manager->current_room->GetInteractables();
	for (InteractableBase* BasicInteractable : roomInteractables)
	{
		if (BasicInteractable->CheckInteract(mouse_pos))
		{
			anyInteractions = true;
			break;
		}

	}


	if (anyInteractions) 
	{
		Data::GetInstance()->window->setMouseCursor(interact_cursor);
	}
	else
	{
		Data::GetInstance()->window->setMouseCursor(generic_cursor);
	}
}

void DebugState::render()
{
	room_manager->Render(EditorMode);
	player->Render();
	inventory->Render();
}

void DebugState::keyPressed(sf::Event event)
{
	if (event.key.code == sf::Keyboard::F5)
	{
		EditorMode = !EditorMode;
		room_manager->current_room->EditorTintBackground(EditorMode);
	}

	if (EditorMode)
	{
		if (editorSelected != nullptr)
		{
			EditorKeyPreciseMoveObjects(event);
		}
	}
}

void DebugState::keyReleased(sf::Event event)
{
	
}

void DebugState::mousePressed(sf::Event event)
{

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (EditorMode)
		{
			EditorMousePlaceObjects(event);
		}
		//Disable Game Input if in Editor Mode
		else if (event.mouseButton.button == sf::Mouse::Left)
		{
			OnMouseClick(event);
		}
	}
}

void DebugState::OnMouseClick(sf::Event event)
{
	ClickCheckMovement(event);
}

void DebugState::ClickCheckMovement(sf::Event event)
{
	sf::Vector2f mouse_pos = Data::GetInstance()->window->mapPixelToCoords(sf::Mouse::getPosition(*Data::GetInstance()->window));

	if (!GameObject::IsWithinBounds(mouse_pos, Data::WindowGetSize()))
	{
		return;
	}

	if (inventory->sprite->getGlobalBounds().contains(mouse_pos))
	{
		inventory->OnMouseClick();
		return;
	}


	std::vector<InteractableBase*> roomInteractables = room_manager->current_room->GetInteractables();
	for (InteractableBase* BasicInteractable : roomInteractables)
	{
		if (BasicInteractable->CheckInteract(mouse_pos))
		{
			player->SetMovementTarget(room_manager->current_room->ConvertWorldToDepthPixelPosition(player->sprite->getPosition()), 
				BasicInteractable->interact_from_pos, 
				room_manager->current_depth(),
				std::bind(&InteractableBase::OnInteract, BasicInteractable, inventory.get()));
			inventory->DeselectHeldItem();
			return;
		}
	}

	sf::Vector2u pixelPosition = room_manager->current_room->ConvertWorldToDepthPixelPosition(mouse_pos);
	
	sf::Color color = room_manager->current_room->DepthTexture.getPixel(pixelPosition.x, pixelPosition.y);

	if (color.a > 0)
	{
		player->SetMovementTarget(room_manager->current_room->ConvertWorldToDepthPixelPosition(player->sprite->getPosition()), pixelPosition, room_manager->current_depth());
	}
}
void DebugState::EditorKeyPreciseMoveObjects(sf::Event event)
{
	// Position Movements
	if (event.key.code == sf::Keyboard::Right)
	{
		editorSelected->sprite->move(sf::Vector2f(1, 0));
	}
	else if (event.key.code == sf::Keyboard::Left)
	{
		editorSelected->sprite->move(sf::Vector2f(-1, 0));
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		editorSelected->sprite->move(sf::Vector2f(0, 1));
	}
	else if (event.key.code == sf::Keyboard::Up)
	{
		editorSelected->sprite->move(sf::Vector2f(0, -1));
	}

	// Rotation Movements
	else if (event.key.code == sf::Keyboard::Comma)
	{
		editorSelected->sprite->rotate(-1);
	}
	else if (event.key.code == sf::Keyboard::Period)
	{
		editorSelected->sprite->rotate(1);
	}

	// Scale Movements
	else if (event.key.code == sf::Keyboard::W)
	{
		sf::Vector2f scale = editorSelected->sprite->getScale() + sf::Vector2f(0, -0.01);
		editorSelected->sprite->setScale(scale);
	}
	else if (event.key.code == sf::Keyboard::S)
	{
		sf::Vector2f scale = editorSelected->sprite->getScale() + sf::Vector2f(0, 0.01);
		editorSelected->sprite->setScale(scale);
	}
	else if (event.key.code == sf::Keyboard::A)
	{
		sf::Vector2f scale = editorSelected->sprite->getScale() + sf::Vector2f(-0.01, 0);
		editorSelected->sprite->setScale(scale);
	}
	else if (event.key.code == sf::Keyboard::D)
	{
		sf::Vector2f scale = editorSelected->sprite->getScale() + sf::Vector2f(0.01, 0);
		editorSelected->sprite->setScale(scale);
	}

	//editorSelected->interact_from_pos = static_cast<sf::Vector2u>(room_manager->current_room->GenerateInteractPosition(editorSelected));
	

	// Saving
	if (event.key.control && event.key.code == sf::Keyboard::S)
	{
		std::cout << "Saving..." << std::endl;
		room_manager->SaveCurrentRoom();
	}
}

void DebugState::EditorMousePlaceObjects(sf::Event event)
{
	sf::Vector2f mouse_pos = Data::GetInstance()->window->mapPixelToCoords(sf::Mouse::getPosition(*Data::GetInstance()->window));


	if (event.mouseButton.button == sf::Mouse::Left)
	{
		bool newEditorSelected = false;
		std::vector<InteractableBase*> roomInteractables = room_manager->current_room->GetInteractables();
		for (InteractableBase* BasicInteractable : roomInteractables)
		{
			if (BasicInteractable->CheckInteract(mouse_pos))
			{
				if (editorSelected != BasicInteractable)
				{
					//Deselect previous selected
					if (editorSelected != nullptr)
					{
						editorSelected->sprite->setColor(sf::Color::White);
					}
					editorSelected = BasicInteractable;
					editorSelected->sprite->setColor(sf::Color(120, 120, 120, 160));

					debugPlaceLeftClick = sf::Vector2f();
					debugPlaceRightClick = sf::Vector2f();
					return;
				}
			}
		}

		std::vector<PlayerRoomSpawner*> spawners = room_manager->current_room->GetSpawners();
		for (PlayerRoomSpawner* spawn : spawners)
		{
			if (GameObject::CheckInteract(*spawn, mouse_pos))
			{
				if (editorSelected != spawn)
				{
					//Deselect previous selected
					if (editorSelected != nullptr)
					{
						editorSelected->sprite->setColor(sf::Color::White);
					}
					editorSelected = spawn;
					editorSelected->sprite->setColor(sf::Color(120, 120, 120, 160));

					debugPlaceLeftClick = sf::Vector2f();
					debugPlaceRightClick = sf::Vector2f();
					return;
				}
			}
		}

		if (!newEditorSelected)
			debugPlaceLeftClick = mouse_pos;
	}
	else if (event.mouseButton.button == sf::Mouse::Right)
	{
		debugPlaceRightClick = mouse_pos;
	}
	else if (event.mouseButton.button == sf::Mouse::Middle)
	{
		if (editorSelected != nullptr)
		{
			editorSelected->interact_from_pos = room_manager->current_room->ConvertWorldToDepthPixelPosition(mouse_pos);
		}
	}


	if (debugPlaceLeftClick != sf::Vector2f() && debugPlaceRightClick != sf::Vector2f())
	{

		if (editorSelected != nullptr)
		{
			//calculate scale required
			sf::Vector2f totalObjectSize = debugPlaceRightClick - debugPlaceLeftClick;

			sf::Vector2f objectScaledSize = sf::Vector2f(totalObjectSize.x / editorSelected->sprite->getLocalBounds().width, totalObjectSize.y / editorSelected->sprite->getLocalBounds().height);


			editorSelected->sprite->setPosition(debugPlaceLeftClick);
			editorSelected->sprite->setScale(objectScaledSize);

			editorSelected->interact_from_pos = static_cast<sf::Vector2u>(room_manager->current_room->GenerateInteractPosition(editorSelected));
		}


		debugPlaceLeftClick = sf::Vector2f();
		debugPlaceRightClick = sf::Vector2f();
	}
}