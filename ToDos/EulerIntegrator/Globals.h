#pragma once
#include <iostream>
#include "p2Log.h"
	
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#include <stdlib.h>


using namespace std;
typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long int uint64;
typedef float float32;
typedef double float64;

//Macros to change from pixel coordinates to meters and viceverse

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((double) METER_PER_PIXEL * p)

#define DEG_TO_RAD(deg) (deg * 0.0174532925199432957f)
#define RAD_TO_DEG(rad) (rad * 57.295779513082320876f)


#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )

typedef unsigned int uint;


enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};


// Configuration -----------
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE false
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "Particle system "
#define ORGANIZATION " UPC"
#define MAX_OBJECTS 150
