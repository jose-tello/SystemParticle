#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;

class Particle
{
public:
	Particle();
	Particle(float life, SDL_Texture* texture, Animation animation, bool fade = false); //The emiter uses this constructor
	Particle(float positionX, float positionY, float speedX, float speedY, float accelerationX, float accelerationY, float angle, float angularSpeed, float life, SDL_Texture* texture, Animation animation, bool fade = false);
	~Particle();

	//Getters and setters
	fMPoint GetPosition();
	fMPoint GetSpeed();
	fMPoint GetAcceleration();
	
	float GetAngle();
	float GetAngularSpeed();

	float GetLife();
	SDL_Texture* GetTexture();

	void SetPosition(fMPoint &);
	void SetSpeed(fMPoint &);
	void SetAcceleration(fMPoint &);
	
	void SetAngle(float);
	void SetAngularSpeed(float);

	//the actual useful functions
	void Update(float dt);
	void PostUpdate(float dt);
	
	bool Activate();
	void Reset(float x, float y, float speedX, float speedY, float accX, float accY, float angularSpeed);
	void Desactivate();

private:
	void Move(float dt);
	void Draw(float dt);

	void CheckLife(float dt);

private:
	SDL_Texture* texture;
	Animation animation;

	fMPoint position; // 0 is the x axis, and 1 the y axis
	fMPoint speed;
	fMPoint acceleration;
	
	float angle;
	float angularSpeed;//positive = right, negative = left

	float life;
	float originalLife;

	bool fade;
	bool active;
};

#endif //__PARTICLE_H__