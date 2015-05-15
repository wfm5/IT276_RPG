#ifndef __GLOBALS_H
#define __GLOBALS_H

extern SDL_Surface* Screen;
extern SDL_Event e;
 // extern so that all files will know it exists
extern bool IN_BATTLE;
// ewwwwww extern in header
// wfm5: causes too many problems to take it out I can optimize it another time
#endif //__GLOBALS_H