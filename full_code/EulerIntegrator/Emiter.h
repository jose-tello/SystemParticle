#ifndef __EMITER_H__
#define __EMITER_H__

#include "vector"
#include "p2Point.h"
#include "Animation.h"
#include "EmiterState.h"

#define FPS 60
#define MSPF 16

class Particle;
struct SDL_Texture;

class Emiter
{
public:
	Emiter(fMPoint &position, fMPoint &particleSpeed, iMPoint &particleVariationSpeed, fMPoint &particleAcceleration, iMPoint& particleVariationAcceleration, 
		   float particleAngularSpeed, int particleVariableAngularSpeed, float particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture, Animation particleAnimation, bool fade, int r = 255, int g = 255, int b = 255);

	Emiter(float positionX, float positionY, float particleSpeedX, float particleSpeedY, int particleVariationSpeedX, int particleVariationSpeedY, float particleAccelerationX,
		   float particleAccelerationY, int particleVariationAccelerationX, int particleVariationAccelerationY, float particleAngularSpeed, int particleVariableAngularSpeed, 
		   float particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture, Animation particleAnimation, bool fade, int r = 255, int g = 255, int b = 255);
	
	~Emiter();

	void Update(float dt);
	void PostUpdate(float dt);

	void GetPosition(int &x, int &y);
	void SetPosition(int x, int y);

	void Activate();
	void Desactivate();

private:
	void Start();

	void ThrowParticles();
	void DrawParticles();

private:
	fMPoint position;

	std::vector<Particle> particleVector;

	SDL_Texture* particleTexture;
	Animation particleAnimation;

	float particlesEmited;
	int activeParticles;

	EmiterState state;

	bool active;
};

#endif //__EMITER_H__