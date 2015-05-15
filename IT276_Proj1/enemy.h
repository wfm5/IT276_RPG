#ifndef __Enemy__
#define __Enemy__

#include "entity.h"
#include "sprite.h"

typedef struct Enemy_S{
	Entity_T *entity;
	Sprite_T *sprite;
	int attackRate;
	int health;
	int damage;
	int mana;
	struct Enemy_S *self;
	bool alive;
	bool isPlayer;

}Enemy_T;

Enemy_T* Init_Enemy(int AttackRate, int dmg, int health, bool isplayer, char* spriteName, int Mana, int level);
void AttackPlayer(Enemy_T *target, Enemy_T *self);
void AttackPlayer2(Enemy_T *target, Enemy_T *self);
void RegenSelf(Enemy_T *self);
void Death(Enemy_T *self);
void PowerUp(Enemy_T *self);
void PowerUp2(Enemy_T *self);
//void DeathPlayer();

#endif