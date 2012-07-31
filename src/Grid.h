#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class Grid
{
	public:
		//Grid (void);
		Grid (sf::RenderWindow &target);
		
		//void setScale (unsigned scale);
		//unsigned getScale (void);
		void setColor (const sf::Color &color);
		const sf::Color &getColor (void);
		void setSubdivide (unsigned subdivide);
		unsigned getSubdivide (void);
		
		void adjust (void); //Recalculate actual scale value. 
		
		//void SetTarget (sf::RenderWindow &window); //Нинужно.
		void draw (void);
	private:
		sf::RenderWindow &window;	//TODO: Рендер на текстуру.
									//http://www.sfml-dev.org/documentation/2.0/classsf_1_1Drawable.php
		unsigned scale;
		sf::Color color;
		unsigned subdivide;
		
		sf::View view; //This view will be used for drawing grid
		
		sf::RectangleShape line; 

		void draw_grid (int tint, unsigned scale);
};

#endif
