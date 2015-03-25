#include <SDL.h>
#include <SDL_image.h>
#include "globals.h"
#include "sprite.h"
#include "entity.h"
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
SDL_Event e;
Entity_T *ent;
//sprite sides
SDL_Rect clipsRight[ 4 ];
SDL_Rect clipsLeft[ 4 ];


	//init varis
	//The offset 
	int offSet; 
	
	//Its rate of movement 
	int velocity = 15; 
	
	//Its current frame 
	int frame; 
	
	//Its animation status 
	int status; 
	//Initializes the variables 
	
	//Handles input 
	void handle_events(); 
	
	//Moves the stick figure 
	void move(); 
	
	//Shows the stick figure 
	void show(); 


void War()
{
	//Move
	offSet = 0;
	velocity = 0;

	//Init animation variables
	frame = 0;
	status = WAR_RIGHT;
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


void move()
{

	offSet +=velocity;

	if( ( offSet < 0 ) || ( offSet + WAR_WIDTH > SCREEN_WIDTH ) ) 
	{ 
		offSet -= velocity; 
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
void show()
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
}

void handle_events()
{
	if( e.type == SDL_KEYDOWN)
	{
		//Set the proper message surface
		switch( e.key.keysym.sym )
		{
			case SDLK_UP: ent->bBox.y -= 25; printf("%d y \n", ent->bBox.y); break;
		    case SDLK_DOWN: ent->bBox.y += 25; printf("%d y \n", ent->bBox.y); break;
			case SDLK_LEFT: ent->bBox.x -= 25; printf("%d x \n", ent->bBox.x); break;
			case SDLK_RIGHT: ent->bBox.x += 25; printf("%d x \n", ent->bBox.x); break;
		}			
	}
}
bool load_files()
{
    //Load the sprite sheet
    wa = IMG_Load( "warrior.png" );
	heroRect.x = 0;
	heroRect.y = 0;
	heroRect.w = 0;
	heroRect.h = 0;

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
	SDL_Rect box;
	SDL_Rect door;
	Sprite_T *s;
	Entity_T *doorEnt;
	SDL_Init(SDL_INIT_EVERYTHING); //inits everything for sdl
	Screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,32,SDL_SWSURFACE); //sets the size of window. SDL_SWSurface makes the Software handle the graphics
	oworld = IMG_Load("Overworld1.png");
	
	
	box.x = 32;
	box.y = 0;
	box.w = 32;
	box.h = 32;
	s = SetupSprite("warrior.png", box);
	box.w = 32;
	box.h = 32;
	box.x = 128;
	box.y = 128;
	ent = SetupEntity(s, box);
	
	door.x = 752;
	door.y = 265;
	s=SetupSprite("door.png",door);
	door.w = 50;
	door.h = 50;
	doorEnt = SetupEntity(NULL,door);

	if(is_Collided(box, door))
	{
		fprintf(stdout,"true");
	}

	quit = false;

	set_clips();

	if(load_files() == false)
	{
		return 1;
	}
	
	while( !quit){
		
		//event loop
		while(SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			handle_events();
			if(heroRect.x == 742 && heroRect.y == 265)
			{
				load_battle();
			}
			//clears the screen for next frame
			SDL_FillRect(Screen,NULL, black_);
		}
		SDL_BlitSurface(oworld,NULL,Screen,NULL);
		move();
		//show();
		DrawEntity(ent);
		//update it
		SDL_Flip(Screen);
		}

	SDL_FreeSurface(Screen); //clean up frees data
	SDL_Quit(); //closes window
	return 0;
}
//entire interation of the game world (do loop) is a frame