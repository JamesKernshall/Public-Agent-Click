#pragma once


#ifndef PLATFORMERSFML_GAMEWIN_H
#define PLATFORMERSFML_GAMEWIN_H

#include "GameStateClass.h"
#include "GameObjects/AnimatedGameObject.h"

class GameWin : public GameStateClass
{
 public:
  bool init() override;
  void start() override;
  void update(float dt) override;
  void render() override;
  void keyPressed(sf::Event event) override;
  void keyReleased(sf::Event event) override;

 private:

	AnimatedGameObject animated_background;
	sf::Cursor fix_cursor;
};

#endif // PLATFORMERSFML_GAMEWIN_H
