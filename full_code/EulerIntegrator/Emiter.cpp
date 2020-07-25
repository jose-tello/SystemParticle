#include "Emiter.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Particle.h"
#include "math.h"

Emiter::Emiter(fMPoint& position, fMPoint& particleSpeed, iMPoint& particleVariationSpeed, fMPoint& particleAcceleration,
	iMPoint& particleVariationAcceleration, float particleAngularSpeed, int particleVariableAngularSpeed, float particlesRate,
	float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture, Animation particleAnimation, bool fade) :


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
	particleTexture(texture),
	particleAnimation(particleAnimation),

	randomizePosX(true),
	randomizePosY(true),

	randomizeSpeedX(true),
	randomizeSpeedY(true),

	randomizeAccelerationX(true),
	randomizeAccelerationY(true),

	randomizeAngularSpeed(true),

	active(true),
	fadeParticles(fade),

	particlesEmited(0.0f),
	activeParticles(0)
{
	Start();
}


Emiter::Emiter(float positionX, float positionY, float particleSpeedX, float particleSpeedY, int particleVariationSpeedX, int particleVariationSpeedY,
	float particleAccelerationX, float particleAccelerationY, int particleVariationAccelerationX, int particleVariationAccelerationY, float particleAngularSpeed,
	int particleVariableAngularSpeed, float particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture, Animation particleAnimation, bool fade) :

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
	particleTexture(texture),
	particleAnimation(particleAnimation),

	randomizePosX(true),
	randomizePosY(true),

	randomizeSpeedX(true),
	randomizeSpeedY(true),

	randomizeAccelerationX(true),
	randomizeAccelerationY(true),

	randomizeAngularSpeed(true),

	active(true),
	fadeParticles(fade),

	particlesEmited(0.0f),
	activeParticles(0)
{
	Start();
}


void Emiter::Start()
{
	//TODO 3: Just calculate the max number of particles you will have in screen
	//particles rate * particles life time
	int maxParticles = particlesRate * particlesLifeTime + 1;

	//We assume that the game will allways go at 60 FPS
	particlesPerFrame = particlesRate * 16 / 1000;

	particleVector.reserve(maxParticles);

	for (int i = 0; i < maxParticles; i++)
	{
		CreateParticle();
	}

	//Set all the bools to check what variables will be randomized in the Generate() functions
	if (areaOfSpawn == nullptr)
	{
		randomizePosX = false;
		randomizePosY = false;
	}

	else
	{
		if (areaOfSpawn->w == 0)
		{
			randomizePosX = false;
		}

		if (areaOfSpawn->h == 0)
		{
			randomizePosY = false;
		}
	}


	if (particleVariationSpeed.x == NULL)
		randomizeSpeedX = false;

	if (particleVariationSpeed.y == NULL)
		randomizeSpeedY = false;

	if (particleVariationAcceleration.x == NULL)
		randomizeAccelerationX = false;

	if (particleVariationAcceleration.y == NULL)
		randomizeAccelerationY = false;

	if (particleVariationAngularSpeed == 0)
		randomizeAngularSpeed = false;
}


void Emiter::CreateParticle()
{
	particleVector.push_back(Particle());
}


Emiter::~Emiter()
{
	particleVector.clear();

	areaOfSpawn = nullptr;
	particleTexture = nullptr;
}


void Emiter::Update(float dt)
{
	if (active)
	{
		ThrowParticles();
	}

	for (int i = 0; i < activeParticles; i++)
	{
		if (particleVector[i].Update(dt) == false)
		{
			activeParticles--;
			particleVector[i] = particleVector[activeParticles];
			particleVector[activeParticles].Deactivate();
		}
	}
}


void Emiter::PostUpdate(float dt)
{
	DrawParticles();
}


void Emiter::Desactivate()
{
	active = false;
}

void Emiter::Activate()
{
	active = true;
}


//This funtions activates the necesary particles and gives them the initial values
void Emiter::ThrowParticles() {

	//You could use delta time instead of particlesPerFrame, but i dont recommend it
	particlesEmited += particlesPerFrame;

	if (particlesEmited >= 1)
	{
		int emited = 0;
		int maxParticles = particleVector.size();

		for (int i = activeParticles; i < maxParticles; i++)
		{
			//TODO 2: Call Activate(), use Generate...() functions to get the parameters Activate() needs.
			//Activate returns false if the particle is already active, and true if we activate it.

			particleVector[i].Reset(GeneratePosX(), GeneratePosY(), GenerateSpeedX(), GenerateSpeedY(), GenerateAccelerationX(), GenerateAccelerationY(), GenerateAngularSpeed(), particlesLifeTime);
			emited++;
			activeParticles++;
			
			//If we activated the necesary particles this frame, break
			if ((int)particlesEmited == emited)
				break;
		}

		particlesEmited -= emited;
	}
}


void Emiter::DrawParticles()
{
	fMPoint pos;
	float angle;
	float lifeTime;
	SDL_Rect rect;

	for (int i = 0; i < activeParticles; i++)
	{
		particleVector[i].GetDrawVariables(pos, angle, lifeTime);
		rect = particleAnimation.GetFrameBox(particlesLifeTime - lifeTime);

		if (App->renderer->IsInsideCamera(rect))
		{
			particleVector[i].GetDrawVariables(pos, angle, lifeTime);

			if (fadeParticles == true)
			{
				Uint8 transparency = lifeTime / particlesLifeTime * 255;
				App->renderer->Blit(particleTexture, pos.x, pos.y, &rect, transparency, 0, angle);
			}

			else
				App->renderer->Blit(particleTexture, pos.x, pos.y, &rect, 255, 0, angle);
		}
	}
}


float Emiter::GeneratePosX()
{
	if (randomizePosX == true)
	{
		float x = (rand() % areaOfSpawn->w) + position.x;
		return x;
	}

	else
		return position.x;
}


float Emiter::GeneratePosY()
{
	if (randomizePosY == true)
	{
		float y = (rand() % areaOfSpawn->h) + position.y;
		return y;
	}

	else
		return position.y;
}


float Emiter::GenerateSpeedX()
{
	if (randomizeSpeedX == true)
	{
		float speedX = (rand() % particleVariationSpeed.x) + particleSpeed.x;
		return speedX;
	}

	else
		return particleSpeed.x;
}


float Emiter::GenerateSpeedY()
{
	if (randomizeSpeedY == true)
	{
		float speedY = (rand() % particleVariationSpeed.y) + particleSpeed.y;
		return speedY;
	}

	else
		return particleSpeed.y;

}


float Emiter::GenerateAccelerationX()
{
	if (randomizeAccelerationX == true)
	{
		float accX = (rand() % particleVariationAcceleration.x) + particleAcceleration.x;
		return accX;
	}

	else
		return particleAcceleration.x;
}


float Emiter::GenerateAccelerationY()
{
	if (randomizeAccelerationY == true)
	{
		float accY = (rand() % particleVariationAcceleration.y) + particleAcceleration.y;
		return accY;
	}

	else
		return particleAcceleration.y;
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


void Emiter::GetPosition(int& x, int& y)
{
	x = position.x;
	y = position.y;
}

void Emiter::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}