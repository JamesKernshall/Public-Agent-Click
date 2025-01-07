#pragma once

#include "GameStateClass.h"
#include "GameObjects/Interactable/EditorInteractable.h"
#include "GameObjects/Player.h"
#include "GameObjects/Inventory.h"
#include <SFML/Window/Cursor.hpp>
#include "Room/RoomManager.h"

class GamePlay : public GameStateClass
{
public:
	virtual bool init() override;
	virtual void start() override;
	virtual void update(float dt) override;
	virtual void render() override;
	virtual void keyPressed(sf::Event event) override;
	virtual void keyReleased(sf::Event event) override;
	virtual void mousePressed(sf::Event event) override;

private:
	std::unique_ptr<Player> player;
	std::unique_ptr<Inventory> inventory;

private:
	sf::Image generic_cursor_tex, interact_cursor_tex;
	sf::Cursor generic_cursor;
	sf::Cursor interact_cursor;
	sf::Music background_music;

	void OnMouseClick(sf::Event event);

	std::unique_ptr<RoomManager> room_manager;


	//Editor Stuff
	void EditorMousePlaceObjects(sf::Event event);
	void EditorKeyPreciseMoveObjects(sf::Event event);
	sf::Vector2f debugPlaceLeftClick, debugPlaceRightClick;
	EditorInteractable* editorSelected = nullptr;

	bool EditorMode = false;

};
