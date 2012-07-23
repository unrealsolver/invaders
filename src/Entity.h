#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <math.h>

class Entity : public sf::Sprite
{
	public:
		Entity (void) : sf::Sprite() {}; //TODO: Implement
		
		void SetTextureFromFile (const std::string&); //Rename to "loadTexture"
			
		void SetForce (const sf::Vector2f&);
		const sf::Vector2f& GetForce (void);
		void SetVelocity (const sf::Vector2f&);
		const sf::Vector2f& GetVelocity (void);
		void SetMass (const float);
		const float GetMass (void);
		
		void SwapColor (const sf::Color&, const sf::Color&);
		
		void Draw (sf::RenderWindow &target);
		
		void OnIdle (float);

		friend class sf::Image;	
		
	private:
		//std::vector <sf::Vector2f*> forces;
		sf::Vector2f F;
		float H;
		sf::Vector2f V;
		float M;
		float m;
		sf::Font font; //tmp
		float prevdt; //tmp
		sf::Texture texture;
		
};

#endif
