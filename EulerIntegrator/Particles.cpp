
#include "Particles.h"
#include "Textures.h"

ModuleParticles::ModuleParticles(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleParticles::~ModuleParticles()
{}


bool ModuleParticles::Start() {

	//charge all particles
	return true;
}

update_status ModuleParticles::PreUpdate() {



	return UPDATE_CONTINUE;
}


update_status ModuleParticles::Update(float dt) {


	return UPDATE_CONTINUE;
}


update_status ModuleParticles::PostUpdate() {


	return UPDATE_CONTINUE;
}