#include "Ship.h"

void
Ship::DrawFire (void)
{
	
}

void
Ship::OnIdle (float dt)
{
	if (march_engine_activated)
	{
		//[TODO] Rewrite!
		sf::Vector2f eng_force = sf::Vector2f (sin (getRotation()* M_PI / 180) * march_engine_force, -cos (getRotation() * M_PI / 180)*march_engine_force);
		SetForce (GetForce() + eng_force);
	}
	Entity::OnIdle (dt);
}

void
Ship::SetMarchEngine (bool activated)
{
	march_engine_activated = activated;
}

void
Ship::SetMarchEngineForce (const float &force)
{
	this->march_engine_force = force;
}

const float&
Ship::GetMarcheEngineForce (void)
{
	return march_engine_force;
}
