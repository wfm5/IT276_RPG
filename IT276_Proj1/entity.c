#include <string.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "defines.h"
#include "sprite.h"
#include "entity.h"
#include "globals.h"

Entity_T *Init_Ent(void)
{
	int i;

	Entity_T *ent;
	
	for(i=0; i< maxents+1; i++)
	{
		if(entityList[i].inuse == 0)
		{
			ent = &entityList[i];
			ent->inuse = 1;
			maxents++;
		}
		else if(maxents < MAX_ENTITIES)
		{
			ent = &entityList[maxents++];
			ent->inuse = 1;
		}
		else if(i == maxents)
		{
			SDL_Delay(8000);
			fprintf(stdout,"No more room for Entities\n");
			exit(1);
			return 0;
		}
		return ent;
	}
}
void Free_Ent(Entity_T *owner)
{
	owner->inuse = 0;
}
void handle_events()
{
	if( e.type == SDL_KEYDOWN)
	{
		//Set the proper message surface
		switch( e.key.keysym.sym )
		{
			//PumpEvents
			case SDLK_UP: player->y -= WAR_HEIGHT ; printf("%d y \n", player->y); break;
		    case SDLK_DOWN: player->y += WAR_HEIGHT ; printf("%d y \n", player->y); break;
			case SDLK_LEFT: player->x -= WAR_HEIGHT ; printf("%d x \n", player->x); break;
			case SDLK_RIGHT: player->x += WAR_HEIGHT ; printf("%d x \n", player->x); break;
		}			
	}
}
Sprite_T *SetupSprite(char *file, SDL_Rect size)
{
	Sprite_T *sprite = (Sprite_T *)malloc(sizeof(Sprite_T)); //load sprite's memory
	sprite->img = IMG_Load(file); //load file
	sprite->size = size; //
	return sprite;
}
Entity_T *DressUpEntity(Sprite_T *s, SDL_Rect box, Entity_T *e)
{
		//Entity_T *e = (Entity_T *)malloc(sizeof(Entity_T)); //allocates memory for entity

		e->bBox = box; //spawns bounding box
		e->sprite = s; //sets sprite to entity
		return e;
}
bool DrawEntity(Entity_T *e)
{
	//draws sprites
	SDL_Rect dst;
	dst.x = e->x;
	dst.y = e->y;
	dst.w = e->sprite->size.w;
	dst.h = e->sprite->size.h;
	e->bBox.x = dst.x;
	e->bBox.y = dst.y;
	SDL_BlitSurface(e->sprite->img, &e->sprite->size, Screen, &dst);
	return true;
}
void Init_Position(Entity_T *e)
{
	e->x = 128;
	e->y = 128;
}
bool is_Collided(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

 //If any of the sides from A are outside of B 
	/*if((a.x + a.w >= b.x) && (a.x <= b.x + b.w) && (a.y + a.h >= b.y) && (a.y <= b.y + b.h))
	{	
		fprintf(stdout, "its true collided \n");
		return true;  
	}
	fprintf(stdout, "its false no collide \n");
	fprintf(stdout, "doorX: %d  \n", b.x);
	fprintf(stdout, "doorY: %d  \n", b.y);
	return false;
	*/
	if( bottomA <= topB ) 
	{ 
		return false; 
	} 
	if( topA >= bottomB ) 
	{ 
		return false; 
	} 
	if( rightA <= leftB ) 
	{ 
		return false; 
	} 
	if( leftA >= rightB ) 
	{ 
		return false; 
	}
	//If none of the sides from A are outside B 
	return true; 
}
//bool check_Collisions(Entity_T *e)