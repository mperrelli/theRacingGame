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
using namespace AGK;
using namespace std;
#include "Globals.h"
#include "Sprite.h"
#include "Vehicle.h"
#include "Environment.h"
#include "Track.h"
#include "MapLoader.h"
#include "log.h"
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


/***************************/
/* IMAGE/SPRITE ATTRIBUTES */
/***************************/
// Image indexes
const int CAR = 2;

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


/*************************/
/* GAMESTATES ATTRIBUTES */
/*************************/
const int TITLESCREEN  = 0,
	      INSTRUCTIONS = 1,
		  PICKMAP	   = 2,
		  PICKCARCOLOR = 3,
		  PICKCARTYPE  = 4,
		  LOADING      = 5,
		  INPLAY       = 6;

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

	// Play Title Screen Music
	agk::PlayMusic(TITLE_SCREEN_MUSIC, TRUE);

	// Create sprites
	userCar.createSprite(CAR_INDEX, CAR);
	userCar.setPosition(SCREEN_WIDTH / 2 - userCar.getHeight() / 2, SCREEN_HEIGHT / 2 - userCar.getWidth() / 2);
	agk::SetSpriteDepth(CAR_INDEX, -1);

	// Set sprite initial visibilities
	userCar.setVisible(FALSE);

	loadMaps();
}

// Main loop, called every frame
void app::Loop ( void )
{

	/* 
	* Every iteration of the main loop we need to check for user input
	* We check the keyboard, cursor position, and mouse clicks.
	*
	* The following functions will need to be implemented
	*
	* updateCursor();
	* checkMouseInput();
	* checkKeyboardInput();
	*
	*/

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
		userCar.setAngle(270);

		g_gameState = INPLAY;

		break;

	case INPLAY:

		/*
		* do somthing.. this will probably include checking
		* for input and updateing the screen IE updateing the
		* environment
		*/

		float x = 0, y = 0;

		x = agk::GetDirectionX();
		y = agk::GetDirectionY();

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

		if(userCar.getCurrSpeed() > 0)
		{
			if(x > 0 && y > 0)
			{
				userCar.setAngle(315);
			}
			else if(x > 0 && y < 0)
			{
				userCar.setAngle(225);
			}
			else if(x < 0 && y > 0)
			{
				userCar.setAngle(45);
			}
			else if(x < 0 && y < 0)
			{
				userCar.setAngle(135);
			}
			else if(x < 0)
			{
				userCar.setAngle(90);
			}
			else if(x > 0)
			{
				userCar.setAngle(270);
			}
			else if(y < 0)
			{
				userCar.setAngle(180);
			}
			else if(y > 0)
			{
				userCar.setAngle(0);
			}
		}

		env.updateEnvironment(x, y, userCar.getCurrSpeed());

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
	carScreen.setVisible(TRUE);
	red.setVisible(TRUE);
	blue.setVisible(TRUE);
	green.setVisible(TRUE);

	// Check to see what color car user wants
	if (agk::GetRawMouseLeftPressed())
	{
		float mouseX = agk::GetRawMouseX();
		float mouseY = agk::GetRawMouseY();

		switch(agk::GetSpriteHit(mouseX, mouseY))
		{
			case RED_INDEX:
				userCar.setColor('R');
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

				break;
			case BALANCE_INDEX:

				// Do something with Vehicle userCar's attributes
				userCar.setMaxSpeed(10);

				break;
			case CONTROL_INDEX:

				// Do something with Vehicle userCar's attributes
				userCar.setMaxSpeed(10);

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

	// Set positions
	red.setX(SCREEN_WIDTH / 2 - red.getCenterX());
	red.setY(SCREEN_HEIGHT / 4 - red.getCenterY());
	green.setX(SCREEN_WIDTH / 2 - green.getCenterX());
	green.setY(SCREEN_HEIGHT / 2 - green.getCenterY());
	blue.setX(SCREEN_WIDTH / 2 - blue.getCenterX());
	blue.setY(SCREEN_HEIGHT / 1.3 - blue.getCenterY());

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