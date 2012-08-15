#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <map>

class Entity : public sf::Sprite
{
	public:
		Entity (sf::RenderWindow &target) : window (target) {}; //TODO: Implement
		
		void setObjMan (std::multimap<float, Entity*> *objects);
		
		void SetTextureFromFile (const std::string&); //Rename to "loadTexture"
			
		void SetForce (const sf::Vector2f&);
		const sf::Vector2f& GetForce (void);
		void SetVelocity (const sf::Vector2f&);
		const sf::Vector2f& GetVelocity (void);
		void SetMass (const float);
		const float GetMass (void);
		
		void SwapColor (const sf::Color&, const sf::Color&);
		
		virtual void OnIdle (float);
		virtual void draw (void) { window.draw (*this);};

		friend class sf::Image;	
		friend class Ship;
	private:
	
		sf::RenderWindow &window;
		sf::Vector2f F;
		float H;
		sf::Vector2f V;
		float M;
		float m;
		sf::Texture texture;
		std::multimap<float, Entity*> *objects;
		
};

#endif
