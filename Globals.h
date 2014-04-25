#pragma once
/*****************************/
/* GLOBAL IMAGE INDEXES      */
/*****************************/
const int ASSETS_START_INDEX = 50;
const int ASSET_OFFSET       = 10;
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

const int CAR = 2;
const int CAR_MOVING = 3;

/*****************************/
/* SCREEN DATA               */
/*****************************/
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_CENTER_X = SCREEN_WIDTH / 2;
const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;

/*****************************/
/* TILE SIZES                */
/*****************************/
const int TRACK_TILE_SIZE = 128;
const int OBJECT_TILE_SIZE = 32;

/*****************************/
/* Sprite Groups             */
/*****************************/
const int SPRITE_GROUP_TRACK     = 1;
const int SPRITE_GROUP_SELECTION = 2;

/*****************************/
/* Vehicle Data              */
/*****************************/
const int VEHICLE_FRAME_HEIGHT = 29;
const int VEHICLE_FRAME_WIDTH  = 70;
const int VEHICLE_FRAMES       = 8;