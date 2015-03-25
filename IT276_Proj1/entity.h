#ifndef __m_ENTITY__
#define __m_ENTITY__


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
	char			*name;
	float			moveSpeed;
	Sprite_T		*sprite;
	SDL_Rect		bBox;
	struct Entity_S *self;					//**<pointer to itself*/
	void (*draw)(struct Entity_S * self);
	void (*think)(struct Entity_S * self);
	int	thinkRate;
	Uint32	thinkNext;
	void (*update)(struct Entity_s * self);
	void (*touch)(struct Entity_S * self,struct Entity_S * other);
	//void (*levelTouch)(struct Entity_S * self,mTrace *trace);
	void (*die)(struct Entity_S * self);
	
}Entity_T;


bool DrawEntity(Entity_T *e);
Sprite_T *SetupSprite(char *file, SDL_Rect size);
Entity_T *SetupEntity(Sprite_T *s, SDL_Rect box);
//void FreeEnt(Entity_T *e)
#endif
