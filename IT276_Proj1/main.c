#include <SDL.h>
#include <SDL_image.h>
#include "defines.h"
#include "sprite.h"
#include "entity.h"
#include "globals.h"
#define black_	0x000000

SDL_Rect heroRect;
//The images that correspond to a keypress 
//SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];
//reference to SDL_Surface
SDL_Surface* Screen;
SDL_Surface* oworld;
SDL_Surface* fmap;
SDL_Surface* wa;

//event variable
Entity_T *ent;
Entity_T *player;
SDL_Event e;

//sprite sides
SDL_Rect clipsRight[ 4 ];
SDL_Rect clipsLeft[ 4 ];


	//init varis
	//The offset 
	int offSet; 
	
	//Its rate of movement 
	//int velocity = 15; 
	
	//Its current frame 
	//int frame; 
	
	//Its animation status 
	//int status; 
	//Initializes the variables 
	
	//Handles input 
	void handle_events(); 
	
	//Moves the stick figure 
	void move(Entity_T *e); 
	
	//Shows the stick figure 
	void show(); 


void War()
{
	//Move
	offSet = 0;
	//velocity = 0;

	//Init animation variables
	//frame = 0;
	//status = WAR_RIGHT;
}

void move(Entity_T *ent)
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
}
void load_battle()
{
	fmap = IMG_Load("BattleMap1.png");

}
void load_map2()
{
	oworld = IMG_Load("Overworld1.png");
}
/*void show()
{
	if(velocity < 0)
	{
			status = WAR_LEFT;
			frame++;
	}
	else if(velocity > 0)
	{
		status = WAR_RIGHT;
		frame++;
	}
	else
	{
		frame = 0;
	}
	if(frame >= 4)
	{
		frame = 0;
	}
	//show it
	if(status == WAR_RIGHT)
	{
		SDL_BlitSurface(wa,NULL,Screen,&heroRect);
	}
	else if(status == WAR_LEFT)
	{
		SDL_BlitSurface(wa, NULL, Screen, &heroRect);
	}
}*/

bool load_files()
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
}


void set_clips() 
{ 
	//Clip the sprites 
	clipsRight[ 0 ].x = 0; 
	clipsRight[ 0 ].y = 0; 
	clipsRight[ 0 ].w = WAR_WIDTH; 
	clipsRight[ 0 ].h = WAR_HEIGHT;

	clipsRight[ 1 ].x = WAR_WIDTH; 
	clipsRight[ 1 ].y = 0; 
	clipsRight[ 1 ].w = WAR_WIDTH; 
	clipsRight[ 1 ].h = WAR_HEIGHT; 

	clipsRight[ 2 ].x = WAR_WIDTH * 2; 
	clipsRight[ 2 ].y = 0; 
	clipsRight[ 2 ].w = WAR_WIDTH; 
	clipsRight[ 2 ].h = WAR_HEIGHT;

	clipsRight[ 3 ].x = WAR_WIDTH * 3; 
	clipsRight[ 3 ].y = 0; 
	clipsRight[ 3 ].w = WAR_WIDTH; 
	clipsRight[ 3 ].h = WAR_HEIGHT; 

	clipsLeft[ 0 ].x = 0; 
	clipsLeft[ 0 ].y = WAR_HEIGHT; 
	clipsLeft[ 0 ].w = WAR_WIDTH; 
	clipsLeft[ 0 ].h = WAR_HEIGHT;

	clipsLeft[ 1 ].x = WAR_WIDTH; 
	clipsLeft[ 1 ].y = WAR_HEIGHT; 
	clipsLeft[ 1 ].w = WAR_WIDTH; 
	clipsLeft[ 1 ].h = WAR_HEIGHT; 

	clipsLeft[ 2 ].x = WAR_WIDTH * 2; 
	clipsLeft[ 2 ].y = WAR_HEIGHT; 
	clipsLeft[ 2 ].w = WAR_WIDTH; 
	clipsLeft[ 2 ].h = WAR_HEIGHT; 

	clipsLeft[ 3 ].x = WAR_WIDTH * 3; 
	clipsLeft[ 3 ].y = WAR_HEIGHT; 
	clipsLeft[ 3 ].w = WAR_WIDTH; 
	clipsLeft[ 3 ].h = WAR_HEIGHT; 
}

int main (int argc,char* argv[]) //ran after SDL main
{
	int quit;
	SDL_Rect playerRect;
	SDL_Rect door;
	Sprite_T *s;
	Sprite_T *d;
	Entity_T *doorEnt;
	SDL_Init(SDL_INIT_EVERYTHING); //inits everything for sdl
	Screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,32,SDL_SWSURFACE); //sets the size of window. SDL_SWSurface makes the Software handle the graphics
	oworld = IMG_Load("Overworld1.png");
	
	player = Init_Ent();
	//Init_Position(player);
	player->width = 32;
	player->height = 32;

	player->bBox.x = 31;
	player->bBox.y = 0;
	player->bBox.w = 31;
	player->bBox.h = 32;

	s = SetupSprite("warrior.png", player->bBox);
	player->sprite = s;
	//DressUpEntity(player->sprite, player->bBox, player);
	player->x = 128;
	player->y = 128;
	
	doorEnt = Init_Ent();
	//Init_Position(doorEnt);
	door.x = 0;
	door.y = 0;

	doorEnt->bBox.w = 20;
	doorEnt->bBox.h = 64;

	d = SetupSprite("door.png",door);
	//doorEnt->sprite = d;
	doorEnt = DressUpEntity(d,door,doorEnt);
	doorEnt->x = 200;
	doorEnt->y = 265;
	door.w = 20;
	door.h = 30;

	quit = false;

	set_clips();

	//if(s)
//	{
	//	fprintf(stdout, "no player sprite \n");
		//return 0;
	//}
	
	while(!quit){
		//event loop
		while(SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			//SDL_PumpEvents();
			handle_events();
			//move(player);

			if(is_Collided(player->bBox, doorEnt->bBox))
			{
				fprintf(stdout, "entered door\n");
			}

			//clears the screen for next frame
			SDL_FillRect(Screen,NULL, black_);
		}
		//show();
		SDL_BlitSurface(oworld,NULL,Screen,NULL);
		//move(player);
		DrawEntity(player);
		Free_Ent(player);
		DrawEntity(doorEnt);
		
		//update it
		SDL_Flip(Screen);
		}

	SDL_FreeSurface(Screen); //clean up frees data
	SDL_Quit(); //closes window
	return 0;
}
//entire interation of the game world (do loop) is a frame