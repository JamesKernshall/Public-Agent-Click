#include "AStar.h"


std::list<sf::Vector2u> AStar::find_path(sf::Vector2u start_pixel, sf::Vector2u end_pixel, sf::Image* image)
{
	std::list<PathNode> open, closed;


	PathNode startNode = PathNode(start_pixel);
	PathNode endNode = PathNode(end_pixel);

	startNode.g = 0;
	startNode.h = calculate_heuristic(static_cast<sf::Vector2i>(startNode.pixel), static_cast<sf::Vector2i>(endNode.pixel));
	startNode.f = startNode.g + startNode.h;

	open.clear();
	closed.clear();

	open.push_back(startNode);

	PathNode* destinationNode = nullptr;

	while (open.size() > 0)
	{
		PathNode* currentNode = &open.front();
		int currentIndex = 0;
		
		for(PathNode& node : open)
		{
			if (node.f < currentNode->f) 
			{
				currentNode = &node;
			}
		}

		closed.push_back(*currentNode);
		open.remove(*currentNode);
		currentNode = &closed.back();


		if (currentNode->pixel == end_pixel)
		{
			destinationNode = currentNode;
			break;
		}

		std::list<PathNode> neighbours = AddNewNeighbourPixels(sf::Vector2i(static_cast<int>(currentNode->pixel.x), static_cast<int>(currentNode->pixel.y)), image);

		for (PathNode& neigh : neighbours)
		{
			if (! (PathNode::HasItem(closed, neigh)) 
				&& !PathNode::HasItemAndLowerHeuristic(open, neigh, currentNode->g + 1))
			{
				PathNode newNode = neigh;
				newNode.parent = currentNode;
				newNode.g = currentNode->g + 1;
				newNode.h = calculate_heuristic(static_cast<sf::Vector2i>(newNode.pixel), static_cast<sf::Vector2i>(endNode.pixel));
				newNode.f = newNode.g + newNode.h;
				
				open.push_back(newNode);
			}
		}
	}
	
	std::list<sf::Vector2u> finalPath;

	while (destinationNode != nullptr)
	{
		finalPath.push_back(destinationNode->pixel);
		destinationNode = destinationNode->parent;
	}

	finalPath.reverse();
	return finalPath;
}

float AStar::calculate_heuristic(sf::Vector2i startNode, sf::Vector2i endNode)
{	
	return fabs(startNode.x - endNode.x) + fabs(startNode.y - endNode.y);
}

void AStar::TryAddPixel(sf::Vector2i pixel, sf::Image* image, std::list<PathNode>* list)
{
	//Check if valid number on the image
	if ((pixel.x >= 0 && pixel.x < image->getSize().x &&
		pixel.y >= 0 && pixel.y < image->getSize().y))
	{
		if (image->getPixel(pixel.x, pixel.y).a > 0)
		{
			list->push_back(PathNode(static_cast<sf::Vector2u>(pixel)));
		}
	}
}

std::list<PathNode> AStar::AddNewNeighbourPixels(sf::Vector2i pixel, sf::Image* image)
{
	std::list<PathNode> neighbours;
	TryAddPixel(pixel + sf::Vector2i(1, 1), image, &neighbours);
	TryAddPixel(pixel + sf::Vector2i(1, 0), image, &neighbours);
	TryAddPixel(pixel + sf::Vector2i(0, 1), image, &neighbours);
	TryAddPixel(pixel + sf::Vector2i(-1, 0), image, &neighbours);
	TryAddPixel(pixel + sf::Vector2i(0, -1), image, &neighbours);
	TryAddPixel(pixel + sf::Vector2i(-1, -1), image, &neighbours);
	TryAddPixel(pixel + sf::Vector2i(-1, 1), image, &neighbours);
	TryAddPixel(pixel + sf::Vector2i(1, -1), image, &neighbours);


	return neighbours;
}
