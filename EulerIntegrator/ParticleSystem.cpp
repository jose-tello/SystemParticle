#include "ParticleSystem.h"
#include "Emiter.h"
#include "Particle.h"

ParticleSystem::ParticleSystem() :
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