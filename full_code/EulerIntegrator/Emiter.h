#ifndef __EMITER_H__
#define __EMITER_H__

#include "vector"
#include "p2Point.h"
#include "Animation.h"

#define FPS 60
#define MSPF 16

class Particle;
struct SDL_Texture;

class Emiter
{
public:
	Emiter(fMPoint &position, fMPoint &particleSpeed, iMPoint &particleVariationSpeed, fMPoint &particleAcceleration, iMPoint& particleVariationAcceleration, 
		   float particleAngularSpeed, int particleVariableAngularSpeed, float particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture, Animation particleAnimation, bool fade);

	Emiter(float positionX, float positionY, float particleSpeedX, float particleSpeedY, int particleVariationSpeedX, int particleVariationSpeedY, float particleAccelerationX,
		   float particleAccelerationY, int particleVariationAccelerationX, int particleVariationAccelerationY, float particleAngularSpeed, int particleVariableAngularSpeed, 
		   float particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture, Animation particleAnimation, bool fade);
	
	~Emiter();

	void Update(float dt);
	void PostUpdate(float dt);

	void GetPosition(int &x, int &y);
	void SetPosition(int x, int y);

	void Activate();
	void Desactivate();

private:
	void Start();

	void CreateParticle();
	void ThrowParticles();
	void DrawParticles();

	//Generate functions, used in ThrowParticles
	float GeneratePosX();
	float GeneratePosY();

	float GenerateSpeedX();
	float GenerateSpeedY();
	
	float GenerateAccelerationX();
	float GenerateAccelerationY();

	float GenerateAngularSpeed();

private:
	fMPoint position;
	fMPoint particleSpeed;
	fMPoint particleAcceleration;

	float particleAngularSpeed;

	iMPoint particleVariationSpeed;
	iMPoint particleVariationAcceleration;
	int particleVariationAngularSpeed;


	std::vector<Particle> particleVector;

	SDL_Rect *areaOfSpawn; //Optional
	SDL_Texture* particleTexture;
	Animation particleAnimation;

	float particlesRate; //per second
	float particlesLifeTime;
	float particlesPerFrame;

	float particlesEmited;
	int activeParticles;

	bool randomizePosX;
	bool randomizePosY;

	bool randomizeSpeedX;
	bool randomizeSpeedY;

	bool randomizeAccelerationX;
	bool randomizeAccelerationY;

	bool randomizeAngularSpeed;

	bool fadeParticles;

	bool active;
};

#endif //__EMITER_H__