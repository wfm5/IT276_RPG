#ifndef __SPRITE__
#define __SPRITE__

typedef struct Sprite_S{
	SDL_Surface *img;
	SDL_Rect size;
	char filename[20];
	int w,h;
	int used;
	int framesperline;
}Sprite_T;

void InitSpriteList();
void CloseSprites();
void DrawSprite(Sprite_T *sprite,SDL_Surface *surface,int sx,int sy, int frame);
Sprite_T *LoadSprite(char *filename,int sizex, int sizey);
Sprite_T *DressUpSprite(char *file, SDL_Rect size);
Sprite_T *SetupSprite(char *file, SDL_Rect size);

#endif