#include "Core/Data.h"
#include "GameObjects/GameObject.h"
#include <iomanip>
#include <sstream>

static Data* instance;

#define PI 3.1415965359f

Data* Data::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Data();
    }

    return instance;
}

Data::Data()
{
  textureMemory = std::map<std::string, sf::Texture>();
}


Data::~Data()
{
  for (auto var : textureMemory)
  {
    //delete(var.second);
  }
}

sf::Vector2f Data::GetRelativeMousePosition()
{
    return window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

float Data::Lerp(float a, float b, float t)
{
  return a + t * (b - a);
}

sf::Texture& Data::LoadTexture(std::string fileName)
{
  if (textureMemory.count(fileName) == 0)
  {
    //Create New Sprite
    sf::Texture sprite_Texture;

    if (!sprite_Texture.loadFromFile(fileName))
    {
      std::cout << "ERROR: " << fileName << " could not be loaded!\n";
      sprite_Texture.loadFromFile("Data/Images/Alien UFO pack/PNG/laserPink3.png\n");
    }
    else
    {
      textureMemory[fileName] = sprite_Texture;
    }
  }

  return textureMemory[fileName];
}

sf::Font& Data::LoadFont(std::string fileName)
{
    if (fontMemory.count(fileName) == 0)
    {
        //Create New Sprite
        sf::Font font;

        if (!font.loadFromFile(fileName))
        {
            std::cout << "ERROR: " << fileName << " could not be loaded!\n";
        }
        else
        {
            fontMemory[fileName] = font;
        }
    }

    return fontMemory[fileName];
}

// ===== Static functions to call instance version =====
void Data::RenderGameObject(GameObject& gameObject)
{
    Data::GetInstance()->RenderLocalGameObject(gameObject);
}

void Data::RenderGameObject(sf::Sprite& gameObject)
{
    Data::GetInstance()->RenderLocalSprite(gameObject);
}

void Data::RenderBackground(GameObject& gameObject)
{
    Data::GetInstance()->RenderLocalBackground(gameObject);
}

void Data::RenderBackground(sf::Sprite& sprite)
{
    Data::GetInstance()->RenderLocalBackground(sprite);
}


float Data::ConvertToRadians(float angle)
{
    return angle * (PI / 180);
}

float Data::ConvertToAngle(float Radians)
{
    return Radians * (180.0 / PI);
}

void Data::RenderLocalSprite(sf::Sprite& sprite)
{
    window->draw(sprite);
}

void Data::RenderLocalBackground(GameObject& gameObject)
{
    if (gameObject.isActive)
    {
        RenderLocalBackground(*gameObject.sprite);
    }
}

void Data::RenderLocalBackground(sf::Sprite& sprite)
{
    sprite.setScale(
        window->getView().getSize().x / sprite.getLocalBounds().width,
        window->getView().getSize().y / sprite.getLocalBounds().height);

    window->draw(sprite);
}

void Data::RenderLocalGameObject(GameObject& gameObject)
{
    if (gameObject.isActive)
    {
        window->draw(*gameObject.sprite);
    }
}

int Data::RandomNext(int minNumber, int maxNumber)
{
  maxNumber -= minNumber;
  return rand() % maxNumber + 1 + minNumber;
}

float Data::RandomNext(float minNumber, float maxNumber)
{
  // Generate a random number between 0 and RAND_MAX
  float random = static_cast<float>(rand()) / RAND_MAX;

  // Scale the random number to fit within the specified range
  return minNumber + random * (maxNumber - minNumber);
}

void Data::SetUpDefaultText(sf::Text& textObj, std::string text, sf::Color color, sf::Font& font)
{
  textObj.setString(text);
  textObj.setFont(font);
  textObj.setFillColor(color);
  textObj.setCharacterSize(48);
}

void Data::SetUpAudio(sf::Sound& sourceObj, sf::SoundBuffer& soundObj, std::string fileName)
{
    if (soundObj.loadFromFile(fileName))
    {
        sourceObj = sf::Sound(soundObj);
    }
}

sf::Vector2u Data::WindowGetSize()
{
    return static_cast<sf::Vector2u>(Data::GetInstance()->window->getView().getSize());
}

std::string Data::ConvertSecondsToTime(float time)
{
  int minutes   = time / 60;
  float seconds = std::fmod(time, 60.0f);

  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << seconds;
  std::string s = stream.str();

  if (seconds < 10)
  {
    s.insert(0, "0");
  }

  return std::to_string(minutes) + ":" + s;
}

