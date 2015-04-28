#ifndef __GLOBALS_H
#define __GLOBALS_H


extern SDL_Surface* Screen;
extern SDL_Event e;
extern Entity_T *player; // extern so that all files will know it exists
extern bool IN_BATTLE;

#endif //__GLOBALS_H