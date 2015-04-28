#include <string.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "defines.h"
#include "sprite.h"
#include "entity.h"
#include "globals.h"

#define MaxSprites 255

Sprite_T SpriteList[MaxSprites];
int NumSprites;

Sprite_T *SetupSprite(char *file, SDL_Rect size)
{
	Sprite_T *sprite = (Sprite_T *)malloc(sizeof(Sprite_T)); //load sprite's memory
	sprite->img = IMG_Load(file); //load file
	sprite->size = size; //
	return sprite;
}

void InitSpriteList()
{
	int x;
	NumSprites = 0;
	memset(SpriteList,0,sizeof(Sprite_T) * MaxSprites);
}

void DrawSprite(Sprite_T *sprite,SDL_Surface *surface,int sx,int sy, int frame)
{
  SDL_Rect src,dest;
  if ((!sprite)||(!surface))return;
  src.x = frame%sprite->framesperline * sprite->w;
  src.y = frame/sprite->framesperline * sprite->h;
  src.w = sprite->w;
  src.h = sprite->h;
  dest.x = sx;
  dest.y = sy;
  dest.w = sprite->w;
  dest.h = sprite->h;
  SDL_BlitSurface(sprite->img, &src, surface, &dest);  
}

Sprite_T *LoadSprite(char *filename,int sizex, int sizey)
{
	int i;
	SDL_Surface *temp;
	/*first search to see if the requested sprite image is alreday loaded*/
	for(i = 0; i < MaxSprites; i++)
	{
		if(strncmp(filename,SpriteList[i].filename,20)==0)
		{
			SpriteList[i].used++;
			return &SpriteList[i];
		}
	}
	
	/*makesure we have the room for a new sprite*/
	if(NumSprites + 1 >= MaxSprites)
	{
		fprintf(stderr, "Maximum Sprites Reached.\n");
		exit(1);
	}
	/*if its not already in memory, then load it.*/
	NumSprites++;
	for(i = 0;i <= NumSprites;i++)
	{
		if(!SpriteList[i].used)break;
	}
	temp = IMG_Load(filename);
	if(temp == NULL)
	{
		fprintf(stderr,"unable to load a vital sprite: %s\n",SDL_GetError());
		exit(0);
	}
	SpriteList[i].img = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	/*sets a transparent color for blitting.*/
	//SDL_SetColorKey(SpriteList[i].img, SDL_SRCCOLORKEY , SDL_MapRGB(SpriteList[i].img->format, 255,255,255));
	/*then copy the given information to the sprite*/
	strncpy(SpriteList[i].filename,filename,20);
	/*now sprites don't have to be 16 frames per line, but most will be.*/
	SpriteList[i].framesperline = 16;
	SpriteList[i].w = sizex;
	SpriteList[i].h = sizey;
	SpriteList[i].used++;
	return &SpriteList[i];
}

void FreeSprite(Sprite_T *sprite)
{
/*first lets check to see if the sprite is still being used.*/
sprite->used--;
if(sprite->used == 0)
{
strcpy(sprite->filename,"\0");
/*just to be anal retentive, check to see if the image is already freed*/
if(sprite->img != NULL)SDL_FreeSurface(sprite->img);
sprite->img = NULL;
}
/*and then lets make sure we don't leave any potential seg faults
lying around*/
}
void CloseSprites()
{
	int i;
	for(i = 0;i < MaxSprites;i++)
	{
		/*it shouldn't matter if the sprite is already freed,
		FreeSprite checks for that*/
		FreeSprite(&SpriteList[i]);
	}
}