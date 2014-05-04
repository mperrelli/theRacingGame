#include "template.h"
#include "Sprite.h"
#include "View.h"
#include "Globals.h"
using namespace AGK;
using namespace std;

// Global static pointer used to ensure a single instance of the class.
View* View::m_pInstance = NULL;  

// Sprites
Sprite titleScreen(TITLE_SCREEN_BG_INDEX,		    "resources/title_screen_bg.jpg"),
	   carScreen(CHOOSE_CAR_COLOR_SCREEN_INDEX,		"resources/choose_car_color_screen.jpg"),
	   red(RED_INDEX,								"resources/RED.jpg"),
	   green(GREEN_INDEX,							"resources/GREEN.jpg"),
	   blue(BLUE_INDEX,								"resources/BLUE.jpg"),
	   carTypeScreen(CHOOSE_CAR_TYPE_SCREEN_INDEX,	"resources/choose_car_type_screen.jpg"),
	   speed(SPEED_INDEX,							"resources/speed.png"),
	   control(CONTROL_INDEX,						"resources/control.png"),
	   balance(BALANCE_INDEX,						"resources/balance.png"),
	   trackScreen(CHOOSE_TRACK_SCREEN_INDEX,		"resources/choose_track_screen.jpg"),
	   linearTrack(LINEAR_INDEX,					"resources/linear_track.png"),
	   loopTrack(LOOP_INDEX,						"resources/loop_track.png"),
	   winnerScreen(WINNER_SCREEN_INDEX,			"resources/winner_screen.jpg"),
	   gameOverScreen(GAME_OVER_SCREEN_INDEX,		"resources/game_over_screen.jpg");
  
View* View::Instance()
{
   if (!m_pInstance)   // Only allow one instance of class to be generated.
      m_pInstance = new View();

   return m_pInstance;
}

View::View()
{
}

void View::buildTitleScreen()
{
	agk::LoadMusic(TITLE_SCREEN_MUSIC,		"resources/title_screen_music.mp3");
}

void View::showTitleScreen()
{
	titleScreen.createSprite();
	agk::PlayMusic(TITLE_SCREEN_MUSIC, TRUE);
}

void View::destroyTitleScreen()
{
	titleScreen.~Sprite();
}

void View::buildTrackScreen()
{
	// Track selection sprite setup
	trackScreen.createSprite();
	linearTrack.createSprite();
	loopTrack.createSprite();

	// Set Track Sprite Group
	linearTrack.setSpriteGroup(SPRITE_GROUP_SELECTION);
	loopTrack.setSpriteGroup(SPRITE_GROUP_SELECTION);

	// Set positions
	linearTrack.setPosition(50, 
							SCREEN_HEIGHT / 2 - linearTrack.getCenterY());
	loopTrack.setPosition(SCREEN_WIDTH - loopTrack.getWidth() - 50,
						  SCREEN_HEIGHT / 2 - loopTrack.getCenterY());

	// Set default visibility
	trackScreen.setVisible(FALSE);
	linearTrack.setVisible(FALSE);
	loopTrack.setVisible(FALSE);
}

void View::showTrackScreen()
{
	trackScreen.setVisible(TRUE);
	linearTrack.setVisible(TRUE);
	loopTrack.setVisible(TRUE);
}

void View::destroyTrackScreen()
{
	trackScreen.~Sprite();
	linearTrack.~Sprite();
	loopTrack.~Sprite();
}

void View::buildCarColorScreen()
{
	// Car color selection sprite setup
	carScreen.createSprite();
	red.createSprite();
	green.createSprite();
	blue.createSprite();

	// Set Color Sprite Group
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
}

void View::showCarColorScreen()
{
	red.setVisible(TRUE);
	blue.setVisible(TRUE);
	green.setVisible(TRUE);
	carScreen.setVisible(TRUE);
}

void View::destroyCarColorScreen()
{
	carScreen.~Sprite();
	red.~Sprite();
	green.~Sprite();
	blue.~Sprite();
}

void View::buildCarTypeScreen()
{
	// Car type selection sprite setup
	carTypeScreen.createSprite();
	speed.createSprite();
	control.createSprite();
	balance.createSprite();

	speed.setSpriteGroup(SPRITE_GROUP_SELECTION);
	control.setSpriteGroup(SPRITE_GROUP_SELECTION);
	balance.setSpriteGroup(SPRITE_GROUP_SELECTION);

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

void View::showCarTypeScreen()
{
	speed.setVisible(TRUE);
	balance.setVisible(TRUE);
	control.setVisible(TRUE);
	carTypeScreen.setVisible(TRUE);
}

void View::destroyCarTypeScreen()
{
	carTypeScreen.~Sprite();
	speed.~Sprite();
	balance.~Sprite();
	control.~Sprite();
}

void View::buildHUDScreen()
{
	// Set hud items
	const int PADDING = 10;
	const int SIZE = 26;

	agk::CreateText(TIMER_LABEL, "Seconds Left: ");
	agk::CreateText(TIMER_VALUE, "120");
	agk::CreateText(HEALTH_LABEL, "Health: ");
	agk::CreateText(HEALTH_VALUE, "100");
	agk::CreateText(SPEED_LABEL,  "Speed: ");
	agk::CreateText(SPEED_VALUE,  "000");

	agk::SetTextSize(HEALTH_LABEL, (float)SIZE);
	agk::SetTextSize(HEALTH_VALUE, (float)SIZE);
	agk::SetTextSize(SPEED_LABEL,  (float)SIZE);
	agk::SetTextSize(SPEED_VALUE,  (float)SIZE);
	agk::SetTextSize(TIMER_LABEL,  (float)SIZE);
	agk::SetTextSize(TIMER_VALUE,  (float)SIZE);

	agk::SetTextDepth(HEALTH_LABEL,  -2);
	agk::SetTextDepth(HEALTH_VALUE,  -2);
	agk::SetTextDepth(SPEED_LABEL,   -2);
	agk::SetTextDepth(SPEED_VALUE,   -2);
	agk::SetTextDepth(TIMER_LABEL,   -2);
	agk::SetTextDepth(TIMER_VALUE,   -2);

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

	agk::SetTextPosition(TIMER_LABEL, SCREEN_WIDTH / 2 - 
						((agk::GetTextTotalWidth(TIMER_LABEL) + 
						  agk::GetTextTotalWidth(TIMER_VALUE)) / 2)
						  , (float)PADDING);

	agk::SetTextPosition(TIMER_VALUE, SCREEN_WIDTH / 2 + 
						((agk::GetTextTotalWidth(TIMER_LABEL) + 
						  agk::GetTextTotalWidth(TIMER_VALUE)) / 2)
						  , (float)PADDING);

	agk::SetTextVisible(HEALTH_LABEL, FALSE);
	agk::SetTextVisible(HEALTH_VALUE, FALSE);
	agk::SetTextVisible(SPEED_LABEL, FALSE);
	agk::SetTextVisible(SPEED_VALUE, FALSE);
	agk::SetTextVisible(TIMER_LABEL, FALSE);
	agk::SetTextVisible(TIMER_VALUE, FALSE);
}

void View::showHUDScreen()
{
	agk::SetTextVisible(HEALTH_LABEL, TRUE);
	agk::SetTextVisible(HEALTH_VALUE, TRUE);
	agk::SetTextVisible(SPEED_LABEL,  TRUE);
	agk::SetTextVisible(SPEED_VALUE,  TRUE);
	agk::SetTextVisible(TIMER_LABEL,  TRUE);
	agk::SetTextVisible(TIMER_VALUE,  TRUE);
}

void View::destroyHUDScreen()
{
	agk::DeleteText(HEALTH_LABEL);
	agk::DeleteText(HEALTH_VALUE);
	agk::DeleteText(SPEED_LABEL);
	agk::DeleteText(SPEED_VALUE);
	agk::DeleteText(TIMER_LABEL);
	agk::DeleteText(TIMER_VALUE);
}

void View::buildGameoverScreen()
{
	gameOverScreen.createSprite(); 
 	gameOverScreen.setVisible(FALSE);
}

void View::showGameoverScreen()
{
	gameOverScreen.setVisible(TRUE);
}

void View::buildWinScreen()
{
	// Game Over/Winner Screen
	winnerScreen.createSprite();
	winnerScreen.setVisible(FALSE);
}

void View::showWinScreen()
{
	winnerScreen.setVisible(TRUE);
}