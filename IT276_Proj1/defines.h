#ifndef __DEFINES_H
#define __DEFINES_H

typedef int bool;
#define true 1
#define false 0
//Screen dimension constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

//dimensions of warrior
#define WAR_HEIGHT 32
#define WAR_WIDTH 32

//direction of sprite
#define WAR_RIGHT 0
#define WAR_LEFT 1
#define WAR_UP 2
#define WAR_DOWN 3

//Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

#endif