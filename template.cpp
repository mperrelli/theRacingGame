// Programmers: Matt Perrelli, Anthony Mascia, Andrew Goreckie
// Course:	    CMPT 456 
// Due Date:    5 May 2014
//
// Unnecessary Vehicle Avoidance Training
//
// UVAT is a game where on must traverse a track as cleanly as 
// possible to stay on the track and avoide other cars as they 
// come speeding by. Survive until the time runs out and you win!

// Includes, namespace and prototypes
#include "template.h"
#include <string>
#include <sstream>
#include "Sprite.h"
#include "Vehicle.h"
#include "Environment.h"
#include "Track.h"
#include "MapLoader.h"
#include "Globals.h"
#include "AI.h"
#include "Timer.h"
#include "View.h"
using namespace AGK;
using namespace std;
app App;

/***********************/
/* FUNCTION PROTOTYPES */
/***********************/
void titleScreen();
void instructionScreen();
void trackScreen();
void chooseCarColor();
void chooseCarType();
void loadMaps();
void updateVehicle();
void checkCollisions();
void updateHud();

/*************************/
/* GAMESTATES ATTRIBUTES */
/*************************/
const int TITLESCREEN  = 0,
	      INSTRUCTIONS = 1,
		  PICKMAP	   = 2,
		  PICKCARCOLOR = 3,
		  PICKCARTYPE  = 4,
		  LOADING      = 5,
		  INPLAY       = 6,
		  GAMEOVER     = 7,
		  WIN		   = 8;

int	g_gameState		   = TITLESCREEN;


/*********************************/
/* ENVRIONMENT AND MAP INSTANCES */
/*********************************/
const int MAX_TRACKS = 10;
int g_tracksAmt = 0;
int g_selectedTrack;

Track tracks[MAX_TRACKS];

// Declare environment
Environment env;

/****************************/
/* SPRITE/VEHICLE INSTANCES */
/****************************/
Vehicle userCar;

// Begin app, called once at the start
void app::Begin( void )
{
	// Set the window title.
    agk::SetWindowTitle("UVAT");
	agk::SetVirtualResolution(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Load Sounds and Music
	agk::LoadSound(GAME_OVER_MUSIC,			"resources/gameovermusic.wav"); 

	// Load Images
	agk::LoadImage(CAR,					    "resources/car.png");
	agk::LoadImage(CAR_MOVING,              "resources/carMoving.png");

	// Create userCar sprite and set all its attributes
	userCar.createSprite(CAR_INDEX, CAR);
	userCar.setPosition(SCREEN_WIDTH / 2 - (VEHICLE_FRAME_WIDTH / 2), 
		                SCREEN_HEIGHT / 2 - (VEHICLE_FRAME_HEIGHT / 2));
	agk::SetSpriteDepth(CAR_INDEX, -1);

	agk::SetSpriteAnimation(CAR_INDEX, VEHICLE_FRAME_WIDTH, 
		                    VEHICLE_FRAME_HEIGHT, VEHICLE_FRAMES);
	agk::PlaySprite(CAR_INDEX);

	// Set sprite initial visibilities
	userCar.setVisible(FALSE);

	View::Instance()->buildTitleScreen();
	View::Instance()->showTitleScreen();

	loadMaps();
}

// Main loop, called every frame
void app::Loop ( void )
{
	switch(g_gameState)
	{
	case TITLESCREEN:

		titleScreen();
		break;

	case INSTRUCTIONS:

		instructionScreen();
		break;

	case PICKMAP:

		trackScreen();
		break;

	case PICKCARCOLOR:

		chooseCarColor();
		break;

	case PICKCARTYPE:

		chooseCarType();
		break;

	case LOADING:

		agk::StopMusic();
		env.setTrack(tracks[g_selectedTrack]);
		userCar.setVisible(TRUE);

		View::Instance()->buildGameoverScreen();
		View::Instance()->buildWinScreen();
		View::Instance()->buildHUDScreen();
		View::Instance()->showHUDScreen();

		g_gameState = INPLAY;

		break;

	case INPLAY:

		Timer::Instance()->tick();

		updateVehicle();

		checkCollisions();

		updateHud();

		if(userCar.getHealth() <= 0)
		{
			g_gameState = GAMEOVER;
			View::Instance()->destroyHUDScreen();
		}

		if(env.getTimeRemaining() <= 0)
		{
			View::Instance()->destroyHUDScreen();
			g_gameState = WIN;
		}

		break;
		
	case GAMEOVER:

		userCar.setVisible(FALSE);
		env.~Environment();

		if(!agk::GetSoundsPlaying(GAME_OVER_MUSIC))
		{
			agk::PlaySound(GAME_OVER_MUSIC);
		}

		View::Instance()->showGameoverScreen();
		break;

	case WIN:

		userCar.setVisible(FALSE);
		env.~Environment();
	
		if(!agk::GetSoundsPlaying(GAME_OVER_MUSIC))
		{
			agk::PlaySound(GAME_OVER_MUSIC);
		}

		View::Instance()->showWinScreen();
		break;
	}

	// Update the screen every iteration of the loop
	agk::Sync();
}

// Called when the app ends
void app::End ( void )
{
}

void titleScreen()
{
	// When enter pressed, show instruction screen
	if(agk::GetRawKeyPressed(AGK_KEY_ENTER))
	{
		View::Instance()->destroyTitleScreen();
		View::Instance()->buildInstructionScreen();

		// Advance gamestate
		g_gameState = INSTRUCTIONS;
	}
}

void instructionScreen()
{
	View::Instance()->showInstructionScreen();

	// When enter pressed, have user pick type of map
	if(agk::GetRawKeyPressed(AGK_KEY_ENTER))
	{
		View::Instance()->destroyInstructionScreen();
		View::Instance()->buildTrackScreen();
		View::Instance()->showTrackScreen();
		g_gameState = PICKMAP;
	}
}

void trackScreen()
{
	float mouseX = agk::GetRawMouseX();
	float mouseY = agk::GetRawMouseY();

	// Check to see what track car user wants
	if (agk::GetRawMouseLeftPressed() && 
		agk::GetSpriteHitGroup(SPRITE_GROUP_SELECTION, mouseX, mouseY))
	{
		float mouseX = agk::GetRawMouseX();
		float mouseY = agk::GetRawMouseY();

		switch(agk::GetSpriteHitGroup(SPRITE_GROUP_SELECTION, mouseX, mouseY))
		{
			case LINEAR_INDEX:

				g_selectedTrack = 0;
				break;

			case LOOP_INDEX:

				g_selectedTrack = 1;
				break;

			default:
				break;
		}

		View::Instance()->destroyTrackScreen();
		View::Instance()->buildCarColorScreen();
		View::Instance()->showCarColorScreen();

		// Advance gamestate
		g_gameState = PICKCARCOLOR;
	}

}

void chooseCarColor()
{
	float mouseX = agk::GetRawMouseX();
	float mouseY = agk::GetRawMouseY();

	// Check to see what color car user wants
	if (agk::GetRawMouseLeftPressed() &&
		agk::GetSpriteHitGroup(SPRITE_GROUP_SELECTION, mouseX, mouseY))
	{

		switch(agk::GetSpriteHitGroup(SPRITE_GROUP_SELECTION, mouseX, mouseY))
		{
			case RED_INDEX:
				
				break;
			case GREEN_INDEX:
				userCar.setColor('G');
				break;
			case BLUE_INDEX:
				userCar.setColor('B');
				break;
			default:
				break;
		}
		
		View::Instance()->destroyCarColorScreen();
		View::Instance()->buildCarTypeScreen();
		View::Instance()->showCarTypeScreen();

		// Advance gamestate
		g_gameState = PICKCARTYPE;
	}
}

void chooseCarType()
{
	float mouseX = agk::GetRawMouseX();
	float mouseY = agk::GetRawMouseY();

	// Check to see what color car user wants
	if (agk::GetRawMouseLeftPressed() &&
		agk::GetSpriteHitGroup(SPRITE_GROUP_SELECTION, mouseX, mouseY))
	{
		switch(agk::GetSpriteHitGroup(SPRITE_GROUP_SELECTION, mouseX, mouseY))
		{
			case SPEED_INDEX:

				userCar.setMaxSpeed(12);
				userCar.setControlFactor(0);
				break;

			case BALANCE_INDEX:

				userCar.setMaxSpeed(11);
				userCar.setControlFactor(1);
				break;

			case CONTROL_INDEX:

				userCar.setMaxSpeed(10);
				userCar.setControlFactor(2);
				break;

			default:
				break;
		}

		View::Instance()->destroyCarTypeScreen();

		// Advance gamestate
		g_gameState = LOADING;
	}
}

// Load all maps from the resources folder
void loadMaps()
{
	MapLoader loader;
	int fIndex = agk::OpenToRead("maps.dat");
	string line;
	int counter = 0;

	while(!agk::FileEOF(fIndex))
	{
		line = agk::ReadLine(fIndex);

		loader.loadFile(line.c_str());

		tracks[counter] = loader.getTrack();

		counter++;
	}
	
	agk::CloseFile(fIndex);
}

// Update Vehicle angle, speed based on input
void updateVehicle()
{
	float x = 0, y = 0;

	x = agk::GetDirectionX();
	y = agk::GetDirectionY();

	int turnspeed = userCar.getTurnSpeed();
	int angle = (int)ceil(userCar.getAngle());

	// keep angle within normal values
	if(angle > 360)
	{
		angle = angle - 360;
	}
	else if(angle < 0)
	{
		angle = angle + 360;
	}
	else if(angle == 360)
	{
		angle = 0;
	}

	// get acceleration and breaking from mouse
	if(agk::GetRawMouseLeftState())
	{
		userCar.accelerate();
	}
	else if(!agk::GetRawMouseLeftState())
	{
		userCar.deccelerate();
	}

	if(agk::GetRawMouseRightState())
	{
		userCar.applyBreak();
	}

	// Manage car animation during turns
	if(userCar.getCurrSpeed() > 0)
	{
		if(angle == NORTH_ANGLE)
		{
			if(agk::GetRawKeyState(AGK_KEY_LEFT))
			{
				angle -= turnspeed;
			}
			else if(agk::GetRawKeyState(AGK_KEY_RIGHT))
			{
				angle += turnspeed;
			}
		}
		else if(angle == EAST_ANGLE)
		{
			if(agk::GetRawKeyState(AGK_KEY_UP))
			{
				angle -= turnspeed;
			}
			else if(agk::GetRawKeyState(AGK_KEY_DOWN))
			{
				angle += turnspeed;
			}
		}
		else if(angle == SOUTH_ANGLE)
		{
			if(agk::GetRawKeyState(AGK_KEY_LEFT))
			{
				angle += turnspeed;
			}
			else if(agk::GetRawKeyState(AGK_KEY_RIGHT))
			{
				angle -= turnspeed;
			}
		}
		else if(angle == WEST_ANGLE)
		{
			if(agk::GetRawKeyState(AGK_KEY_UP))
			{
				angle += turnspeed;
			}
			else if(agk::GetRawKeyState(AGK_KEY_DOWN))
			{
				angle -= turnspeed;
			}
		}
		// Northeast Quandrent
		else if(angle > NORTH_ANGLE && angle < EASTHIGH_ANGLE) 
		{
			if(agk::GetRawKeyState(AGK_KEY_UP) && agk::GetRawKeyState(AGK_KEY_RIGHT))
			{
				angle = angle;
			}
			else if(agk::GetRawKeyState(AGK_KEY_UP) || agk::GetRawKeyState(AGK_KEY_LEFT))
			{
				angle -= turnspeed;
			}
			else if(agk::GetRawKeyState(AGK_KEY_RIGHT) || agk::GetRawKeyState(AGK_KEY_DOWN))
			{
				angle += turnspeed;
			}
		}
		// Southheast Quandrent
		else if(angle > EAST_ANGLE && angle < SOUTH_ANGLE)
		{
			if(agk::GetRawKeyState(AGK_KEY_RIGHT) && agk::GetRawKeyState(AGK_KEY_DOWN))
			{
				angle = angle;
			}
			else if(agk::GetRawKeyState(AGK_KEY_RIGHT) || agk::GetRawKeyState(AGK_KEY_UP))
			{
				angle -= turnspeed;
			}
			else if(agk::GetRawKeyState(AGK_KEY_DOWN) || agk::GetRawKeyState(AGK_KEY_LEFT))
			{
				angle += turnspeed;
			}
		}	
		// Southwest Quandrent
		else if(angle > SOUTH_ANGLE && angle < WEST_ANGLE)
		{
			if(agk::GetRawKeyState(AGK_KEY_LEFT) && agk::GetRawKeyState(AGK_KEY_DOWN))
			{
				angle = angle;
			}
			else if(agk::GetRawKeyState(AGK_KEY_DOWN) || agk::GetRawKeyState(AGK_KEY_RIGHT))
			{
				angle -= turnspeed;
			}
			else if(agk::GetRawKeyState(AGK_KEY_LEFT) || agk::GetRawKeyState(AGK_KEY_UP))
			{
				angle += turnspeed;
			}
		}
		// Northwest Quandrent
		else if(angle > WEST_ANGLE && angle < NORTH_ANGLE)
		{
			if(agk::GetRawKeyState(AGK_KEY_UP) && agk::GetRawKeyState(AGK_KEY_LEFT))
			{
				angle = angle;
			}
			else if(agk::GetRawKeyState(AGK_KEY_UP) || agk::GetRawKeyState(AGK_KEY_RIGHT))
			{
				angle += turnspeed;
			}
			else if(agk::GetRawKeyState(AGK_KEY_LEFT) || agk::GetRawKeyState(AGK_KEY_DOWN))
			{
				angle -= turnspeed;
			}
		}
	}

	userCar.update();
	userCar.setAngle(angle);
	env.updateEnvironment(x, y, userCar.getCurrSpeed());
}

// Check collisions between vehicles and the track
void checkCollisions()
{
	int vehicleIndex = userCar.getSpriteIndex();

	if(Timer::Instance()->getElapsedTime() % COLLISION_CHECK_INTERVAL == 0)
	{
		// Check other vehicles
		for(int i = AI_SPRITE_START_INDEX; i < AI_SPRITE_START_INDEX + env.getAIAmount(); i++)
		{
			if(agk::GetSpriteCollision(vehicleIndex, i))
			{
				userCar.setHealth(userCar.getHealth() - 20);
			}
		}

		// Check current surface below vehicle
		int sIndex = agk::GetSpriteHitGroup(SPRITE_GROUP_TRACK , userCar.getCenterX(), userCar.getCenterY());

		if(agk::GetSpriteImageID(sIndex) == BG)
		{
			userCar.setHealth(userCar.getHealth() - 5);
		}
	}
}

// Updates the Heads-up Display
void updateHud()
{
	ostringstream ss;

	// Health
	ss << userCar.getHealth();
	string health(ss.str());

	agk::SetTextString(HEALTH_VALUE, health.c_str());

	ss.str(std::string());

	// Speed
	ss << userCar.getSpeed();
	string speed(ss.str());

	agk::SetTextString(SPEED_VALUE, speed.c_str());

	ss.str(std::string());

	// Timer
	ss << env.getTimeRemaining();
	string time(ss.str());

	agk::SetTextString(TIMER_VALUE, time.c_str());
}