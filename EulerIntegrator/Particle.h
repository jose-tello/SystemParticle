#pragma once

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "vector"

struct SDL_Texture;

class Particle
{
public:
	Particle();
	Particle(std::vector<int> &position, std::vector<int> &speed, std::vector<int> &acceleration, float angle, float angularSpeed, float life, SDL_Texture *texture);
	Particle(int positionX, int positionY, int speedX, int speedY, int accelerationX, int accelerationY, float angle, float angularSpeed, float life, SDL_Texture* texture);
	~Particle();

	std::vector<int> GetPosition();
	std::vector<int> GetSpeed();
	std::vector<int> GetAcceleration();
	
	float GetAngle();
	float GetAngularSpeed();


	void SetPosition(std::vector<int> &);
	void SetSpeed(std::vector<int> &);
	void SetAcceleration(std::vector<int> &);
	
	void SetAngle(float);
	void SetAngularSpeed(float);


	void Update(float dt);
	void PostUpdate();

private:
	void Move(float dt);
	void CheckLife(float dt);
	void Draw();

private:
	SDL_Texture* texture;

	std::vector<int> position; // 0 is the x axis, and 1 the y axis
	std::vector<int> speed;
	std::vector<int> acceleration;
	
	float angularSpeed;//positive = right, negative = left
	float angle;

	float life;
};

#endif //__PARTICLE_H__