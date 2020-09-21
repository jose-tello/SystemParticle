#include "EmiterState.h"

#include "SDL/include/SDL_rect.h"
#include <stdlib.h>

EmiterState::EmiterState(fMPoint particleSpeed, fMPoint particleAcceleration, float particleAngularSpeed, float particlesRate, float particlesLifeTime, 
						   SDL_Rect* areaOfSpawn, iMPoint particleVariationSpeed, iMPoint particleVariationAcceleration, int particleVariationAngularSpeed,
						   bool fadeParticles, int rColor, int gColor, int bColor) :

	particleSpeed(particleSpeed),
	particleAcceleration(particleAcceleration),
	particleAngularSpeed(particleAngularSpeed),
	
	particlesRate(particlesRate),
	particlesLifeTime(particlesLifeTime),
	particlesPerFrame(0),
	
	areaOfSpawn(areaOfSpawn),
	particleVariationSpeed(particleVariationSpeed),
	particleVariationAcceleration(particleVariationAcceleration),
	particleVariationAngularSpeed(particleVariationAngularSpeed),

	randomizePosX(true),
	randomizePosY(true),
	randomizeSpeedX(true),
	randomizeSpeedY(true),
	randomizeAccelerationX(true),
	randomizeAccelerationY(true),
	randomizeAngularSpeed(true),

	fadeParticles(fadeParticles),
	fadeColor(true),
	rColor(rColor),
	gColor(gColor),
	bColor(bColor)
{
	Start();
}


EmiterState::~EmiterState()
{
	//delete areaOfSpawn;
}


void EmiterState::Start()
{
	//We assume that the game will allways go at 60 FPS
	particlesPerFrame = particlesRate * 16 / 1000;


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

	if (rColor == 255 && gColor == 255 && bColor == 255)
		fadeColor = false;
}


void EmiterState::GenerateValues(fMPoint& emmiterPos, float& posX, float& posY, float& spX, float& spY, float& accX, float& accY, float& asp) const
{
	posX = GeneratePosX(emmiterPos.x);
	posY = GeneratePosY(emmiterPos.y);

	spX = GenerateSpeedX();
	spY = GenerateSpeedY();

	accX = GenerateAccelerationX();
	accY = GenerateAccelerationY();
	
	asp = GenerateAngularSpeed();
}


float EmiterState::GetParticlesRate() const
{
	return particlesRate;
}


float EmiterState::GetParticlesLifeTime() const
{
	return particlesLifeTime;
}


float EmiterState::GetParticlesPerFrame() const
{
	return particlesPerFrame;
}


float EmiterState::GeneratePosX(float posX) const
{
	if (randomizePosX == true)
	{
		float x = (rand() % areaOfSpawn->w) + posX;
		return x;
	}

	else
		return posX;
}


float EmiterState::GeneratePosY(float posY) const
{
	if (randomizePosY == true)
	{
		float y = (rand() % areaOfSpawn->h) + posY;
		return y;
	}

	else
		return posY;
}


float EmiterState::GenerateSpeedX() const
{
	if (randomizeSpeedX == true)
	{
		float speedX = (rand() % particleVariationSpeed.x) + particleSpeed.x;
		return speedX;
	}

	else
		return particleSpeed.x;
}


float EmiterState::GenerateSpeedY() const
{
	if (randomizeSpeedY == true)
	{
		float speedY = (rand() % particleVariationSpeed.y) + particleSpeed.y;
		return speedY;
	}

	else
		return particleSpeed.y;

}


float EmiterState::GenerateAccelerationX() const
{
	if (randomizeAccelerationX == true)
	{
		float accX = (rand() % particleVariationAcceleration.x) + particleAcceleration.x;
		return accX;
	}

	else
		return particleAcceleration.x;
}


float EmiterState::GenerateAccelerationY() const
{
	if (randomizeAccelerationY == true)
	{
		float accY = (rand() % particleVariationAcceleration.y) + particleAcceleration.y;
		return accY;
	}

	else
		return particleAcceleration.y;
}


float EmiterState::GenerateAngularSpeed() const
{ 
	if (randomizeAngularSpeed == true)
	{
		float angularSpeed = (rand() % particleVariationAngularSpeed) + particleAngularSpeed;
		return angularSpeed;
	}

	else
		return particleAngularSpeed;
}