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
	rect = { 0, 0, 10, 400 };

	rect2 = { 0, 0, 550, 10 };

	SDL_Texture* snowball = App->textures->Load("particleTextures/bolaNieve.png");

	Animation anim1;
	anim1.PushBack(SDL_Rect{ 0, 0, 10, 10 }, 1, 0, 0);

	Animation anim2;
	anim2.PushBack(SDL_Rect{ 0, 12, 6, 6 }, 1, 0, 0);

	Animation anim3;
	anim3.PushBack(SDL_Rect{ 7, 11, 8, 8 }, 1, 0, 0);

	//Emiter emiter(80, 90, 2, 2, 15, -5, 0, 0, 2, 1, 5, 0, 50, 1, &rect, App->textures->Load("particleTextures/redParticle.png"), anim, true);
	//Emiter emiter2(50, 50, 2, 2, 2, -2, 0, 0, 2, 1, -2, 0, 5, 2, nullptr, App->textures->Load("particleTextures/littleBlueParticle.png"), anim2, false);

	Emiter emiterBigSnowBall   (0, 20, 2, 2, 2, -3, 0, 0, 0, 1, 5, 0, 6, 3.5, &rect, snowball, anim1, true);
	Emiter emiterMidSnowBall   (0, 20, 2, 2, 3, -2, 0, 0, 0, 1, 5, 0, 8, 3.5, &rect, snowball, anim2, true);
	Emiter emiterLittleSnowBall(0, 20, 3, 2, 3, -2, 0, 0, 0, 1, 5, 0, 8, 3.5, &rect, snowball, anim3, true);

	Emiter emiterBigSnowBall2   (20, 0, 2, 2, 2, -3, 0, 0, 0, 1, 5, 0, 6, 3.5, &rect2, snowball, anim1, true);
	Emiter emiterMidSnowBall2   (20, 0, 2, 2, 3, -2, 0, 0, 0, 1, 5, 0, 8, 3.5, &rect2, snowball, anim2, true);
	Emiter emiterLittleSnowBall2(20, 0, 3, 2, 3, -2, 0, 0, 0, 1, 5, 0, 8, 3.5, &rect2, snowball, anim3, true);
	
	//particleSystem->PushEmiter(emiter);
	//particleSystem->PushEmiter(emiter2);
	particleSystem->PushEmiter(emiterBigSnowBall);
	particleSystem->PushEmiter(emiterMidSnowBall);
	particleSystem->PushEmiter(emiterLittleSnowBall);

	particleSystem->PushEmiter(emiterBigSnowBall2);
	particleSystem->PushEmiter(emiterMidSnowBall2);
	particleSystem->PushEmiter(emiterLittleSnowBall2);

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

	dtime = dt;

	return UPDATE_CONTINUE;
}


update_status ModuleParticles::PostUpdate() 
{
	particleSystem->PostUpdate(dtime);

	return UPDATE_CONTINUE;
}