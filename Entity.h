#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class Entity : public sf::Sprite
{
	public:
		Entity (void) : sf::Sprite() {}; //TODO: Implement
		
		void SetImageFromFile (const std::string&);
			
		void SetForce (const sf::Vector2f&);
		const sf::Vector2f& GetForce (void);
		void SetVelocity (const sf::Vector2f&);
		const sf::Vector2f& GetVelocity (void);
		void SetMass (const float);
		const float GetMass (void);
		
		void ConnectForce (const sf::Vector2f& );
		void DisconnectForce (const sf::Vector2f&);
		
		void OnIdle (float);
		friend class sf::Image;
	private:
		//std::vector <sf::Vector2f*> forces;
		sf::Vector2f F;
		float H;
		sf::Vector2f V;
		float M;
		float m;
		
		sf::Image image;
};

#endif
