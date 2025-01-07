#pragma once


#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H

#include <math.h>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class GameObject
{
public:
    GameObject();
    ~GameObject();

    enum TouchingEdge
    {
        None = 0,
        Top,
        Bottom,
        Left,
        Right
    };

    static bool CheckInteract(GameObject& gameObject, sf::Vector2f MousePosition);
    static bool IsInside(GameObject& gameObject1, GameObject& gameObject2);
    static bool IsTouchingEdge(GameObject& gameObject, TouchingEdge& out);
    static bool IsWithinBounds(GameObject& gameObject, sf::Vector2u screenSize);
    static bool IsWithinBounds(sf::Vector2f& position, sf::Vector2u screenSize);

    virtual void CreateSprite(std::string fileName);
    static void CreateSprite(sf::Sprite& sprite, std::string fileName);
    static sf::Vector2f NormaliseVector(sf::Vector2f vector2F);
    static float VectorMagnitude(sf::Vector2f vector2F);

    std::shared_ptr<sf::Sprite> sprite;
    bool isActive = true;
};


#endif // SPACEINVADERS_GAMEOBJECT_H