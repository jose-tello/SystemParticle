#include "Emiter.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Particle.h"
#include "math.h"

Emiter::Emiter(std::vector<int>& position, std::vector<int>& speedOfParticles, std::vector<int>& accelerationOfParticles, float particleAngularSpeed, int particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture) :
	position(position),
	speedOfParticles(speedOfParticles),
	accelerationOfParticles(accelerationOfParticles),
	particleAngularSpeed(particleAngularSpeed),
	particlesRate(particlesRate),
	particlesLifeTime(particlesLifeTime),
	areaOfSpawn(areaOfSpawn),
	particleTexture(texture)
{
	Start();
}


void Emiter::Start() 
{
	

}

Emiter::~Emiter() {

	particleVector.clear();

	position.clear();
	speedOfParticles.clear();
	accelerationOfParticles.clear();

	areaOfSpawn = nullptr;
	particleTexture = nullptr;
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

	
}



//Please check this out i fckng hate it but i cant thing of something better and internet doesnt help XD
void Emiter::ThrowParticles() {

	

}