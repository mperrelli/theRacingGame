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
#include <list>
using namespace AGK;
using namespace std;
#include "Sprite.h"
#include "Vehicle.h"
#include "Environment.h"
#include "Track.h"
app App;

// Function prototypes
void generateTitleScreen();
void generateInstructions();
void generateCarScreen();
void chooseCarColor();
void loadMaps();

// Height and width of the screen
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// Image indexes
const int TITLE_SCREEN_BG = 1;
const int CAR = 2;
const int CHOOSE_CAR_SCREEN = 3;
const int RED = 4;
const int GREEN = 5;
const int BLUE = 6;

// Sprite indexes
const int TITLE_SCREEN_BG_INDEX = 1;
const int CAR_INDEX = 2;
const int CHOOSE_CAR_SCREEN_INDEX = 3;
const int RED_INDEX = 4;
const int GREEN_INDEX = 5;
const int BLUE_INDEX = 6;

// Sound and Music indexes
const int TITLE_SCREEN_MUSIC = 1;

// Gamestates
const int TITLESCREEN  = 0,
	      INSTRUCTIONS = 1,
		  PICKMAP	   = 2,
		  PICKVEHICLE  = 3,
		  INPLAY       = 4;

int g_gameState		   = TITLESCREEN;

// Global Constant Variables
const int SHOW		 = 1,
		  HIDE		 = 0,
		  LOOP_TRUE  = 1,
		  LOOP_FALSE = 0;


// An array of tracks for easy use. This should be replaced
// with a linked list later
const int MAX_TRACKS = 10;

Track tracks[MAX_TRACKS];

// Declare environment
Environment env;

list<Sprite> sprites;

// Begin app, called once at the start
void app::Begin( void )
{
	// Set the window title.
    agk::SetWindowTitle("UVAT");
	agk::SetVirtualResolution(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Load Sounds and Music
	agk::LoadMusic(TITLE_SCREEN_MUSIC, "resources/title_screen_music.mp3");

	// Load Images
	agk::LoadImage(TITLE_SCREEN_BG, "resources/title_screen_bg.jpg");
	agk::LoadImage(CAR, "resources/car.gif");
	agk::LoadImage(CHOOSE_CAR_SCREEN, "resources/choose_car_screen.jpg");
	agk::LoadImage(RED, "resources/RED.jpg");
	agk::LoadImage(GREEN, "resources/GREEN.jpg");
	agk::LoadImage(BLUE, "resources/BLUE.jpg");

	// Play Title Screen Music
	agk::PlayMusic(TITLE_SCREEN_MUSIC, LOOP_TRUE);

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

		// Loads a track into the environment
		env.setTrack(tracks[0]);

		g_gameState = PICKVEHICLE;

		break;

	case PICKVEHICLE:

		/*
		* The user will select a vehicle. I'm not really sure where we want to go with this.
		* We should at least be selecting between control, speed or balanced and a color.
		*/

		generateCarScreen();
		g_gameState = INPLAY;
		break;

	case INPLAY:
	
		/*
		* do somthing.. this will probably include checking
		* for input and updateing the screen IE updateing the
		* environment
		*/

		break;
	}

	// Update the screen every iteration of the loop
	agk::Sync();
}

// Called when the app ends
void app::End ( void )
{
}

void chooseCarColor(){

}

void generateTitleScreen()
{
	Sprite titleScreen(TITLE_SCREEN_BG, TITLE_SCREEN_BG_INDEX);
	titleScreen.createSprite();


	// When enter pressed, show instruction screen
	if(agk::GetRawKeyPressed(AGK_KEY_ENTER)){
		titleScreen.deleteSprite();
		g_gameState = INSTRUCTIONS;
	}
}

void generateCarScreen(){

	// Create necessary sprites for car creation
	Sprite carScreen(CHOOSE_CAR_SCREEN, CHOOSE_CAR_SCREEN_INDEX);
	Sprite car(CAR, CAR_INDEX);
	Sprite red(RED, RED_INDEX);
	Sprite green(GREEN, GREEN_INDEX);
	Sprite blue(BLUE, BLUE_INDEX);
	carScreen.createSprite();
	car.createSprite();
	red.createSprite();
	green.createSprite();
	blue.createSprite();

	// Unhide this to see if car is actually changing colors
	// Tested and it works
	car.setVisible(false);

	// Set positions
	red.setX(red.getCenterX() - red.getWidth() / 2);
	red.setY(red.getCenterY() / 2 - red.getHeight() / 2);
	green.setX(green.getCenterX() - green.getWidth() / 2);
	green.setY(green.getCenterY() - green.getHeight() / 2);
	blue.setX(blue.getCenterX() - blue.getWidth() / 2);
	blue.setY(480 / 1.3 - blue.getHeight() / 2);

	// Check to see what color car user wants
	if (agk::GetRawMouseLeftPressed())
	{
		float mouseX = agk::GetRawMouseX();
		float mouseY = agk::GetRawMouseY();

		switch(agk::GetSpriteHit(mouseX, mouseY))
		{
			case RED:
				car.setColor('R');
				break;
			case GREEN:
				car.setColor('G');
				break;
			case BLUE:
				car.setColor('B');
				break;
			default:
				break;
		}

		// Destroy sprites not in use
		carScreen.deleteSprite();
		red.deleteSprite();
		green.deleteSprite();
		blue.deleteSprite();

		// Next game state
		g_gameState = INPLAY;
	}

	

}

void generateInstructions(){

	//agk::SetSpriteVisible(INTRUCTIONS_BG_INDEX, SHOW);
	agk::Print("Instructions Go Here. Press Enter to Continue");

	// When enter pressed, have user pick type of map
	if(agk::GetRawKeyPressed(AGK_KEY_ENTER)){
		g_gameState = PICKMAP;
	}
}

// Load all maps from the resources folder
void loadMaps()
{
	// TEST: loading a test track in on the fly

	// Constants for the image indecies
	static const int BG            = 10;
	static const int TRACK         = 11;

	int track[20][20] =
		{ {BG   , BG   , BG   , BG   , BG   , BG   , BG   , BG   , BG   , BG   },
		  {BG   , BG   , BG   , BG   , BG   , BG   , BG   , BG   , BG   , BG   },
		  {TRACK, TRACK, TRACK, TRACK, TRACK, TRACK, TRACK, TRACK, TRACK, TRACK},
		  {BG   , BG   , BG   , BG   , BG   , BG   , BG   , BG   , BG   , BG   },
		  {BG   , BG   , BG   , BG   , BG   , BG   , BG   , BG   , BG   , BG   },
		};

	tracks[0].setTrack(track);
	tracks[0].setRows(5);
	tracks[0].setCols(10);
	tracks[0].setName("TestMap1");
	tracks[0].setDescription("This is a test description");
}