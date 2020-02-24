#pragma once

#include "vector"
#include "Particle.h"

struct SDL_Rect;
struct SDL_Texture;

class Emiter
{
public:
	Emiter(vector<Particle> &, vector<int> &, vector<int> &, vector<int> &, SDL_Rect *, SDL_Texture *);
	~Emiter();

	void Update();
	void PostUpdate();

private:
	void ThrowParticles();

private:
	std::vector<int> position;
	std::vector<int> speedOfParticles;
	std::vector<int> accelerationOfParticles;

	std::vector<Particle> particleSamples;
	std::vector<Particle> particleVector;

	SDL_Rect *areaOfSpawn;
	SDL_Texture* texture; //Optional
};
