#include "Emiter.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Particle.h"
#include "math.h"

Emiter::Emiter(std::vector<float> &position, std::vector<float> &particleSpeed, std::vector<int> &particleVariationSpeed, std::vector<float> &particleAcceleration, float particleAngularSpeed, int particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture) :
	position(position),
	particleSpeed(particleSpeed),
	particleAcceleration(particleAcceleration),
	particleAngularSpeed(particleAngularSpeed),
	particlesRate(particlesRate),
	particlesLifeTime(particlesLifeTime),
	areaOfSpawn(areaOfSpawn),
	particleTexture(texture),
	particleVariationSpeed(particleVariationSpeed)
{
	Start();
}


Emiter::Emiter(float positionX, float positionY, float particleSpeedX, float particleSpeedY, int particleVariationSpeedX, int particleVariationSpeedY, float particleAccelerationX, float particleAccelerationY, float particleAngularSpeed, int particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture) :
	position{ positionX, positionY },
	particleSpeed{ particleSpeedX, particleSpeedY },
	particleAcceleration{particleAccelerationX, particleAccelerationY},
	particleAngularSpeed(particleAngularSpeed),
	particlesRate(particlesRate),
	particlesLifeTime(particlesLifeTime),
	areaOfSpawn(areaOfSpawn),
	particleTexture(texture),
	particleVariationSpeed{ particleVariationSpeedX, particleVariationSpeedY }
{
	Start();
}


void Emiter::Start() 
{
	int maxParticles = particlesRate * particlesLifeTime * FPS;

	particleVector.reserve(maxParticles);

	for (int i = 0; i < maxParticles; i++)
	{
		CreateParticle();
	}
}


void Emiter::CreateParticle() 
{
	std::vector<float> auxSpeed;

	
	auxSpeed.push_back(particleSpeed[0] + (rand() % particleVariationSpeed[0]));
	auxSpeed.push_back(particleSpeed[1] + (rand() % particleVariationSpeed[1]));

	particleVector.push_back(Particle(position, auxSpeed, particleAcceleration, 0, particleAngularSpeed, particlesLifeTime, particleTexture));

}

Emiter::~Emiter() {

	particleVector.clear();

	position.clear();
	particleSpeed.clear();
	particleAcceleration.clear();

	particleVariationSpeed.clear();
	particleVariationAcceleration.clear();

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
		if (particleVector[i].Activate(position[0], position[1]))
		{
			particlesEmited++;
		}

		if (particlesEmited == particlesRate)
			break;
	}

}