#include <string.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "globals.h"
#include "sprite.h"
#include "entity.h"


Sprite_T *SetupSprite(char *file, SDL_Rect size)
{
	Sprite_T *sprite = (Sprite_T *)malloc(sizeof(Sprite_T));
	sprite->img = IMG_Load("warrior.png");
	sprite->size = size;
	return sprite;
}
Entity_T *SetupEntity(Sprite_T *s, SDL_Rect box)
{
	Entity_T *e = (Entity_T *)malloc(sizeof(Entity_T));	
	e->bBox = box;
	e->sprite = s;
	return e;
}
bool DrawEntity(Entity_T *e)
{
	SDL_Rect dst;
	dst.x = e->bBox.x;
	dst.y = e->bBox.y;
	dst.w = e->sprite->size.w;
	dst.h = e->sprite->size.h;
	SDL_BlitSurface(e->sprite->img, &e->sprite->size, Screen, &dst);
	return true;
}
//bool check_Collisions(Entity_T *e)