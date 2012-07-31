#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class BackGround
{
	public:
	
		int LoadImage (std::string, unsigned char); //Щито поделать...
		void Draw (sf::RenderWindow&);
		
		friend class sf::Image;
	private:
		sf::Texture image[3];
		sf::Sprite sprite[3];
};

#endif
