#include "Particle.h"

ParticleSystem::ParticleSystem (int x, int y, float time_last)
{
}

bool
ParticleSystem::IsAlive (float dt)
{
	return  ((time_last -= dt) < 0)?0:1;
		
}
