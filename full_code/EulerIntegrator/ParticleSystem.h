#ifndef __PARTICLE_SYSTEM_H__
#define __PARTICLE_SYSTEM_H__

#include "p2Point.h"
#include "vector"

class Emiter;

class ParticleSystem
{
public:
	ParticleSystem();
	ParticleSystem(float x, float y);

	~ParticleSystem();

	void PushEmiter(Emiter& emiter);

	void Update(float dt);
	void PostUpdate(float dt);

	void Desactivate();
	void Activate();

	bool IsActive();

	void Move(int x, int y);

private:
	std::vector<Emiter> emiterVector;
	fMPoint	position;

	bool active;
};

#endif //__PARTICLE_SYSTEM_H__