#include "Emiter.h"
#include "Globals.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Module.h"

Emiter::Emiter(std::vector<Particle> &particleSamples, std::vector<int> &position, std::vector<int> &speedOfParticles, std::vector<int> &accelerationOfParticles, SDL_Rect *areaOfSpawn, SDL_Texture *texture) :
	particleSamples(particleSamples),
	position(position),
	speedOfParticles(speedOfParticles),
	accelerationOfParticles(accelerationOfParticles),
	areaOfSpawn(areaOfSpawn),
	texture(texture)
{}


Emiter::~Emiter() {

	particleSamples.clear();
	particleVector.clear();
	
	position.clear();
	speedOfParticles.clear();
	accelerationOfParticles.clear();

	areaOfSpawn = nullptr;
	texture = nullptr;
}


void Emiter::Update(float dt) {

	ThrowParticles();
	
	int numParticles = particleVector.size();

	for (int i = 0; i < numParticles; i++)
	{
		particleVector[i].Update(dt);
	}
}


void Emiter::PostUpdate() {

	int numParticles = particleVector.size();

	for (int i = 0; i < numParticles; i++)
	{
		particleVector[i].PostUpdate();
	}

	Draw();
}


void Emiter::Draw() {

	
	if (texture != nullptr)
	{
	//App->

	
	}
}


void Emiter::ThrowParticles() {


}