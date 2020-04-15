#pragma once
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
	std::vector<float>	position;

	bool active;
};

