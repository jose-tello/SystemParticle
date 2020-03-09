#pragma once

#include "vector"


class Particle;
struct SDL_Rect;
struct SDL_Texture;

class Emiter
{
public:
	Emiter(std::vector<int> &position, std::vector<int> &particleSpeed, std::vector<int> &particleVariationSpeed, std::vector<int> &particleAcceleration, float particleAngularSpeed, int particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture);
	Emiter(int positionX, int positionY, int particleSpeedX, int particleSpeedY, int particleVariationSpeedX, int particleVariationSpeedY, int particleAccelerationX, int particleAccelerationY, float particleAngularSpeed, int particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture);
	~Emiter();

	void Update(float);
	void PostUpdate();

private:
	void Start();
	void CreateParticle();
	void ThrowParticles();


private:
	std::vector<int> position;
	std::vector<int> particleSpeed;
	std::vector<int> particleAcceleration;

	std::vector<int> particleVariationSpeed;

	float particleAngularSpeed;

	std::vector<Particle> particleVector;

	SDL_Rect *areaOfSpawn; //Optional
	SDL_Texture* particleTexture;

	int particlesRate; //per frame
	float particlesLifeTime;
};
