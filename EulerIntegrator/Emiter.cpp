#include "Emiter.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Particle.h"
#include "math.h"

Emiter::Emiter(std::vector<int> position, std::vector<int> particleSpeed, std::vector<int> particleAcceleration, float particleAngularSpeed, int particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture) :
	position(position),
	particleSpeed(particleSpeed),
	particleAcceleration(particleAcceleration),
	particleAngularSpeed(particleAngularSpeed),
	particlesRate(particlesRate),
	particlesLifeTime(particlesLifeTime),
	areaOfSpawn(areaOfSpawn),
	particleTexture(texture),
	particleVariationSpeed{10, 5}
{
	Start();
}


Emiter::Emiter(int positionX, int positionY, int particleSpeedX, int particleSpeedY, int particleAccelerationX, int particleAccelerationY, float particleAngularSpeed, int particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture) :
	position{ positionX, positionY },
	particleSpeed{ particleSpeedX, particleSpeedY },
	particleAcceleration{particleAccelerationX, particleAccelerationY},
	particleAngularSpeed(particleAngularSpeed),
	particlesRate(particlesRate),
	particlesLifeTime(particlesLifeTime),
	areaOfSpawn(areaOfSpawn),
	particleTexture(texture),
	particleVariationSpeed{ 15, -5 }

{
	Start();
}


void Emiter::Start() 
{
	int maxParticles = particlesRate * (particlesLifeTime);

	for (int i = 0; i < maxParticles; i++)
	{
		CreateParticle();
	}
}


void Emiter::CreateParticle() 
{
	std::vector<int> auxSpeed;

	
	auxSpeed.push_back(particleSpeed[0] + (rand() % particleVariationSpeed[0]));
	auxSpeed.push_back(particleSpeed[1] + (rand() % particleVariationSpeed[1]));

	particleVector.push_back(Particle(position, auxSpeed, particleAcceleration, 0, particleAngularSpeed, particlesLifeTime, particleTexture));

}

Emiter::~Emiter() {

	particleVector.clear();

	position.clear();
	particleSpeed.clear();
	particleAcceleration.clear();

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



void Emiter::ThrowParticles() {

	int particlesEmited = 0;

	for (int i = 0; i < particleVector.size(); i++)
	{
		if (particleVector[i].Activate())
		{
			particlesEmited++;
		}

		if (particlesEmited == particlesRate)
			break;
	}

}