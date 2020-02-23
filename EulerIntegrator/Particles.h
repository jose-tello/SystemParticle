#pragma once

#ifndef __MODULE_PARTICLES__
#define __MODULE_PARTICLES__

#include "Module.h"
#include "Particle.h"

class ModulePartiles : public Module
{
public:
	ModulePartiles(Application* app, bool start_enabled = true);
	~ModulePartiles();

	bool Start();
	update_status PreUpdate();
	update_status Update(float dt);
	update_status PostUpdate();

private:
	vector<Particle> particleArray;
};




#endif //__MODULE_PARTICLES__