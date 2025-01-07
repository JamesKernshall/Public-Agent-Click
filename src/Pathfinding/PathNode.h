#pragma once
#include "SFML/Graphics/Transform.hpp"
#include "list"


class PathNode
{
public:
	PathNode(sf::Vector2u pos);

public:
	PathNode* parent = nullptr;
	sf::Vector2u pixel;
	float g;
	float h;
	float f;

	bool operator==(const PathNode& rhs) const noexcept
	{
		return this->pixel == rhs.pixel; // for example
	}


	static bool HasItem(std::list<PathNode> nodeList, PathNode item);
	static bool HasItemAndLowerHeuristic(std::list<PathNode> nodeList, PathNode item, float itemG);
};