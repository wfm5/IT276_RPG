#include<sdl.h>

int main (int argc,char* argv[]) //ran after SDL main
{
	SDL_Surface* Screen; //reference to SDL_Surface
	SDL_Init(SDL_INIT_EVERYTHING); //inits everything for sdl
	Screen = SDL_SetVideoMode(800,600,32,SDL_SWSURFACE); //sets the size of window. SDL_SWSurface makes the Software handle the graphics
	SDL_Delay(10000); //delays in milliseconds 1000 = 1sec
	SDL_FreeSurface(Screen); //clean up frees data
	SDL_Quit(); //closes window
	return 0;
}