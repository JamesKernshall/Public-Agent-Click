#pragma once

#include <SFML/Window/Event.hpp>
#include "Core/Data.h"

#ifndef PLATFORMERSFML_GAMESTATECLASS_H
#define PLATFORMERSFML_GAMESTATECLASS_H

class GameStateClass
{
 public:
	 virtual bool init() abstract;
	 virtual void start() abstract;
	 virtual void update(float dt) abstract;
	 virtual void render() abstract;
	 virtual void keyPressed(sf::Event event) abstract;
	 virtual void keyReleased(sf::Event event) abstract; 
	 virtual void mousePressed(sf::Event event) {};

};

#endif // PLATFORMERSFML_GAMESTATECLASS_H
