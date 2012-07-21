#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class ParticleSystem
{
	public:
		ParticleSystem (int, int, float);
		//~Particle (void);
		void OnIdle (float);
		bool IsAlive (float);
		void SetDecay (bool);
		
	private:
		float time_last;
		
};

#endif
