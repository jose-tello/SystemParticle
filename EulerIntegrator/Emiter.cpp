#include "Emiter.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Particle.h"
#include "math.h"

Emiter::Emiter(std::vector<float>& position, std::vector<float>& particleSpeed, std::vector<int>& particleVariationSpeed,
	std::vector<float>& particleAcceleration, std::vector<int>& particleVariationAcceleration, float particleAngularSpeed,
	int particleVariableAngularSpeed, float particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture) :

	position(position),
	particleSpeed(particleSpeed),
	particleVariationSpeed(particleVariationSpeed),
	particleAcceleration(particleAcceleration),
	particleVariationAcceleration(particleVariationAcceleration),
	particleAngularSpeed(particleAngularSpeed),
	particleVariationAngularSpeed(particleVariableAngularSpeed),
	particlesRate(particlesRate),
	particlesLifeTime(particlesLifeTime),
	areaOfSpawn(areaOfSpawn),
	particleTexture(texture)

{
	Start();
}


Emiter::Emiter(float positionX, float positionY, float particleSpeedX, float particleSpeedY, int particleVariationSpeedX, int particleVariationSpeedY,
	float particleAccelerationX, float particleAccelerationY, int particleVariationAccelerationX, int particleVariationAccelerationY, float particleAngularSpeed,
	int particleVariableAngularSpeed, float particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture) :

	position{ positionX, positionY },
	particleSpeed{ particleSpeedX, particleSpeedY },
	particleVariationSpeed{ particleVariationSpeedX, particleVariationSpeedY },
	particleAcceleration{ particleAccelerationX, particleAccelerationY },
	particleVariationAcceleration{ particleVariationAccelerationX, particleVariationAccelerationY },
	particleAngularSpeed(particleAngularSpeed),
	particleVariationAngularSpeed(particleVariableAngularSpeed),
	particlesRate(particlesRate),
	particlesLifeTime(particlesLifeTime),
	areaOfSpawn(areaOfSpawn),
	particleTexture(texture)
{
	Start();
}


void Emiter::Start()
{
	int maxParticles = particlesRate * particlesLifeTime + 1;

	//We assume that the game will allways go at 60 FPS
	particlesPerFrame = particlesRate * 16 / 1000;

	particleVector.reserve(maxParticles);

	for (int i = 0; i < maxParticles; i++)
	{
		CreateParticle();
	}


	if (areaOfSpawn == nullptr)
	{
		randomizePos = false;
	}
	else
		randomizePos = true;


	if (particleVariationSpeed[0] == NULL && particleVariationSpeed[1] == NULL)
	{
		randomizeSpeed = false;
	}
	else
		randomizeSpeed = true;


	if (particleVariationAcceleration[0] == NULL && particleVariationAcceleration[1] == NULL)
	{
		randomizeAcceleration = false;
	}
	else
		randomizeAcceleration = true;
}


void Emiter::CreateParticle()
{
	particleVector.push_back(Particle(particlesLifeTime, particleTexture));
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

	particlesEmited += particlesPerFrame;

	if (particlesEmited >= 1)
	{
		int emited = 0;

		for (int i = 0; i < particleVector.size(); i++)
		{
			if (particleVector[i].Activate(GeneratePosX(), GeneratePosY(), GenerateSpeedX(), GenerateSpeedY(), GenerateAccelerationX(), GenerateAccelerationY(), GenerateAngularSpeed()))
			{
				emited++;
			}

			if ((int)particlesEmited == emited)
				break;
			
		}

		particlesEmited -= emited;
	}
}


float Emiter::GeneratePosX()
{
	if (randomizePos == true)
	{
		float x = (rand() % areaOfSpawn->w) + position[0];
		return x;
	}

	else
		return position[0];
}


float Emiter::GeneratePosY()
{
	if (randomizePos == true)
	{
		float y = (rand() % areaOfSpawn->h) + position[1];
		return y;
	}

	else
		return position[1];
}


float Emiter::GenerateSpeedX()
{
	if (randomizeSpeed == true)
	{
		float speedX = (rand() % particleVariationSpeed[0]) + particleSpeed[0];
		return speedX;
	}

	else
		return particleSpeed[0];
}


float Emiter::GenerateSpeedY()
{
	if (randomizeSpeed == true)
	{
		float speedY = (rand() % particleVariationSpeed[1]) + particleSpeed[1];
		return speedY;
	}

	else
		return particleSpeed[1];

}


float Emiter::GenerateAccelerationX()
{
	if (randomizeAcceleration == true)
	{
		float accX = (rand() % particleVariationAcceleration[0]) + particleAcceleration[0];
		return accX;
	}

	else
		return particleAcceleration[0];
}


float Emiter::GenerateAccelerationY()
{
	if (randomizeAcceleration == true)
	{
		float accY = (rand() % particleVariationAcceleration[1]) + particleAcceleration[1];
		return accY;
	}

	else
		return particleAcceleration[1];
}


float Emiter::GenerateAngularSpeed()
{
	if (randomizeAngularSpeed == true)
	{
		float angularSpeed = (rand() % particleVariationAngularSpeed) + particleAngularSpeed;
		return angularSpeed;
	}

	else
		return particleAngularSpeed;
}