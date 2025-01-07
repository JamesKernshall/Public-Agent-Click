#include "Core/Data.h"
#include "GameObject.h"

// === STATIC FUNCTIONS ===


float GameObject::VectorMagnitude(sf::Vector2f vector2F)
{
    return std::sqrt(std::pow(vector2F.x, 2) + std::pow(vector2F.y, 2));
}

sf::Vector2f GameObject::NormaliseVector(sf::Vector2f vector2F)
{
    return sf::Vector2f(vector2F.x / GameObject::VectorMagnitude(vector2F), vector2F.y / GameObject::VectorMagnitude(vector2F));
}

bool GameObject::CheckInteract(GameObject& gameObject, sf::Vector2f MousePosition)
{
    return (gameObject.sprite->getGlobalBounds().contains(MousePosition));
}

bool GameObject::IsInside(GameObject& gameObject1, GameObject& gameObject2)
{
    if (!gameObject1.isActive || !gameObject2.isActive)
    {
        return false;
    }

    sf::Vector2f gameObject1TopLeftPos = sf::Vector2f(gameObject1.sprite->getPosition().x - gameObject1.sprite->getOrigin().x,
        gameObject1.sprite->getPosition().y - gameObject1.sprite->getOrigin().y);

    sf::Vector2f gameObject2TopLeftPos = sf::Vector2f(gameObject2.sprite->getPosition().x - gameObject2.sprite->getOrigin().x,
        gameObject2.sprite->getPosition().y - gameObject2.sprite->getOrigin().y);


    bool collisionX = (gameObject1TopLeftPos.x + gameObject1.sprite->getGlobalBounds().width >= gameObject2TopLeftPos.x
        && gameObject2TopLeftPos.x + gameObject2.sprite->getGlobalBounds().width >= gameObject1TopLeftPos.x);
    bool collisionY = (gameObject1TopLeftPos.y + gameObject1.sprite->getGlobalBounds().height >= gameObject2TopLeftPos.y
        && gameObject2TopLeftPos.y + gameObject2.sprite->getGlobalBounds().height >= gameObject1TopLeftPos.y);
    return collisionX && collisionY;
}


bool GameObject::IsTouchingEdge(GameObject& gameObject, GameObject::TouchingEdge& out)
{
    sf::Vector2f screenSize = static_cast<sf::Vector2f>(Data::WindowGetSize());

    sf::Vector2f pos = gameObject.sprite->getPosition();
    float width = gameObject.sprite->getGlobalBounds().width;
    float height = gameObject.sprite->getGlobalBounds().height;
    if (pos.x < 0) // Over Left
    {
        out = TouchingEdge::Left;
        return true;
    }
    else if (pos.x + width > screenSize.x) // Over Right
    {
        out = TouchingEdge::Right;
        return true;
    }


    // Disabled Y Input to allow ships to go above edge
    else if (pos.y < 0) // Touching Top
    {
        out = TouchingEdge::Top;
        return true;
    }
    else if (pos.y + height > screenSize.y) // Touching bottom
    {
        out = TouchingEdge::Bottom;
        return true;
    }

    else
    {
        out = TouchingEdge::None;
        return false;
    }
}
bool GameObject::IsWithinBounds(GameObject& gameObject, sf::Vector2u screenSize)
{
    sf::Vector2f pos = gameObject.sprite->getPosition();
    float width = gameObject.sprite->getGlobalBounds().width;
    float height = gameObject.sprite->getGlobalBounds().height;
    if (pos.x + width < 0) // Over Left
    {
        return false;
    }
    else if (pos.x > screenSize.x) // Over Right
    {
        return false;
    }
    else if (pos.y + height < 0) // Touching Top
    {
        return false;
    }
    else if (pos.y > screenSize.y) // Touching bottom
    {
        return false;
    }
    else
        return true;
}

bool GameObject::IsWithinBounds(sf::Vector2f& position, sf::Vector2u screenSize)
{
    if (position.x < 0) // Over Left
    {
        return false;
    }
    else if (position.x > screenSize.x) // Over Right
    {
        return false;
    }
    else if (position.y < 0) // Touching Top
    {
        return false;
    }
    else if (position.y > screenSize.y) // Touching bottom
    {
        return false;
    }
    else
        return true;
}


// === NON STATIC FUNCTIONS ===

GameObject::GameObject()
{
    sprite = std::make_shared<sf::Sprite>();
}

void GameObject::CreateSprite(sf::Sprite& sprite, std::string fileName)
{
    if (fileName.length() == 0)
        return;
    if (Data::GetInstance()->textureMemory.count(fileName) == 0)
    {
        //Create New Sprite
        sf::Texture sprite_Texture;

        if (!sprite_Texture.loadFromFile(fileName))
        {
            std::cout << "ERROR: " << fileName << " could not be loaded!";
            sprite_Texture.loadFromFile("Data/Images/ballBlue.png");
        }
        else
        {
            Data::GetInstance()->textureMemory[fileName] = sprite_Texture;
        }
    }

    sprite.setTexture(Data::GetInstance()->textureMemory[fileName]);
}

void GameObject::CreateSprite(std::string fileName)
{
    if (Data::GetInstance()->textureMemory.count(fileName) == 0)
    {
        //Create New Sprite
        sf::Texture sprite_Texture;

        if (!sprite_Texture.loadFromFile(fileName))
        {
            std::cout << "ERROR: " << fileName << " could not be loaded!";
            sprite_Texture.loadFromFile("Data/Images/Alien UFO pack/PNG/laserPink3.png");
        }
        else
        {
            Data::GetInstance()->textureMemory[fileName] = sprite_Texture;
        }
    }

    this->sprite->setTexture(Data::GetInstance()->textureMemory[fileName]);
}



GameObject::~GameObject()
{
    
}