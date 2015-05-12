#ifndef __MOUSE__
#define __MOUSE__

#include "SDL.h"
#include "entity.h"

int mx;
int my;
bool clickLeft;
bool clickRight;
bool stopClick;

void InitMouse();
void DrawMouse();
int checkClick(Entity_T *b);
void mouseThink();
int mouseHover(int x, int y, int w, int h);

#endif