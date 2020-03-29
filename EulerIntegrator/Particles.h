#pragma once

#ifndef __MODULE_PARTICLES__
#define __MODULE_PARTICLES__


#include "Module.h"

class ParticleSystem;
class Emiter;

class ModuleParticles : public Module
{
public:
	ModuleParticles(bool start_enabled = true);
	~ModuleParticles();

	bool Start();
	update_status PreUpdate();
	update_status Update(float dt);
	update_status PostUpdate();

private:
	vector<Emiter> particleArray; 
	ParticleSystem *particleSystem;

	SDL_Rect rect;
	Emiter* emiter;
	Emiter* emiter2;
};




#endif //__MODULE_PARTICLES__