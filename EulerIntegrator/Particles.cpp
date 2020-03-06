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
	Emiter emiter(150, 100, 5, -10, 0, 2, 0, 10, 50, nullptr, App->textures->Load("particleTextures/redParticle.png"));
	particleSystem->PushEmiter(emiter);

	Emiter emiter2(150, 100, -5, -10, 0, 2, 0, 10, 50, nullptr, App->textures->Load("particleTextures/redParticle.png"));
	particleSystem->PushEmiter(emiter2);

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