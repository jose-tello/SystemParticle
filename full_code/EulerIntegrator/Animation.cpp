#include "Animation.h"

void Animation::PushBack(const SDL_Rect& rect, const int maxFr, int pivotPositionX, int pivotPositionY)
{
	for (int i = 0; i < maxFr; i++)
	{
		frames.push_back(Frame(rect, pivotPositionX, pivotPositionY));
	}
	maxFrames += maxFr;
}


Frame& Animation::GetCurrentFrame(float dt)
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


Frame& Animation::GetFrame(float time)
{
	float timer = time;
	int actualFrame = timer / 0.016;


	if (actualFrame >= maxFrames)
	{
		if (loop)
		{
			actualFrame = actualFrame % maxFrames;
		}
		else
			actualFrame = maxFrames - 1;
	}

	return frames[actualFrame];
}


SDL_Rect& Animation::GetCurrentFrameBox(float dt)
{
	return GetCurrentFrame(dt).frame;
}


SDL_Rect& Animation::GetFrameBox(float time)
{
	return GetFrame(time).frame;
}


SDL_Rect& Animation::GetRect()
{
	return this->frames[0].frame;
}


bool Animation::Finished() const
{
	return loops > 0;
}


void Animation::ResetAnimation()
{
	timePassed = 0.0f;
	currentFrame = 0;
}