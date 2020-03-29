#pragma once
#include "vector"

class Emiter;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void PushEmiter(Emiter& emiter);

	void Update(float dt);
	void PostUpdate();

	void Desactivate();
	void Activate();

	bool IsActive();

private:
	std::vector<Emiter> emiterVector;
	bool active;
};

