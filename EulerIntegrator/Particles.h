#pragma once

#ifndef __MODULE_PARTICLES__
#define __MODULE_PARTICLES__


#include "Module.h"
#include "Emiter.h"

class ModuleParticles : public Module
{
public:
	ModuleParticles(Application* app, bool start_enabled = true);
	~ModuleParticles();

	bool Start();
	update_status PreUpdate();
	update_status Update(float dt);
	update_status PostUpdate();

private:
	vector<Emiter> particleArray; 
	
};




#endif //__MODULE_PARTICLES__