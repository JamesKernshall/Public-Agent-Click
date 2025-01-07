#pragma once

#ifndef PLATFORMERSFML_PAUSE_H
#define PLATFORMERSFML_PAUSE_H

#include "GameStateClass.h"
class Pause : public GameStateClass
{
 public:
  bool init() override;
  void start() override;
  void update(float dt) override;
  void render() override;
  void keyPressed(sf::Event event) override;
  void keyReleased(sf::Event event) override;
};

#endif // PLATFORMERSFML_PAUSE_H
