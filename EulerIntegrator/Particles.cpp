#include "Application.h"
#include "Globals.h"
#include "Particles.h"
#include "Textures.h"

ModuleParticles::ModuleParticles(bool start_enabled) : Module(start_enabled)
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