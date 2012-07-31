#include "Grid.h"

Grid::Grid (sf::RenderWindow &target) : window (target)
{
	color = sf::Color (255,255,255,128);
	subdivide = 4;
	scale = 50;
	this->line.setFillColor (color);
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
Grid::adjust (void)
{
	/* TODO: Rewrite. Antipattern: "Magic numbers" */
	if (window.getView().getSize().y / scale > 5)
	{	
		scale *= subdivide;
	}
	if (window.getView().getSize().y / scale < 2)
	{
		scale /= subdivide;
	}
	
}

void
Grid::draw (void)
{
	view = window.getView ();
	draw_grid (1, this->scale);
	window.setView (view);
	draw_grid (3, this->scale * this->subdivide); //TODO: Bad idea. Привязываемся к крупной сетке, а не мелкой. Впрочем похуй...
	window.setView (view);
}

void
Grid::draw_grid (int tint, unsigned scale)
{
	/* Useful references */
	const sf::Vector2f &size = window.getView().getSize();
	const sf::Vector2f &center = window.getView().getCenter();
	const sf::Vector2f &d_size = window.getDefaultView().getSize();//TODO: УБРАТЬ В ДРУГОЕ МЕСТО
	
	/* WARNING: LINEAR ALGEBRA! DON"T READ! */
	float zoom = (d_size.x / size.x);
	sf::Vector2f offset;
	offset.x = fmod (center.x - size.x/2, scale) * zoom;
	offset.y = fmod (center.y - size.y/2, scale) * zoom;
	float between = scale * zoom;
	
	/* Returns to local coordinates */
	window.setView (window.getDefaultView());
	
	/* Draw */
	this->line.setSize (sf::Vector2f (d_size.x, tint));
	
	for (float i = -offset.y; i < d_size.y; i += between)
	{
		line.setPosition (0, i);
		window.draw (line);
	}
	
	this->line.setSize (sf::Vector2f (tint, d_size.y));
	
	for (float i = -offset.x; i < d_size.x; i += between)
	{
		line.setPosition (i, 0);
		window.draw (line);
	}
}
