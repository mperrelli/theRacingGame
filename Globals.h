#pragma once
/*****************************/
/* GLOBAL IMAGE INDEXES      */
/*****************************/
const int ASSETS_START_INDEX = 50;
const int ASSET_OFFSET       = 10;
const int MAX_ASSETS         = 17;
const int BG               = ASSETS_START_INDEX;
const int TRACK_H          = ASSETS_START_INDEX + 1;
const int TRACK_V          = ASSETS_START_INDEX + 2;
const int TRACK_TURN_EN    = ASSETS_START_INDEX + 3;
const int TRACK_TURN_ES    = ASSETS_START_INDEX + 4;
const int TRACK_TURN_WN    = ASSETS_START_INDEX + 5;
const int TRACK_TURN_WS    = ASSETS_START_INDEX + 6;
const int BARRIER_H        = ASSETS_START_INDEX + 7;
const int BARRIER_V        = ASSETS_START_INDEX + 8;
const int BARRIER_TURN_EN  = ASSETS_START_INDEX + 9;
const int BARRIER_TURN_ES  = ASSETS_START_INDEX + 10;
const int BARRIER_TURN_WN  = ASSETS_START_INDEX + 11;
const int BARRIER_TURN_WS  = ASSETS_START_INDEX + 12;
const int BARRIER_END_EW   = ASSETS_START_INDEX + 13;
const int BARRIER_END_NS   = ASSETS_START_INDEX + 14;
const int BARRIER_END_SN   = ASSETS_START_INDEX + 15;
const int BARRIER_END_WE   = ASSETS_START_INDEX + 16;

const int TRACK_ATLAS_START_INDEX = 200;

const int AI_SPRITE_START_INDEX = 1500;

const int CAR = 2;
const int CAR_MOVING = 3;

/***************************/
/* IMAGE/SPRITE INDICES    */
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
const int CHOOSE_TRACK_SCREEN_INDEX     = 11;
const int LINEAR_INDEX				    = 12;
const int LOOP_INDEX					= 13;
const int WINNER_SCREEN_INDEX			= 14; 
const int GAME_OVER_SCREEN_INDEX		= 15;

// Sound and Music indexes
const int TITLE_SCREEN_MUSIC = 1;
const int GAME_OVER_MUSIC	 = 2;

// Text Indexes
const int HEALTH_LABEL = 1;
const int HEALTH_VALUE = 2;
const int SPEED_LABEL  = 3;
const int SPEED_VALUE  = 4;
const int TIMER_LABEL  = 5;
const int TIMER_VALUE  = 6;

/*****************************/
/* SCREEN DATA               */
/*****************************/
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_CENTER_X = SCREEN_WIDTH / 2;
const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;

/*****************************/
/* TILE AND TRACK SIZES      */
/*****************************/
const int TRACK_TILE_SIZE = 128;
const int OBJECT_TILE_SIZE = 32;
const int OBJECTS_PER_TILEROW = TRACK_TILE_SIZE / OBJECT_TILE_SIZE;
const int TRACK_MAX_SIZE_ROWS = 20;
const int TRACK_MAX_SIZE_COLS = 20;
const int OBJECT_MAX_SIZE_COLS = 80;
const int OBJECT_MAX_SIZE_ROWS = 80;

/*****************************/
/* SPRITE GROUPS             */
/*****************************/
const int SPRITE_GROUP_TRACK     = 1;
const int SPRITE_GROUP_SELECTION = 2;

/*****************************/
/* SPRITE DEPTHS             */
/*****************************/
const int SPRITE_AI_DEPTH = -1;

/*****************************/
/* VEHICLE DATA              */
/*****************************/
const int VEHICLE_FRAME_HEIGHT = 29;
const int VEHICLE_FRAME_WIDTH  = 70;
const int VEHICLE_FRAMES       = 8;

/*****************************/
/* INTERVALS                 */
/*****************************/
const int ADD_AI_INTERVAL = 200;
const int COLLISION_CHECK_INTERVAL = 10;

/*****************************/
/* RANGES                    */
/*****************************/
const int AI_SPEED_LOW = 7;
const int AI_SPEED_HIGH = 12;
const int AI_CHECK_LOW = 7;
const int AI_CHECK_HIGH = 13;

/**************************************/
/* DIRECTION AND CORRESPONDING ANGLES */
/**************************************/
const int EAST_ANGLE     = 0;
const int EASTHIGH_ANGLE = 360;
const int SOUTH_ANGLE    = 90;
const int WEST_ANGLE     = 180;
const int NORTH_ANGLE    = 270;

const int NORTH = 1;
const int WEST  = 2;
const int SOUTH = 3;
const int EAST  = 4;

/*****************************/
/* TIME                      */
/*****************************/
const int TICKS_PER_SEC = 70;