#include "Application.h"
#include "Globals.h"
#include "Particles.h"
#include "Emiter.h"
#include "ParticleSystem.h"
#include "Textures.h"

ModuleParticles::ModuleParticles(bool start_enabled) : Module(start_enabled)
{}

ModuleParticles::~ModuleParticles()
{}


bool ModuleParticles::Start() {

	//charge all particles
	

	particleSystem = new ParticleSystem();
	Emiter emiter(150, 150, 5, 5, 0, 0, 0, 10, 5, nullptr, App->textures->Load("particleTextures/redParticle.png"));
	particleSystem->PushEmiter(emiter);

	return true;
}

update_status ModuleParticles::PreUpdate() {



	return UPDATE_CONTINUE;
}


update_status ModuleParticles::Update(float dt) {

	particleSystem->Update(dt);

	return UPDATE_CONTINUE;
}


update_status ModuleParticles::PostUpdate() {

	particleSystem->PostUpdate();

	return UPDATE_CONTINUE;
}