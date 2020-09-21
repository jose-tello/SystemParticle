#ifndef __EMMITER_STATE_H__
#define __EMMITER_STATE_H__

#include "p2Point.h"

struct SDL_Rect;

struct EmiterState
{
public:
	EmiterState(fMPoint, fMPoint, float, float, float, SDL_Rect*, iMPoint, iMPoint, int, bool, int, int, int);
	~EmiterState();

	void GenerateValues(fMPoint& emmiterPos, float& posX, float& posY, float& spX, float& spY, float& accX, float& accY, float& asp) const;

	float GetParticlesRate() const;
	float GetParticlesLifeTime() const;
	float GetParticlesPerFrame() const;

private:
	void Start();

	//GenerateFunctions
	float GeneratePosX(float) const;
	float GeneratePosY(float) const;

	float GenerateSpeedX() const;
	float GenerateSpeedY() const;

	float GenerateAccelerationX() const;
	float GenerateAccelerationY() const;

	float GenerateAngularSpeed() const;

private:

	fMPoint particleSpeed;
	fMPoint particleAcceleration;
	float particleAngularSpeed;

	float particlesRate; //per second
	float particlesLifeTime;
	float particlesPerFrame;

	SDL_Rect* areaOfSpawn; // optional
	iMPoint particleVariationSpeed;
	iMPoint particleVariationAcceleration;
	int particleVariationAngularSpeed;
	
	bool randomizePosX;
	bool randomizePosY;
	bool randomizeSpeedX;
	bool randomizeSpeedY;
	bool randomizeAccelerationX;
	bool randomizeAccelerationY;
	bool randomizeAngularSpeed;

public:
	bool fadeParticles;
	bool fadeColor;
	int rColor;
	int gColor;
	int bColor;
};

#endif//__EMMITER_STATE_H__