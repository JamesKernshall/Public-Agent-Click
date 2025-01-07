#include "Core/Data.h"
#include "Pause.h"
#include "GameObjects/GameObject.h"

bool Pause::init()
{
  
  return true;
}

void Pause::start()
{

}

void Pause::update(float dt)
{

}


void Pause::render()
{
  
}

void Pause::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Key::Escape)
  {
 
  }
}

void Pause::keyReleased(sf::Event event)
{

}