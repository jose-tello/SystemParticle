#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;

class Particle
{
public:
	Particle(); //The emiter uses this constructor
	Particle(float positionX, float positionY, float speedX, float speedY, float accelerationX, float accelerationY, float angle, float angularSpeed, float life, bool fade = false);
	~Particle();

	//Getters and setters
	fMPoint GetPosition();
	fMPoint GetSpeed();
	fMPoint GetAcceleration();
	
	float GetAngle();
	float GetAngularSpeed();

	float GetLife();

	void SetPosition(fMPoint &);
	void SetSpeed(fMPoint &);
	void SetAcceleration(fMPoint &);
	
	void SetAngle(float);
	void SetAngularSpeed(float);

	//the actual useful functions
	void Update(float dt);
	void GetDrawVariables(fMPoint &, float &, float &);
	
	bool IsActive();
	void Reset(float x, float y, float speedX, float speedY, float accX, float accY, float angularSpeed, float lifeTime);

private:
	void Move(float dt);

	void CheckLife(float dt);

private:

	fMPoint position; // 0 is the x axis, and 1 the y axis
	fMPoint speed;
	fMPoint acceleration;
	
	float angle;
	float angularSpeed;//positive = right, negative = left

	float life;
};

#endif //__PARTICLE_H__