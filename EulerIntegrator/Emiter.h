#pragma once

#include "vector"


class Particle;
struct SDL_Rect;
struct SDL_Texture;

class Emiter
{
public:
	Emiter(std::vector<Particle> &particleSamples, std::vector<int> &position, std::vector<int> &speedOfParticles, std::vector<int> &accelerationOfParticles, float particleAngularSpeed, SDL_Rect* areaOfSpawn, SDL_Texture* texture);
	~Emiter();

	void Update(float);
	void PostUpdate();

private:
	void ThrowParticles();
	void Draw();

private:
	std::vector<int> position;
	std::vector<int> speedOfParticles;
	std::vector<int> accelerationOfParticles;

	float particleAngularSpeed;

	std::vector<Particle> particleSamples;
	std::vector<Particle> particleVector;

	SDL_Rect *areaOfSpawn;
	SDL_Texture* texture; //Optional

	int particlesPerFrame;
};
