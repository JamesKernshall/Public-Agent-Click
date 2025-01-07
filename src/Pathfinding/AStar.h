#pragma once
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Transform.hpp"
#include "PathNode.h"
#include "list"

class AStar
{
public:
	static std::list<sf::Vector2u> find_path(sf::Vector2u start_pixel, sf::Vector2u end_pixel, sf::Image* image);

private:
	static float calculate_heuristic(sf::Vector2i startNode, sf::Vector2i endNode);
	static void TryAddPixel(sf::Vector2i pixel, sf::Image* image, std::list<PathNode>* list);
	static std::list<PathNode> AddNewNeighbourPixels(sf::Vector2i pixel, sf::Image* image);
};