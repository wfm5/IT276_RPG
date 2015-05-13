#include <SDL.h>
#include <SDL_image.h>
#include "defines.h"
#include "sprite.h"
#include "entity.h"
#include "globals.h"
#include "mouse.h"
#include "enemy.h"
#include "SDL_ttf.h"
#define black_	0x000000

SDL_Rect heroRect;
//The images that correspond to a keypress 
//SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];
//reference to SDL_Surface
SDL_Surface* Screen;
SDL_Surface* oworld;

SDL_Color color={0,0,0};
TTF_Font *font;
SDL_Surface *text_surface;
//event variable
Entity_T *ent;
Enemy_T *Player;
Enemy_T *Pig;
Enemy_T *Pig2;
Entity_T *menu;
Entity_T *doorEnt;
SDL_Event e;


int offSet; 
int MAP_FLAG;
bool IN_BATTLE;
	
//Handles input 
void handle_events(); 
void updateGame();
/*void move(Entity_T *ent)
{

	ent->x += ent->xVel;

	if( ( ent->x < 0 ) || ( ent->x + (float)ent->width > SCREEN_WIDTH ) ) 
	{ 
		ent->x -= ent->xVel; 
	}

	ent->y += ent->yVel;

	if((ent->y < 0) || (ent->y + (float)ent->height > SCREEN_HEIGHT))
	{
		ent->y -= ent->xVel;
	}
}*/
void load_battle()
{
	if(MAP_FLAG == 15)
	{
		oworld = IMG_Load("BattleMap1.png");
		MAP_FLAG &= ~1; 
		//fprintf(stdout, "%d",MAP_FLAG);
	}
}
void load_map2()
{
	if(MAP_FLAG == 14)
	{
		oworld = IMG_Load("BattleMap2.png");
		MAP_FLAG &= ~2;
		//fprintf(stdout, "%d",MAP_FLAG);
	}
}
void load_map3()
{
	if(MAP_FLAG == 12)
	{
		oworld = IMG_Load("BattleMap3.png");
		MAP_FLAG &= ~4;
		fprintf(stdout, "%d",MAP_FLAG);
	}
}

void HandleInput()
{
  Uint8 buttons;
  int x,y;
  buttons = SDL_GetMouseState(&x,&y);
  if (buttons)
  {
	if(checkClick(menu))
	{
		fprintf(stdout,"Clicky");//activate button
	}
  }
}

/*bool load_files()//USE THIS TO HANDLE SPRITES LATER ON. TAKE A SPRITE AND A VARIABLE AND PUT SPRITE ON VARI
{
    //Load the sprite sheet
    wa = IMG_Load( "warrior.png" );
	//heroRect.x = 0;
	//heroRect.y = 0;
	//heroRect.w = 0;
	//heroRect.h = 0;

    //If there was a problem in loading the sprite
    if( wa == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}*/

void updateGame()
{
	if(!(text_surface=TTF_RenderText_Solid(font,"Hello World!",color))) 
	{
    //handle error here, perhaps print TTF_GetError at least
	}else 
	{
    SDL_BlitSurface(text_surface,NULL,Screen,NULL);
    //perhaps we can reuse it, but I assume not for simplicity.
    SDL_FreeSurface(text_surface);
	}

	mouseThink();
	if(is_Collided(((Enemy_T*)Player)->entity->bBox, doorEnt->bBox))
	{
		fprintf(stdout, "entered door\n");
		if(MAP_FLAG == 15)
		{
			IN_BATTLE = true;
			load_battle();
			Battle_Positions(((Enemy_T*)Player)->entity);
		}
		else if(MAP_FLAG == 14)
		{
			load_map2();
			Init_Position(((Enemy_T*)Player)->entity);
		}
		else if(MAP_FLAG == 12)
		{
			load_map3();
		}
		else
		{
			return;
		}
	}
	if(Pig->health <= 0)
	{
		Death(Pig);
		load_map2();
	}
	if(mouseHover(menu->bBox.x,menu->bBox.y,menu->bBox.w,menu->bBox.h))
	{
		//fprintf(stdout,"its over boy \n");
		if(clickLeft)
		{
			
			if(Player->alive = true)
			{
				fprintf(stdout,"player attacks \n");
				if(Pig->alive)
				{
					AttackPlayer(Pig,Player);
					fprintf(stdout,"Player hit Pig for: %d \n",Player->damage);
					fprintf(stdout,"Pig Health Remaining: %d \n \n", Pig->health);
				}
			}

			fprintf(stdout,"enemy attacks back \n");

			if(Pig->alive)
			{
				AttackPlayer(Player,Pig);
				fprintf(stdout,"Pig hit player for: %d \n \n",Pig->damage);
				fprintf(stdout,"Player Health Remaining: %d \n \n", Player->health);
			}			
		}
	}
}
void DrawGame()
{
		SDL_BlitSurface(oworld,NULL,Screen,NULL);
		DrawEntity(((Enemy_T*)Player)->entity);
		DrawEntity(doorEnt);
		if(IN_BATTLE == true)
		{ 
			DrawEntity(menu);
			if(MAP_FLAG == 14)
			{
				if(Pig->alive)
				{
					DrawEntity(Pig->entity);
				}
			}
			if(MAP_FLAG == 12)
			{
				if(Pig2->alive)
				{
					DrawEntity(Pig2->entity);
				}
			}
			
		}
		DrawMouse(); //turn off the mouse
		//update it
		SDL_Flip(Screen);
		SDL_FillRect(Screen,NULL, black_); //clears the screen for next frame
}
void CleanUpAll()
{
	CloseSprites();
/*any other cleanup functions can be added here*/
}

void Init_All()
{
	SDL_Init(SDL_INIT_EVERYTHING); //inits everything for sdl
	//InitEntityList();
	InitSpriteList();
	InitMouse();	
	atexit(CleanUpAll);
	
}
int main (int argc,char* argv[]) //ran after SDL main
{
	int quit;
//	SDL_Rect playerRect;
	SDL_Rect door;
	SDL_Rect Abutton;
	
	Sprite_T *d;
	Sprite_T *button;
	IN_BATTLE = false;
	
	Init_All();

	Screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,32,SDL_SWSURFACE); //sets the size of window. SDL_SWSurface makes the Software handle the graphics
	oworld = IMG_Load("Overworld1.png");
	MAP_FLAG = 15;

//player data was here
	//PlayerStats(Player);
	Player = (Enemy_T*)Init_Enemy(1,2,10,true,"warrior.png",10);
	Pig = (Enemy_T*)Init_Enemy(1,1,6,false,"ppl_mon.png",0);
	Pig2 = (Enemy_T*)Init_Enemy(1,2,10,false,"ppl_mon.png",0);

	door.x = 770;
	door.y = 265;
	door.w = 20;
	door.h = 30;

	doorEnt = Init_Ent();
	doorEnt->bBox.w = 20;
	doorEnt->bBox.h = 64;

	d = SetupSprite("door.png",door);

	doorEnt = DressUpEntity(d,door,doorEnt);
	doorEnt->x = 770;
	doorEnt->y = 265;

	menu = Init_Ent();
	Abutton.x = 220;
	Abutton.y = 190;
	Abutton.h = 32;
	Abutton.w = 60;

	menu->bBox.w = 60;
	menu->bBox.h = 32;

	button = SetupSprite("button_attack.png",menu->bBox);
	menu->sprite = button;
	menu = DressUpEntity(button,Abutton,menu);
	menu->x = 158;
	menu->y = 98;
	//LoadSprite("mouse.png",16,16);
	quit = false;

	while(!quit){
		//event loop
		while(SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			HandleInput();
			handle_events();
			updateGame();
			DrawGame();
		}
	}
	SDL_FreeSurface(Screen); //clean up frees data
	SDL_Quit(); //closes window
	return 0;
}
//entire interation of the game world (do loop) is a frame