#ifndef __m_ENTITY__
#define __m_ENTITY__
#define MAX_ENTITIES 255
#include "sprite.h"
int maxents;

enum mEntityStates{
	mEntitySpawn = 0,
	mEntityNeutral = 1,
	mEntityAttack = 2,
	mEntityDying = 3,
	mEntityDead = 4,
};

enum mEntityShape{
	mEntityNoShape = 0,
	mEntity
};

typedef struct Entity_S{
	Uint32			id;
	Uint32			levelId;
	//char			*name;
	//float			moveSpeed;
	int				inuse;
	Sprite_T		*sprite;
	SDL_Rect		bBox;
	float			x,y;
	int				width;
	int				height;
	struct Entity_S *owner;					//**<pointer to itself*/
	void (*draw)(struct Entity_S * self);
	void (*think)(struct Entity_S * self);
	//int	thinkRate;
	//Uint32	thinkNext;
	void (*update)(struct Entity_s * self);
	void (*touch)(struct Entity_S * self,struct Entity_S * other);
	//void (*levelTouch)(struct Entity_S * self,mTrace *trace);
	void (*die)(struct Entity_S * self);
	
}Entity_T;

Entity_T entityList[MAX_ENTITIES];
Entity_T *Init_Ent(void);
void InitEntityList();
void Free_Ent(Entity_T *self);

void move(Entity_T *e);

void handle_events();
void Init_Position(Entity_T *e);
bool DrawEntity(Entity_T *e);

Entity_T *DressUpEntity(Sprite_T *s,SDL_Rect box,Entity_T *e);
//Entity_T *SetupEntity(Sprite_T *s, SDL_Rect box);
bool is_Collided(SDL_Rect a, SDL_Rect b);
void Battle_Positions(Entity_T *e);
#endif
