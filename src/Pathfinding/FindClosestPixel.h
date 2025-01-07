#pragma once
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Transform.hpp"

/// NOTE, THIS IS UNUSED.
/// This would generate the closest point using a given pixel and the depth map however...
/// After lengthly implementation I realised unless I account for depth using the depth map the closest point will end up looking wildly wrong
/// And it's better and easier to simply have a button to take from the mouse_pos during editor mode

class FindClosestPixel
{
public:
	FindClosestPixel(sf::Image* image);
	sf::Vector2i ClosetPixel(sf::Vector2u start_pixel);

private:
	void AddNewNeighbourPixels(sf::Vector2i pixel);
	void TryAddPixel(sf::Vector2i pixel);
private:
	std::vector<sf::Vector2i> open;
	sf::Image* image;
};