#include "ParticleSystem.h"
#include "Emiter.h"
#include "Particle.h"

ParticleSystem::ParticleSystem()
{}


ParticleSystem::~ParticleSystem()
{
	emiterVector.clear();
}


void ParticleSystem::Update(float dt)
{
	int numEmiters = emiterVector.size();

	for (int i = 0; i < numEmiters; i++)
	{
		emiterVector[i].Update(dt);
	}
}


void ParticleSystem::PostUpdate() 
{
	int numEmiters = emiterVector.size();

	for (int i = 0; i < numEmiters; i++)
	{
		emiterVector[i].PostUpdate();
	}
}


void ParticleSystem::PushEmiter(Emiter& emiter) 
{
	emiterVector.push_back(emiter);
}