#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Ship : public Entity
{
	public:
		Ship (sf::RenderWindow &target) : Entity (target) {};
		void SetMarchEngineForce (const float&);
		const float& GetMarcheEngineForce (void);
		
		void SetMarchEngine (bool);
		void OnIdle (float);
	private:
		sf::Vector2f turn_ort;
		float march_engine_force;
		bool march_engine_activated;
};

#endif
