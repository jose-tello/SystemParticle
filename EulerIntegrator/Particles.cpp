#include "Application.h"
#include "Globals.h"
#include "Particles.h"
#include "Emiter.h"
#include "ParticleSystem.h"
#include "Textures.h"
#include "Input.h"

ModuleParticles::ModuleParticles(bool start_enabled) : Module(start_enabled)
{}

ModuleParticles::~ModuleParticles()
{}


bool ModuleParticles::Start() 
{
	particleSystem = new ParticleSystem();
	rect = { 0, 0, 100, 100 };
	Emiter emiter(80, 90, 2, 2, 15, -5, 0, 0, 2, 1, 5, 0, 50, 1, &rect, App->textures->Load("particleTextures/redParticle.png"), true);
	Emiter emiter2(50, 50, 2, 2, 2, -2, 0, 0, 2, 1, -2, 0, 5, 2, nullptr, App->textures->Load("particleTextures/littleBlueParticle.png"), false);
	
	particleSystem->PushEmiter(emiter);
	particleSystem->PushEmiter(emiter2);

	return true;
}

update_status ModuleParticles::PreUpdate() 
{
	if (App->input->GetKey(SDL_SCANCODE_1))
	{
		particleSystem->Activate();
	}

	if (App->input->GetKey(SDL_SCANCODE_2))
	{
		particleSystem->Desactivate();
	}

	if (App->input->GetKey(SDL_SCANCODE_3))
	{
		particleSystem->Move(App->input->GetMouseX(), App->input->GetMouseY());
	}
	return UPDATE_CONTINUE;
}


update_status ModuleParticles::Update(float dt) 
{
	particleSystem->Update(dt);

	return UPDATE_CONTINUE;
}


update_status ModuleParticles::PostUpdate() 
{
	particleSystem->PostUpdate();

	return UPDATE_CONTINUE;
}