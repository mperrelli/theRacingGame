#include "template.h"
#include <string>
#include <sstream>
#include "MapLoader.h"
#include "Track.h"
#include "Globals.h"
using namespace AGK;
using namespace std;

MapLoader::MapLoader()
{
	mapName = "";
	mapDescription = "";
	rows = 0;
	cols = 0;
	startPosX = 0;
	startPosY = 0;
	time = 0;
}

// Takes a map file and processes it
void MapLoader::loadFile(string file)
{
	int fIndex = agk::OpenToRead(file.c_str());
	string line;

	if(agk::FileIsOpen(fIndex))
	{
		// Load each line of the map file into an array
		int lineCount = 0;

		while(!agk::FileEOF(fIndex))
		{
			line = agk::ReadLine(fIndex);

			if(line.substr(0, 1) != "#")
			{
				lines[lineCount] = line;
				lineCount++;
			}
		}

		// Iterate through the line array and look for section headers and do 
		// approriate processing for each section.
		for(int i = 0; i < lineCount; i++)
		{
			if(lines[i] == "-meta")
			{
				mapName = lines[i+1].substr(5);
				mapDescription = lines[i+2].substr(12);
				rows = atoi(lines[i+3].substr(5).c_str());
				cols = atoi(lines[i+4].substr(5).c_str());
				startPosX = atoi(lines[i+5].substr(10).c_str());
				startPosY = atoi(lines[i+6].substr(10).c_str());
				AIStartPosX = atoi(lines[i+7].substr(12).c_str());
				AIStartPosY = atoi(lines[i+8].substr(12).c_str());
				time = atoi(lines[i+9].substr(5).c_str());
			}

			if(lines[i] == "-assets")
			{
				assets[0] = lines[i+1].substr(3);
				assets[1] = lines[i+2].substr(3);
				assets[2] = lines[i+3].substr(3);
				assets[3] = lines[i+4].substr(3);
				assets[4] = lines[i+5].substr(3);
				assets[5] = lines[i+6].substr(3);
				assets[6] = lines[i+7].substr(3);
				assets[7] = lines[i+8].substr(3);
				assets[8] = lines[i+9].substr(3);
				assets[9] = lines[i+10].substr(3);
				assets[10] = lines[i+11].substr(3);
				assets[11] = lines[i+12].substr(3);
				assets[12] = lines[i+13].substr(3);
				assets[13] = lines[i+14].substr(3);
				assets[14] = lines[i+15].substr(3);
				assets[15] = lines[i+16].substr(3);
				assets[16] = lines[i+17].substr(3);
			}

			if(lines[i] == "-map")
			{
				for(int j = 1; j <= rows; j++)
				{
					processTrackRow(lines[i + j], j - 1);
				}
			}

			if(lines[i] == "-objects")
			{
				for(int j = 1; j <= rows * OBJECTS_PER_TILEROW; j++)
				{
					processObjectRow(lines[i + j], j - 1);
				}
			}
		}
	}

	agk::CloseFile(fIndex);

	// Store all the data to track object
	storeData();
}

// Iterates through a row of the track and processes each tile
void MapLoader::processTrackRow(string row, int rowNum)
{
    string temp; 
    stringstream ss(row); 

	int counter = 0;

    while (ss >> temp)
	{
		track[rowNum][counter] = applyAssetOffset(atoi(temp.c_str()));
		counter++;
	}
}

// Iterates through a row of the objects and processes each tile
void MapLoader::processObjectRow(string row, int rowNum)
{
    string temp; 
    stringstream ss(row); 

	int counter = 0;

    while (ss >> temp)
	{
		objects[rowNum][counter] = applyAssetOffset(atoi(temp.c_str()));
		counter++;
	}
}

// Stores information to track object
void MapLoader::storeData()
{
	map.setName(mapName);
	map.setDescription(mapDescription);
	map.setCols(cols);
	map.setRows(rows);
	map.setStartPosX(startPosX);
	map.setStartPosY(startPosY);
	map.setAIStartPosX(AIStartPosX);
	map.setAIStartPosY(AIStartPosY);
	map.setAssets(assets);
	map.setTrack(track);
	map.setObjects(objects);
	map.setTime(time);
}

// Returns the track object
Track MapLoader::getTrack()
{
	return map;
}

int MapLoader::applyAssetOffset(int num)
{
	return (num + ASSETS_START_INDEX) - ASSET_OFFSET;
}

MapLoader::~MapLoader(void)
{
}
