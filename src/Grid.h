#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <math.h>

class Grid
{
	public:
		//Grid (void);
		Grid (sf::RenderWindow &window);
		
		void setScale (unsigned scale);
		unsigned getScale (void);
		void setColor (const sf::Color &color);
		const sf::Color &getColor (void);
		void setSubdivide (unsigned subdivide);
		unsigned getSubdivide (void);
		
		//void SetTarget (sf::RenderWindow &window); //Нинужно.
		void draw (void);
	private:
		sf::RenderWindow *window;	//TODO: Рендер на текстуру. RemderTarget != RenderWindow, печаль.
									//http://www.sfml-dev.org/documentation/2.0/classsf_1_1Drawable.php
		unsigned scale;
		sf::Color color;
		unsigned subdivide;
		
		sf::RectangleShape line; 
		
		void draw_grid (int tint, unsigned scale);
};

#endif
