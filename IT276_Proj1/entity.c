#include <string.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "defines.h"
#include "sprite.h"
#include "entity.h"
#include "globals.h"
#include "enemy.h"

int NumEntity;

extern Enemy_T* Player;
/*void InitEntityList()
{
	int x;
	NumEntity = 0;
	memset(entityList,0,sizeof(Entity_T) * MAX_ENTITIES);
	for(x = 0;x < MAX_ENTITIES;x++) 
		entityList[x] = NULL;
}*/
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
			return ent;
		}
	}
	return NULL;
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
		case SDLK_UP: ((Enemy_T*)Player)->entity->y -= WAR_HEIGHT ; printf("%d y \n", ((Enemy_T*)Player)->entity->bBox); break;
		case SDLK_DOWN: ((Enemy_T*)Player)->entity->y += WAR_HEIGHT ; printf("%d y \n", ((Enemy_T*)Player)->entity->bBox); break;
		case SDLK_LEFT: ((Enemy_T*)Player)->entity->x -= WAR_HEIGHT ; printf("%d x \n", ((Enemy_T*)Player)->entity->bBox); break;
			case SDLK_RIGHT: ((Enemy_T*)Player)->entity->x += WAR_HEIGHT ; printf("%d x \n", ((Enemy_T*)Player)->entity->bBox); break;
		}			
	}// probably should check key up there
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
	if (!e)return 0;
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
void Battle_Positions(Entity_T *e)
{
	e->x = 200;
	e->y = 200;
	fprintf(stdout,"Battle Start \n");
	//DrawEntity(enemy1)
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
//void touchButton(Entity_S * self,struct Entity_S * other){
//}
//bool check_Collisions(Entity_T *e)