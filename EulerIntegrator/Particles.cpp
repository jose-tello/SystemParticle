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


	particleSystem = new ParticleSystem();
	Emiter emiter(150, 100, 2, 2, 15, -5, 0, 0, 2, 1, 5, 0, 5, 1, nullptr, App->textures->Load("particleTextures/littleBlueParticle.png"));
	//Emiter emiter2(150, 100, 2, 2, 2, -2, 0, 0, 2, 1, 0, 0, 5, 0.5, nullptr, App->textures->Load("particleTextures/BigBlueParticle.png"));
	//particleSystem->PushEmiter(emiter);
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