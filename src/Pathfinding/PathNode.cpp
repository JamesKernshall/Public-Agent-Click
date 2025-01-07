#include "PathNode.h"


PathNode::PathNode(sf::Vector2u position)
{
	pixel = position;
	g = 999999;
}

bool PathNode::HasItem(std::list<PathNode> nodeList, PathNode item)
{
	//Check if isn't already contained in open
	return std::find(nodeList.begin(), nodeList.end(), item) != nodeList.end();
}

bool PathNode::HasItemAndLowerHeuristic(std::list<PathNode> nodeList, PathNode item, float itemG)
{
	for(auto& node : nodeList)
	{
		if (node.pixel == item.pixel && itemG >= node.g)
		{
			return true;
		}
	}
	return false;
}
