#pragma once

#ifndef __ANIMATION_H__
#define __ANIMATION_H__


#include "SDL/include/SDL_rect.h"
#include "Application.h"
#include "Frame.h"
#include "vector"

class Animation
{
public:
	void PushBack(const SDL_Rect& rect, const int maxFr, int pivotPositionX, int pivotPositionY);

	Frame& GetCurrentFrame(float dt);
	Frame& GetFrame(float time);

	SDL_Rect& GetCurrentFrameBox(float dt);
	SDL_Rect& GetFrameBox(float time);

	SDL_Rect& GetRect();

	bool Finished() const;
	void ResetAnimation();

public:
	bool loop = true;
	std::vector<Frame> frames;

private:
	float timePassed = 0.0f;
	int maxFrames = 0;
	int currentFrame = 0;

};

#endif
