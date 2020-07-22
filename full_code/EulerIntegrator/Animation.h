#pragma once

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "vector"
#include "SDL/include/SDL_rect.h"
#include "Application.h"

class Frame
{
public:
	Frame(SDL_Rect rect, int pivotPosX, int pivotPosY) : frame(rect), pivotPositionX(pivotPosX), pivotPositionY(pivotPosY) {}
	SDL_Rect frame;

	int pivotPositionX;
	int pivotPositionY;
};

class Animation
{
public:
	bool loop = true;
	std::vector<Frame> frames;

private:
	float timePassed = 0;
	int maxFrames = 0;
	int currentFrame = 0;
	int loops = 0;

public:


	void PushBack(const SDL_Rect& rect, const int maxFr, int pivotPositionX, int pivotPositionY) 
	{
		for (int i = 0; i < maxFr; i++)
		{
			frames.push_back(Frame(rect, pivotPositionX, pivotPositionY));
		}
		maxFrames += maxFr;
	}


	Frame& GetCurrentFrame(float dt)
	{
		if (timePassed < maxFrames * dt)
		{
			timePassed += dt;
			currentFrame = timePassed / 0.016;
		}

		if (currentFrame >= maxFrames)
		{
			if (loop)
			{
				currentFrame = 0;
				timePassed = 0.0f;
				loops++;
			}

			else
				currentFrame = frames.size() - 1;
		}


		return frames[currentFrame];
	}


	Frame& GetFrame(float time)
	{
		float timer = time;
		int actualFrame = timer / 0.016;
		

		if (actualFrame >= maxFrames)
		{
			return frames[maxFrames - 1];
		}


		return frames[actualFrame];
	}


	SDL_Rect& GetCurrentFrameBox(float dt)
	{
		return GetCurrentFrame(dt).frame;
	}


	SDL_Rect& GetFrameBox(float time)
	{
		return GetFrame(time).frame;
	}


	SDL_Rect& GetRect()
	{
		return this->frames[0].frame;
	}


	bool Finished() const
	{
		return loops > 0;
	}


	void ResetAnimation()
	{
		timePassed = 0;
		currentFrame = 0;
	}


};

#endif
