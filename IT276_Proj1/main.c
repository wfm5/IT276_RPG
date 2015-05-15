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
Enemy_T *Pig3;
Entity_T *menu;
Entity_T *menu2;
Entity_T *doorEnt;

Sprite_T *button;

SDL_Event e;


int offSet; 
int MAP_FLAG;
int up;
int quit;
bool IN_BATTLE;
	
//Handles input 
void handle_events(); 
void updateGame();


void load_battle()
{
	if(MAP_FLAG == 15)
	{
		oworld = IMG_Load("BattleMap1.png");
		MAP_FLAG &= ~1; 
	}
}
void load_map2()
{
	if(MAP_FLAG == 14)
	{
		oworld = IMG_Load("BattleMap2.png");
		MAP_FLAG &= ~2;
	}
}
void load_map3()
{
	if(MAP_FLAG == 12)
	{
		oworld = IMG_Load("BattleMap3.png");
		MAP_FLAG &= ~4; //8
	}
}
void load_map4()
{
	if(MAP_FLAG == 8)
	{
		oworld = IMG_Load("YouWin.png");
		MAP_FLAG &= ~8; 
		fprintf(stdout,"%d",MAP_FLAG);
	}
}
void end_game()
{
	if(MAP_FLAG == 0)
	{
		quit = true;
	}
}

Entity_T MakeButton(char* buttonname,float bx, float by)
{
	SDL_Rect Abutton;
	menu = Init_Ent();
	Abutton.x = 220;
	Abutton.y = 190;
	Abutton.h = 32;
	Abutton.w = 60;

	menu->bBox.w = 60;
	menu->bBox.h = 32;

	button = SetupSprite(buttonname,menu->bBox);
	menu->sprite = button;
	menu = DressUpEntity(button,Abutton,menu);
	menu->x = bx;
	menu->y = by;

	return *menu;
}
Entity_T MakeButton2(char* buttonname,float bx, float by) //repeating this for last minute changes
{
	SDL_Rect Sbutton;
	menu2 = Init_Ent();
	Sbutton.x = 220;
	Sbutton.y = 190;
	Sbutton.h = 32;
	Sbutton.w = 60;

	menu2->bBox.w = 60;
	menu2->bBox.h = 32;

	button = SetupSprite(buttonname,menu2->bBox);
	menu2->sprite = button;
	menu2 = DressUpEntity(button,Sbutton,menu2);
	menu2->x = bx;
	menu2->y = by;

	return *menu2;
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
		//fprintf(stdout,"Clicky");//activate button
	}
	if(checkClick(menu2))
	{
		//fprintf(stdout,"clicky");
	}
  }
}

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
		else if(MAP_FLAG == 8)
		{
			load_map4();
		}
		else
		{
			end_game();
			return;
		}
	}
	if(Pig->health <= 0)
	{
		Death(Pig);
		Pig2->alive = true;
		PowerUp(Player);
		load_map2();
	}
	if(Pig2->health <= 0)
	{
		Death(Pig2);
		Pig3->alive = true;
		PowerUp2(Player);
		load_map3();
	}
	if(Pig3->health <= 0)
	{
		Death(Pig3);
		IN_BATTLE = false;
		load_map4();
	}
	if(mouseHover(menu->bBox.x,menu->bBox.y,menu->bBox.w,menu->bBox.h))
	{
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
				if(Pig2->alive)
				{
					AttackPlayer(Pig2,Player);
					fprintf(stdout,"Player hit Pig for: %d \n",Player->damage);
					fprintf(stdout,"Crawler Health Remaining: %d \n \n", Pig2->health);
				}
				if(Pig3->alive)
				{
					AttackPlayer(Pig3,Player);
					fprintf(stdout,"Player hit Pig for: %d \n",Player->damage);
					fprintf(stdout,"King Health Remaining: %d \n \n", Pig3->health);
				}
			}

			fprintf(stdout,"enemy attacks back \n");

			if(Pig->alive)
			{
				AttackPlayer(Player,Pig);
				fprintf(stdout,"Pig hit player for: %d \n \n",Pig->damage);
				fprintf(stdout,"Player Health Remaining: %d \n \n", Player->health);
			}			
			if(Pig2->alive)
			{
				AttackPlayer(Player,Pig2);
				fprintf(stdout,"Crawler hit player for: %d \n \n",Pig2->damage);
				fprintf(stdout,"Player Health Remaining: %d \n \n", Player->health);
			}
			if(Pig3->alive)
			{
				AttackPlayer(Player,Pig3);
				fprintf(stdout,"King hit player for: %d \n \n",Pig3->damage);
				fprintf(stdout,"Player Health Remaining: %d \n \n", Player->health);
			}	
		}
	}
	if(mouseHover(menu2->bBox.x,menu2->bBox.y,menu2->bBox.w,menu2->bBox.h))
	{
		if(clickLeft)
		{
			
			if(Player->alive = true && Player->mana > 0)
			{
				fprintf(stdout,"player attacks \n");
				if(Pig->alive)
				{
					AttackPlayer2(Pig,Player);
					fprintf(stdout,"Player hit Pig for: %d magic damage\n",(Player->mana)+2);
					fprintf(stdout,"Pig Health Remaining: %d \n \n", Pig->health);
				}
				if(Pig2->alive)
				{
					AttackPlayer2(Pig2,Player);
					fprintf(stdout,"Player hit Pig for: %d magic damage \n",(Player->mana)+2);
					fprintf(stdout,"Crawler Health Remaining: %d \n \n", Pig2->health);
				}
				if(Pig3->alive)
				{
					AttackPlayer2(Pig3,Player);
					fprintf(stdout,"Player hit Pig for: %d \n",(Player->mana)+2);
					fprintf(stdout,"King Health Remaining: %d \n \n", Pig3->health);
				}

				fprintf(stdout,"enemy attacks back \n");

				if(Pig->alive)
				{
					AttackPlayer(Player,Pig);
					fprintf(stdout,"Pig hit player for: %d \n \n",Pig->damage);
					fprintf(stdout,"Player Health Remaining: %d \n \n", Player->health);
				}			
				if(Pig2->alive)
				{
					AttackPlayer(Player,Pig2);
					fprintf(stdout,"Crawler hit player for: %d \n \n",Pig2->damage);
					fprintf(stdout,"Player Health Remaining: %d \n \n", Player->health);
				}
				if(Pig3->alive)
				{
					AttackPlayer(Player,Pig3);
					AttackPlayer(Player,Pig3);
					RegenSelf(Pig3);
					fprintf(stdout,"King healed a small ammount of health \n");
					fprintf(stdout,"King hit player for: %d \n \n",(Pig3->damage)*2);
					fprintf(stdout,"Player Health Remaining: %d \n \n", Player->health);
				}	
			}else{
				fprintf(stdout,"You don't have enough mana to deal damage. \n");
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
			DrawEntity(menu2);
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
			if(MAP_FLAG == 8)
			{
				if(Pig3->alive)
				{
					DrawEntity(Pig3->entity);
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
	InitEntityList();
	InitSpriteList();
	InitMouse();	
	atexit(CleanUpAll);
	
}

// this could be shorter
// wfm5: I got rid of some of the button crap
int main (int argc,char* argv[]) //ran after SDL main
{
//	SDL_Rect playerRect;
	SDL_Rect door;
	
	
	Sprite_T *d;
	
	IN_BATTLE = false;
	
	Init_All();

	Screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,32,SDL_SWSURFACE); //sets the size of window. SDL_SWSurface makes the Software handle the graphics
	oworld = IMG_Load("Overworld1.png");
	MAP_FLAG = 15;

	Player = (Enemy_T*)Init_Enemy(1,2,10,true,"warrior.png",10,9);
	Pig = (Enemy_T*)Init_Enemy(1,1,6,false,"ppl_mon.png",0,0);
	Pig2 = (Enemy_T*)Init_Enemy(1,2,10,false,"ppl_mon.png",0,1);
	Pig3 = (Enemy_T*)Init_Enemy(1,3,15,false,"ppl_mon.png",0,2);
	Pig2->alive = false;
	Pig3->alive = false;
	MakeButton("button_attack.png",158,68);
	MakeButton2("button_spell.png",158,110);

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