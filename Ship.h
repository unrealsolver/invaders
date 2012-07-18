#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"


enum
{
	CW = 1,
	CCW
};

class Ship : public Entity
{
	public:
		Ship (void) : Entity () {};
		void SetMarchEngineForce (const float&);
		const float& GetMarcheEngineForce (void);
		
		void SetMarchEngine (bool);
		void OnIdle (float);
		
		void DrawFire (void);
	private:
		float march_engine_force;
		bool march_engine_activated;
		//bool is_draw_fire;
};

#endif
