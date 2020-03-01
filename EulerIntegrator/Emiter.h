#pragma once

#include "vector"


class Particle;
struct SDL_Rect;
struct SDL_Texture;

class Emiter
{
public:
	Emiter(std::vector<int> &position, std::vector<int> &speedOfParticles, std::vector<int> &accelerationOfParticles, float particleAngularSpeed, int particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture);
	~Emiter();

	void Update(float);
	void PostUpdate();

private:
	void Start();
	void ThrowParticles();

private:
	std::vector<int> position;
	std::vector<int> speedOfParticles;
	std::vector<int> accelerationOfParticles;

	float particleAngularSpeed;

	std::vector<Particle> particleVector;

	SDL_Rect *areaOfSpawn; //Optional
	SDL_Texture* particleTexture;

	int particlesRate; //per frame
	float particlesLifeTime;
};
