// Programmers: Matt Perrelli, Anthony Mascia, Andrew Goreckie
// Course:	    CMPT 456 
// Due Date:    N/A
//
// The Racing Game
//
// Description will go here

// Includes, namespace and prototypes
#include "template.h"
#include <string>
#include <sstream>
using namespace AGK;
using namespace std;
#include "Sprite.h"
#include "Vehicle.h"
#include "Environment.h"
#include "Track.h"
#include "MapLoader.h"
#include "Log.h"
#include "Globals.h"
#include "AI.h"
app App;

/***********************/
/* FUNCTION PROTOTYPES */
/***********************/
void generateTitleScreen();
void generateInstructions();
void generateCarScreen();
void chooseCarColor();
void loadMaps();
void chooseCarType();
void createSpritesForMenus();
void updateVehicle();
void checkCollisions();
void updateHud();

/***************************/
/* IMAGE/SPRITE ATTRIBUTES */
/***************************/

// Sprite indexes
const int TITLE_SCREEN_BG_INDEX			= 1;
const int CAR_INDEX						= 2;
const int CHOOSE_CAR_COLOR_SCREEN_INDEX = 3;
const int RED_INDEX						= 4;
const int GREEN_INDEX					= 5;
const int BLUE_INDEX					= 6;
const int CHOOSE_CAR_TYPE_SCREEN_INDEX  = 7;
const int SPEED_INDEX					= 8;
const int BALANCE_INDEX					= 9;
const int CONTROL_INDEX					= 10;

// Sound and Music indexes
const int TITLE_SCREEN_MUSIC = 1;

// Text Indexes
const int HEALTH_LABEL = 1;
const int HEALTH_VALUE = 2;
const int SPEED_LABEL  = 3;
const int SPEED_VALUE  = 4;


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
		  GAMEOVER     = 7;

int	g_gameState		   = TITLESCREEN;


/*********************************/
/* ENVRIONMENT AND MAP INSTANCES */
/*********************************/
const int MAX_TRACKS = 10;
int g_tracksAmt = 0;

Track tracks[MAX_TRACKS];

// Declare environment
Environment env;

/****************************/
/* SPRITE/VEHICLE INSTANCES */
/****************************/
Vehicle userCar;

Sprite titleScreen(TITLE_SCREEN_BG_INDEX,			"resources/title_screen_bg.jpg"),
	   carScreen(CHOOSE_CAR_COLOR_SCREEN_INDEX,		"resources/choose_car_color_screen.jpg"),
	   red(RED_INDEX,								"resources/RED.jpg"),
	   green(GREEN_INDEX,							"resources/GREEN.jpg"),
	   blue(BLUE_INDEX,								"resources/BLUE.jpg"),
	   carTypeScreen(CHOOSE_CAR_TYPE_SCREEN_INDEX,	"resources/choose_car_type_screen.jpg"),
	   speed(SPEED_INDEX,							"resources/speed.png"),
	   control(CONTROL_INDEX,						"resources/control.png"),
	   balance(BALANCE_INDEX,						"resources/balance.png");

// Begin app, called once at the start
void app::Begin( void )
{
	// Set the window title.
    agk::SetWindowTitle("UVAT");
	agk::SetVirtualResolution(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Load Sounds and Music
	agk::LoadMusic(TITLE_SCREEN_MUSIC,		"resources/title_screen_music.mp3");

	// Load Images
	agk::LoadImage(CAR,					    "resources/car.png");
	agk::LoadImage(CAR_MOVING,              "resources/carMoving.png");

	// Play Title Screen Music
	agk::PlayMusic(TITLE_SCREEN_MUSIC, TRUE);

	// Create sprites
	userCar.createSprite(CAR_INDEX, CAR);
	userCar.setPosition(SCREEN_WIDTH / 2 - (VEHICLE_FRAME_WIDTH / 2), 
		                SCREEN_HEIGHT / 2 - (VEHICLE_FRAME_HEIGHT / 2));
	agk::SetSpriteDepth(CAR_INDEX, -1);

	agk::SetSpriteAnimation(CAR_INDEX, VEHICLE_FRAME_WIDTH, 
		                    VEHICLE_FRAME_HEIGHT, VEHICLE_FRAMES);
	agk::PlaySprite(CAR_INDEX);

	// Set sprite initial visibilities
	userCar.setVisible(FALSE);

	// Set hud items
	const int PADDING = 10;
	const int SIZE = 26;

	agk::CreateText(HEALTH_LABEL, "Health: ");
	agk::CreateText(HEALTH_VALUE, "100");
	agk::CreateText(SPEED_LABEL,  "Speed: ");
	agk::CreateText(SPEED_VALUE,  "000");

	agk::SetTextSize(HEALTH_LABEL, SIZE);
	agk::SetTextSize(HEALTH_VALUE, SIZE);
	agk::SetTextSize(SPEED_LABEL,  SIZE);
	agk::SetTextSize(SPEED_VALUE,  SIZE);

	agk::SetTextDepth(HEALTH_LABEL,  -2);
	agk::SetTextDepth(HEALTH_VALUE,  -2);
	agk::SetTextDepth(SPEED_LABEL,   -2);
	agk::SetTextDepth(SPEED_VALUE,   -2);

	agk::SetTextPosition(HEALTH_LABEL, SCREEN_WIDTH / 2 -
		                 agk::GetTextTotalWidth(HEALTH_VALUE) - PADDING,
						 SCREEN_HEIGHT - 
						 agk::GetTextTotalHeight(HEALTH_LABEL));
	agk::SetTextAlignment(HEALTH_LABEL, 2);

	agk::SetTextPosition(HEALTH_VALUE, SCREEN_WIDTH / 2 - PADDING,
						 SCREEN_HEIGHT - 
						 agk::GetTextTotalHeight(HEALTH_LABEL));
	agk::SetTextAlignment(HEALTH_VALUE, 2);

	agk::SetTextPosition(SPEED_LABEL, SCREEN_WIDTH / 2 + PADDING, 
						 SCREEN_HEIGHT - 
						 agk::GetTextTotalHeight(SPEED_LABEL));

	agk::SetTextPosition(SPEED_VALUE, SCREEN_WIDTH / 2 + 
		                 agk::GetTextTotalWidth(SPEED_LABEL) + PADDING,
						 SCREEN_HEIGHT - 
						 agk::GetTextTotalHeight(SPEED_VALUE));

	agk::SetTextVisible(HEALTH_LABEL, FALSE);
	agk::SetTextVisible(HEALTH_VALUE, FALSE);
	agk::SetTextVisible(SPEED_LABEL, FALSE);
	agk::SetTextVisible(SPEED_VALUE, FALSE);

	loadMaps();
}

// Main loop, called every frame
void app::Loop ( void )
{
	switch(g_gameState)
	{
	case TITLESCREEN:

		generateTitleScreen();
		break;

	case INSTRUCTIONS:

		generateInstructions();
		break;

	case PICKMAP:

		/*
		* This is where we build a screen that displays map selection.
		* Right now this is a choice between two maps. Linear or Cyclical.
		* user clicks on one of the other and then we generate a map based on that.
		*
		* The user should also be selecting a difficulty here
		*/

		g_gameState = PICKCARCOLOR;

		break;

	case PICKCARCOLOR:

		/*
		* The user will select a vehicle. I'm not really sure where we want to go with this.
		* We should at least be selecting between control, speed or balanced and a color.
		*/

		chooseCarColor();
		break;

	case PICKCARTYPE:

		chooseCarType();
		break;

	case LOADING:

		agk::StopMusic();
		env.setTrack(tracks[1]);
		userCar.setVisible(TRUE);

		agk::SetTextVisible(HEALTH_LABEL, TRUE);
		agk::SetTextVisible(HEALTH_VALUE, TRUE);
		agk::SetTextVisible(SPEED_LABEL,  TRUE);
		agk::SetTextVisible(SPEED_VALUE,  TRUE);

		g_gameState = INPLAY;

		break;

	case INPLAY:

		/*
		* do somthing.. this will probably include checking
		* for input and updateing the screen IE updateing the
		* environment
		*/

		updateVehicle();

		checkCollisions();

		updateHud();

		if(userCar.getHealth() <= 0)
		{
			g_gameState = GAMEOVER;
		}

		break;
		
	case GAMEOVER:

		agk::DeleteText(HEALTH_LABEL);
		agk::DeleteText(HEALTH_VALUE);
		agk::DeleteText(SPEED_LABEL);
		agk::DeleteText(SPEED_VALUE);

		agk::Print("GAMEOVER");
		break;
	}

	// Update the screen every iteration of the loop
	agk::Sync();
}

// Called when the app ends
void app::End ( void )
{
}

void generateTitleScreen()
{
	titleScreen.createSprite();
	// When enter pressed, show instruction screen
	if(agk::GetRawKeyPressed(AGK_KEY_ENTER))
	{
		titleScreen.~Sprite();
		createSpritesForMenus();
		g_gameState = INSTRUCTIONS;
	}
}

void chooseCarColor()
{
	red.setVisible(TRUE);
	blue.setVisible(TRUE);
	green.setVisible(TRUE);
	carScreen.setVisible(TRUE);

	// Check to see what color car user wants
	if (agk::GetRawMouseLeftPressed())
	{
		float mouseX = agk::GetRawMouseX();
		float mouseY = agk::GetRawMouseY();

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

		// Destroy sprites not in use
		carScreen.~Sprite();
		red.~Sprite();
		green.~Sprite();
		blue.~Sprite();

		g_gameState = PICKCARTYPE;
	}
}

void chooseCarType()
{
	speed.setVisible(TRUE);
	balance.setVisible(TRUE);
	control.setVisible(TRUE);
	carTypeScreen.setVisible(TRUE);

	// Check to see what color car user wants
	if (agk::GetRawMouseLeftPressed())
	{
		float mouseX = agk::GetRawMouseX();
		float mouseY = agk::GetRawMouseY();

		switch(agk::GetSpriteHit(mouseX, mouseY))
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

		// Destroy sprites not in use
		carTypeScreen.~Sprite();
		speed.~Sprite();
		balance.~Sprite();
		control.~Sprite();

		g_gameState = LOADING;
	}
}

void generateInstructions(){

	//agk::SetSpriteVisible(INTRUCTIONS_BG_INDEX, SHOW);
	agk::Print("Instructions Go Here. Press Enter to Continue");

	// When enter pressed, have user pick type of map
	if(agk::GetRawKeyPressed(AGK_KEY_ENTER))
	{
		g_gameState = PICKMAP;
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

// We only want to create and position a single time.
void createSpritesForMenus()
{
	// Car color selection sprite setup
	carScreen.createSprite();
	red.createSprite();
	green.createSprite();
	blue.createSprite();

	// Set Sprite Group
	red.setSpriteGroup(SPRITE_GROUP_SELECTION);
	green.setSpriteGroup(SPRITE_GROUP_SELECTION);
	blue.setSpriteGroup(SPRITE_GROUP_SELECTION);

	// Set positions
	red.setX(SCREEN_WIDTH / 2 - red.getCenterX());
	red.setY(SCREEN_HEIGHT / 4 - red.getCenterY());
	green.setX(SCREEN_WIDTH / 2 - green.getCenterX());
	green.setY(SCREEN_HEIGHT / 2 - green.getCenterY());
	blue.setX(SCREEN_WIDTH / 2 - blue.getCenterX());
	blue.setY(SCREEN_HEIGHT / 1.3f - blue.getCenterY());

	carScreen.setVisible(FALSE);
	red.setVisible(FALSE);
	green.setVisible(FALSE);
	blue.setVisible(FALSE);

	// Car type selection sprite setup
	carTypeScreen.createSprite();
	speed.createSprite();
	control.createSprite();
	balance.createSprite();

	// Set positions
	speed.setPosition(20, SCREEN_HEIGHT / 2 - speed.getCenterY());

	balance.setPosition(SCREEN_WIDTH / 2 - balance.getCenterX(), 
						SCREEN_HEIGHT / 2 - balance.getCenterY());

	control.setPosition(SCREEN_WIDTH - control.getWidth() - 20,
						SCREEN_HEIGHT / 2 - control.getCenterY());

	// Set default visibility
	carTypeScreen.setVisible(FALSE);
	speed.setVisible(FALSE);
	control.setVisible(FALSE);
	balance.setVisible(FALSE);
}

void updateVehicle()
{
	const int EAST = 0;
	const int EASTHIGH = 360;
	const int SOUTH = 90;
	const int WEST = 180;
	const int NORTH = 270;

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
		if(angle == NORTH)
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
		else if(angle == EAST)
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
		else if(angle == SOUTH)
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
		else if(angle == WEST)
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
		else if(angle > NORTH && angle < EASTHIGH) 
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
		else if(angle > EAST && angle < SOUTH)
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
		else if(angle > SOUTH && angle < WEST)
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
		else if(angle > WEST && angle < NORTH)
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

void checkCollisions()
{
	int vehicleIndex = userCar.getSpriteIndex();

	if(env.getTime() % 10 == 0)
	{
		for(int i = AI_SPRITE_START_INDEX; i < AI_SPRITE_START_INDEX + env.getAIAmount(); i++)
		{
			if(agk::GetSpriteCollision(vehicleIndex, i))
			{
				userCar.setHealth(userCar.getHealth() - 20);
			}
		}

		int sIndex = agk::GetSpriteHitGroup(SPRITE_GROUP_TRACK , userCar.getCenterX(), userCar.getCenterY());

		if(agk::GetSpriteImageID(sIndex) == BG)
		{
			userCar.setHealth(userCar.getHealth() - 5);
		}
	}
}

void updateHud()
{
	ostringstream ss;
	ss << userCar.getHealth();
	string health(ss.str());

	agk::SetTextString(HEALTH_VALUE, health.c_str());

	ss.str(std::string());

	ss << userCar.getSpeed();
	string speed(ss.str());

	agk::SetTextString(SPEED_VALUE, speed.c_str());
}