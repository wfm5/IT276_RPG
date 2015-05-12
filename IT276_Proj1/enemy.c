#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "defines.h"
#include "sprite.h"
#include "entity.h"
#include "globals.h"
#include "enemy.h"



Enemy_T* Init_Enemy(int AttackRate, int dmg, int hp, bool isplayer, char* spriteName, int Mana)
{
	Enemy_T* enemy = (Enemy_T*) malloc(sizeof(Enemy_T));
	enemy->entity = Init_Ent();
	enemy->alive = 1;
	enemy->attackRate = 1;
	enemy->health = hp;
	enemy->damage = dmg;
	enemy->isPlayer = isplayer;
	if(enemy->isPlayer)
	{
		//enemy->entity = Init_Ent();
	//Init_Position(player);
	enemy->entity->width = 32;
	enemy->entity->height = 32;

	enemy->entity->bBox.x = 31;
	enemy->entity->bBox.y = 0;
	enemy->entity->bBox.w = 31;
	enemy->entity->bBox.h = 32;

	enemy->entity->sprite = SetupSprite(spriteName, enemy->entity->bBox);
	//DressUpEntity(player->sprite, player->bBox, player);
	enemy->entity->x = 100;
	enemy->entity->y = 100;
	//enemy->entity = player;
	}
	if(!(enemy->isPlayer))
	{
		enemy->entity->width = 32;
		enemy->entity->height = 32;

		enemy->entity->bBox.x = 64;
		enemy->entity->bBox.y = 288;
		enemy->entity->bBox.w = 28;
		enemy->entity->bBox.h = 32;

		enemy->entity->sprite = SetupSprite(spriteName, enemy->entity->bBox);
		enemy->entity->x = 550;
		enemy->entity->y = 200;
	}
	//enemy->sprite = sprite;
	enemy->mana = Mana;
	//PlayerStats();
	return enemy;
}


void AttackPlayer(Enemy_T *target, Enemy_T *self)
{
	target->health = target->health - (self->damage * self->attackRate);
	if(target->health <= 0)
	{
		Death(target);
	}
}

void RegenSelf(Enemy_T *self)
{
	self->health += 2;
}

void Death(Enemy_T *self)
{
	self->alive = 0;
	if(self->isPlayer)
	{
		if((self->alive) = 0)
		{
			fprintf(stdout, "Game Over \n");
		}
	}
}