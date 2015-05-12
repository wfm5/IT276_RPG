//#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "defines.h"
#include "mouse.h"
#include "sprite.h"
#include "entity.h"

extern SDL_Surface *Screen;

Sprite_T *Msprite;


struct
{
  Uint32 state;
  Uint32 shown;
  Uint32 frame;
  Uint16  x, y;
}Mouse;


/*mouse handling functions*/
/*this only handles the drawing and animation of.  Assuming you have a 16 by 16  tiled sprite sheet.  This will not handle input*/
void InitMouse()
{
	FILE *file;
	Msprite = LoadSprite("mouse.png",16, 16);
	if(Msprite == NULL)
	{
		file = fopen("output.txt","w");
		fprintf(file,"mouse didn't load\n");
		return;
	}
	mx = 0;
	my = 0;
	Mouse.state = 0;
	Mouse.shown = 1;
	Mouse.frame = 0;
}
int checkClick(Entity_T *b)
{
	if(mouseHover(b->x,b->y,b->width,b->height))
	{
		if(clickLeft)return 1;
	}
	return 0;
}
/*draws to the screen immediately before the blit, after all
 *     it wouldn't be a very good mouse if it got covered up by the
 *     game content*/
void DrawMouse()
{
  SDL_GetMouseState(&mx,&my);
  if(Msprite != NULL) DrawSprite(Msprite,Screen,mx,my,Mouse.frame);
  Mouse.frame = (Mouse.frame + 1)%16;
  Mouse.x = mx;
  Mouse.y = my;
}
void mouseThink()
{
	SDL_GetMouseState(&mx,&my);
	if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) //if clicked 
	{
		clickLeft = true;
		clickRight = false;
	}
	else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		clickLeft = 0;
		clickRight = 1;
	}
	else
	{
		clickLeft = 0;
		clickRight = 0;
		stopClick = 0;
	}
}
int mouseHover(int x, int y, int w, int h)
{
	if((mx > x) && (mx < x + w) && (my > y) && (my < y + h))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}