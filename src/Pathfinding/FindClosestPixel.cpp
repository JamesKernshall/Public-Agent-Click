#include "FindClosestPixel.h"
#include <algorithm>

FindClosestPixel::FindClosestPixel(sf::Image* img)
{
	image = img;
}

sf::Vector2i FindClosestPixel::ClosetPixel(sf::Vector2u start_pixel)
{
	open.push_back(static_cast<sf::Vector2i>(start_pixel));

	for(int i = 0; i < open.size(); i++)
	{
		sf::Vector2i pixel = open[i];

		if (pixel.x >= image->getSize().x || pixel.y >= image->getSize().y)
		{
			continue;
		}

		if (image->getPixel(pixel.x, pixel.y).a > 0)
		{
			return pixel;
		}

		AddNewNeighbourPixels(pixel);
		
	}

	return static_cast<sf::Vector2i>(start_pixel);
}

void FindClosestPixel::AddNewNeighbourPixels(sf::Vector2i pixel)
{	
	TryAddPixel(pixel + sf::Vector2i(1, 0));
	TryAddPixel(pixel + sf::Vector2i(0, 1));
	TryAddPixel(pixel + sf::Vector2i(-1, 0));
	TryAddPixel(pixel + sf::Vector2i(0, -1));
}

void FindClosestPixel::TryAddPixel(sf::Vector2i pixel)
{
	//Check if valid number on the image
	if (!(pixel.x >= 0 && pixel.x <= image->getSize().x &&
		pixel.y >= 0 && pixel.y <= image->getSize().y))
	{
		return;
	}

	//Check if isn't already contained in open
	if (std::find(open.begin(), open.end(), pixel) == open.end()) 
	{
		open.emplace_back(pixel);
	}
}
