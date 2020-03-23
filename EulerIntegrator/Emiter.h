#pragma once

#include "vector"

#define FPS 60
class Particle;
struct SDL_Rect;
struct SDL_Texture;

class Emiter
{
public:
	Emiter(std::vector<float> &position, std::vector<float> &particleSpeed, std::vector<int> &particleVariationSpeed, std::vector<float> &particleAcceleration, 
		   std::vector<int>& particleVariationAcceleration, float particleAngularSpeed, int particleVariableAngularSpeed, int particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture);

	Emiter(float positionX, float positionY, float particleSpeedX, float particleSpeedY, int particleVariationSpeedX, int particleVariationSpeedY, float particleAccelerationX,
		float particleAccelerationY, int particleVariationAccelerationX, int particleVariationAccelerationY, float particleAngularSpeed, int particleVariableAngularSpeed, int particlesRate, float particlesLifeTime, 
		SDL_Rect* areaOfSpawn, SDL_Texture* texture);
	
	~Emiter();

	void Update(float);
	void PostUpdate();

	void GetPosition(std::vector<float>&);
	void SetPosition(std::vector<float>*);

private:
	void Start();
	void CreateParticle();
	void ThrowParticles();

	float GeneratePosX();
	float GeneratePosY();

	float GenerateSpeedX();
	float GenerateSpeedY();
	
	float GenerateAccelerationX();
	float GenerateAccelerationY();

	float GenerateAngularSpeed();

private:
	std::vector<float> position;
	std::vector<float> particleSpeed;
	std::vector<float> particleAcceleration;

	float particleAngularSpeed;

	std::vector<int> particleVariationSpeed;
	std::vector<int> particleVariationAcceleration;
	int particleVariationAngularSpeed;


	std::vector<Particle> particleVector;

	SDL_Rect *areaOfSpawn; //Optional
	SDL_Texture* particleTexture;

	int particlesRate; //per frame
	float particlesLifeTime;

	bool randomizePos;
	bool randomizeSpeed;
	bool randomizeAcceleration;
	bool randomizeAngularSpeed;

};
