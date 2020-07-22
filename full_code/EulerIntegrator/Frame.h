#ifndef __FRAME_H__
#define __FRAME_H__

class Frame
{
public:
	Frame(SDL_Rect rect, int pivotPosX, int pivotPosY) : frame(rect), pivotPositionX(pivotPosX), pivotPositionY(pivotPosY) {}
	SDL_Rect frame;

	int pivotPositionX;
	int pivotPositionY;
};

#endif //__FRAME_H__