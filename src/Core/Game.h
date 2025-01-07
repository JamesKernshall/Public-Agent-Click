#pragma once


#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include "GameState/DebugState.h"
#include "GameState/GamePlay.h"
#include "GameState/GameWin.h"
#include "GameState/Menu.h"
#include "GameState/Pause.h"

class Game
{
public:
	Game(sf::RenderWindow& window);
	~Game();
	bool init();
	void start();
	void update(float dt);
	void render();
	void mouseClicked(sf::Event event);
	void keyPressed(sf::Event event);
	void keyReleased(sf::Event event);

private:
	sf::RenderWindow& window;

	// Game States
	GamePlay state_gameplay;
	Menu state_menu;
	Pause state_pause;
	DebugState state_Debug;
	GameWin state_GameWin;
};

#endif // PLATFORMER_GAME_H