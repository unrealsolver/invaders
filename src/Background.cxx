#include "Background.h"

int
BackGround::LoadImage (std::string path, unsigned char layer)
{
	layer--;
	if (layer > 2)
	{
		std::cout << "Bad layer number " << (unsigned) layer << std::endl;
		return 1;
	}
	image[layer].loadFromFile (path);
	image[layer].setSmooth (false);
	sprite[layer].setTexture (image[layer]);
	sprite[layer].setScale (10,10);
}


void
BackGround::Draw (sf::RenderWindow &App)
{
	const sf::View  *view = &App.getView();	
	const sf::FloatRect *screen = &view->getViewport();
	
	int i = 1;
	int c = 0;
	int f = 15; 
	//sprite.SetPosition (screen->Left - fmod(screen->Left/f, sprite.GetSize().x), floor(screen->Top/f));
	for (i = 0; i < 2; i++)
	{
		f /= i + 1;
		for (int x = screen->left - fmod(screen->left/f, sprite[i].getTextureRect().left); x < screen->width; x += sprite[i].getTextureRect().left) // >10: C++ is magic...
		{	
			for (int y = screen->top - fmod(screen->top/f, sprite[i].getTextureRect().top); y < screen->height; y += sprite[i].getTextureRect().top)
			{
				if (screen->left - fmod(screen->left/f, sprite[i].getTextureRect().left) > screen->left) 
				{
					std::cout << "WTF?!" << std::endl;
				//	exit (1);
				}
				sprite[i].setPosition (x, y);
				App.draw (sprite[i]);
				c++;
			}
		}
	}
	std::cout << "Total tiles: " << c << std::endl;
	
}
