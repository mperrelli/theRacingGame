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
#include "Sprite.h"
#include "Vehicle.h"
#include "Environment.h"
#include "Track.h"
#include "log.h"
app App;

// Function prototypes
void generateTitleScreen();
void generateInstructions();
void loadMaps();

// Height and width of the screen
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// Image indexes
const int TITLE_SCREEN_BG = 1;

// Sprite indexes
const int TITLE_SCREEN_BG_INDEX = 1;

// Sound and Music indexes
const int TITLE_SCREEN_MUSIC = 1;

// Gamestates
const int TITLESCREEN  = 0,
	      INSTRUCTIONS = 1,
		  PICKMAP	   = 2,
		  PICKVEHICLE  = 3,
		  INPLAY       = 4;

int g_gameState		   = PICKMAP;

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

	// Create Sprites and Set Visibilities
	agk::CreateSprite(TITLE_SCREEN_BG_INDEX, TITLE_SCREEN_BG);
	agk::SetSpriteVisible(TITLE_SCREEN_BG_INDEX, HIDE);

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

		g_gameState = INPLAY;

		break;

	case PICKVEHICLE:

		/*
		* The user will select a vehicle. I'm not really sure where we want to go with this.
		* We should at least be selecting between control, speed or balanced and a color.
		*/

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

void generateTitleScreen()
{
	agk::SetSpriteVisible(TITLE_SCREEN_BG_INDEX, SHOW);

	// When enter pressed, show instruction screen
	if(agk::GetRawKeyPressed(AGK_KEY_ENTER)){
		agk::DeleteSprite(TITLE_SCREEN_BG_INDEX);
		g_gameState = INSTRUCTIONS;
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

	string assets[17] =
	{
		"grass.png",
		"trackV.png",
		"trackH.png",
		"trackTurnEN.png",
		"trackTurnES.png",
		"trackTurnWN.png",
		"trackTurnWS.png",
		"barrierH.png",
		"barrierV.png",
		"barrierTurnEN.png",
		"barrierTurnES.png",
		"barrierTurnWN.png",
		"barrierTurnWS.png",
		"barrierEndEW.png",
		"barrierEndNS.png",
		"barrierEndWE.png",
		"barrierEndSN.png"
	};

	tracks[0].setStartPosX(256);
	tracks[0].setStartPosY(320);
	tracks[0].setAssets(assets);
	tracks[0].setTrack(track);
	tracks[0].setRows(5);
	tracks[0].setCols(10);
	tracks[0].setName("map1");
	tracks[0].setDescription("This is a test description");
}