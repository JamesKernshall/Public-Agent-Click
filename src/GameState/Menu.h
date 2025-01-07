#pragma once

#ifndef PLATFORMERSFML_MENU_H
#define PLATFORMERSFML_MENU_H


#include "GameStateClass.h"

class Menu : public GameStateClass
{
public:
	bool init() override;
	void start() override;
	void update(float dt) override;
	void render() override;
	void keyPressed(sf::Event event) override;
	void keyReleased(sf::Event event) override;

private:

};


#endif // PLATFORMERSFML_GAMEOVER_H
