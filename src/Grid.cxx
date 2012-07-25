#include "Grid.h"

Grid::Grid (sf::RenderWindow &window)
{
	color = sf::Color (255,255,255,128);
	subdivide = 5;
	scale = 50;
	this->window = &window;
	this->line.setFillColor (color);
}

void
Grid::setScale (unsigned scale)
{
	this->scale = scale;
}

unsigned
Grid::getScale (void)
{
	return this->scale;
}

void
Grid::setColor (const sf::Color &color)
{
	this->color = color;
}

const sf::Color&
Grid::getColor (void)
{
	return this->color;
}

void
Grid::setSubdivide (unsigned subdivide)
{
	this->subdivide = subdivide;
}

unsigned
Grid::getSubdivide (void)
{
	return this->subdivide;
}

void
Grid::draw (void)
{
	draw_grid (1, this->scale);
	draw_grid (2, this->scale * this->subdivide);
	
}

void
Grid::draw_grid (int tint, unsigned scale)
{
	/*
	sf::RectangleShape zero_marker;
	zero_marker.setSize (sf::Vector2f (10, 10));
	zero_marker.setPosition (sf::Vector2f (-5.f, -5.f));
	zero_marker.setOutlineThickness (2);
	zero_marker.setOutlineColor (sf::Color (64, 255, 32, 150));
	zero_marker.setFillColor (sf::Color::Transparent);
	*/
	const sf::Vector2f &size = window->getView().getSize();
	const sf::Vector2f &center = window->getView().getCenter();
	
	this->line.setSize (sf::Vector2f (size.x, tint));
	/*		* центр экрана  * сдвиг					  * упреждение, чтобы рисовать с начала экрана, а не с середины */
	for (int i = center.y - fmod (center.y, scale) -  (((int) size.y)/(scale*2))*scale; i < center.y + size.y/2; i += scale)
	{
		line.setPosition (center.x - size.x/2, i);
		window->draw (line);
	}
	
	this->line.setSize (sf::Vector2f (tint, size.y));
	
	for (int i = center.x - fmod (center.x, scale)  - (((int) size.x)/(scale*2))*scale; i < center.x + size.x/2; i += scale)
	{
		line.setPosition (i, center.y - size.y/2);
		window->draw (line);
	}
}
