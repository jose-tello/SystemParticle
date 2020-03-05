#pragma once

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "vector"

struct SDL_Texture;

class Particle
{
public:
	Particle();
	Particle(std::vector<int> position, std::vector<int> speed, std::vector<int> acceleration, float angle, float angularSpeed, float life, SDL_Texture *texture);
	Particle(int positionX, int positionY, int speedX, int speedY, int accelerationX, int accelerationY, float angle, float angularSpeed, float life, SDL_Texture* texture);
	~Particle();

	//Getters and setters
	std::vector<int> GetPosition();
	std::vector<int> GetSpeed();
	std::vector<int> GetAcceleration();
	
	float GetAngle();
	float GetAngularSpeed();

	float GetLife();
	SDL_Texture* GetTexture();

	void SetPosition(std::vector<int> &);
	void SetSpeed(std::vector<int> &);
	void SetAcceleration(std::vector<int> &);
	
	void SetAngle(float);
	void SetAngularSpeed(float);

	//the actual useful functions
	void Update(float dt);
	void PostUpdate();
	
	bool Activate();
private:
	void Move(float dt);
	void Draw();

	void CheckLife(float dt);
	void Desactivate();
	
	void Restart();

private:
	SDL_Texture* texture;

	std::vector<int> position; // 0 is the x axis, and 1 the y axis
	std::vector<int> speed;
	std::vector<int> acceleration;

	std::vector<int> originalPosition;
	std::vector<int> originalSpeed;
	
	float angularSpeed;//positive = right, negative = left
	float angle;

	float life;
	float originalLife;
	bool active;
};

#endif //__PARTICLE_H__