#include "Emiter.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Particle.h"
#include "math.h"

Emiter::Emiter(std::vector<Particle> &particleSamples, std::vector<int> &position, std::vector<int> &speedOfParticles, std::vector<int> &accelerationOfParticles, float particleAngularSpeed, SDL_Rect *areaOfSpawn, SDL_Texture *texture) :
	particleSamples(particleSamples),
	position(position),
	speedOfParticles(speedOfParticles),
	accelerationOfParticles(accelerationOfParticles),
	particleAngularSpeed(particleAngularSpeed),
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

	Draw();

	int numParticles = particleVector.size();

	for (int i = 0; i < numParticles; i++)
	{
		particleVector[i].PostUpdate();
	}

	
}


void Emiter::Draw() {

	if (texture != nullptr)
	{
		App->renderer->Blit(texture, position[0], position[1]);
	}
}


void Emiter::ThrowParticles() {

	for (int i = 0; i < particlesPerFrame; i++)
	{
		int random = rand() % particleSamples.size() - 1;

		if (areaOfSpawn == nullptr)
		{
			Particle aux(position, speedOfParticles, accelerationOfParticles, particleSamples[random].GetAngle(), particleAngularSpeed, particleSamples[random].GetLife(), particleSamples[random].GetTexture());
			particleVector.push_back(aux);
		}
		
		else
		{

		}
	}

}