#pragma once

#ifndef SPACEINVADERSSFML_DATA_H
#define SPACEINVADERSSFML_DATA_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <functional>
#include <iostream>

class GameObject;
class GamePlay;

class Data
{

 public:

  enum GAMESTATE
  {
    Menu,
    Gameplay,
    Paused,
    Debug,
    Winner
  };

  std::function<void()> OnGameStateSwitch;

  static Data* GetInstance();

  Data();
  ~Data();

  GAMESTATE gamestate = GAMESTATE::Gameplay;
  sf::RenderWindow* window;

  sf::Texture& LoadTexture(std::string fileName);
  sf::Font& LoadFont(std::string fileName);


  /// <summary>
  /// Get's the current mouse position in relation with the screen
  /// </summary>
  /// <returns></returns>
  sf::Vector2f GetRelativeMousePosition();

  static float Lerp(float a, float b, float t);
  static void SetUpDefaultText(sf::Text& textObj, std::string text, sf::Color color, sf::Font& font);
  static void SetUpAudio(sf::Sound& sourceObj, sf::SoundBuffer& soundObj, std::string fileName);
  static sf::Vector2u WindowGetSize();
  static int RandomNext(int minNumber, int maxNumber = 0);
  static float RandomNext(float minNumber, float maxNumber);
  static std::string ConvertSecondsToTime(float time);
  static void RenderGameObject(GameObject& gameObject);
  static void RenderGameObject(sf::Sprite& gameObject);
  static void RenderBackground(GameObject& gameObject);
  static void RenderBackground(sf::Sprite& sprite);
  static float ConvertToRadians(float angle);
  static float ConvertToAngle(float Radians);



  std::map<std::string, sf::Texture> textureMemory;
  std::map<std::string, sf::Font> fontMemory;

  bool mansion_power = true;

  sf::SoundBuffer generic_item_fail;
  sf::Sound DialogueSource;

 private:
  void RenderLocalGameObject(GameObject& gameObject);
  void RenderLocalSprite(sf::Sprite& sprite);
  void RenderLocalBackground(GameObject& gameObject);
  void RenderLocalBackground(sf::Sprite& sprite);
};

#endif // SPACEINVADERSSFML_DATA_H
