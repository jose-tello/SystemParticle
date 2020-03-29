#include "ParticleSystem.h"
#include "Emiter.h"
#include "Particle.h"

ParticleSystem::ParticleSystem() :
	position{ 0, 0},
	active(true)
{}

ParticleSystem::ParticleSystem(float x, float y) :
	position{x, y},
	active(true)
{}

ParticleSystem::~ParticleSystem()
{
	emiterVector.clear();
}


void ParticleSystem::Update(float dt)
{
	if (active) 
	{
		int numEmiters = emiterVector.size();

		for (int i = 0; i < numEmiters; i++)
		{
			emiterVector[i].Update(dt);
		}
	}
}


void ParticleSystem::PostUpdate() 
{
	if (active)
	{
		int numEmiters = emiterVector.size();

		for (int i = 0; i < numEmiters; i++)
		{
			emiterVector[i].PostUpdate();
		}
	}
}


void ParticleSystem::PushEmiter(Emiter& emiter) 
{
	emiterVector.push_back(emiter);
}


void ParticleSystem::Desactivate()
{
	active = false;
}


void ParticleSystem::Activate()
{
	active = true;
}


bool ParticleSystem::IsActive()
{
	return active;
}


void ParticleSystem::Move(int x, int y)
{
	int previousX = position[0];
	int previousY = position[1];

	int xPos, yPos;

	if (active)
	{
		int numEmiters = emiterVector.size();

		for (int i = 0; i < numEmiters; i++)
		{
			emiterVector[i].GetPosition(xPos, yPos);

			xPos += x - previousX;
			yPos += y - previousY;

			emiterVector[i].SetPosition(xPos, yPos);
		}
	}

	position[0] = x;
	position[1] = y;
}