#pragma once
#include "template.h"
using namespace std;

class Timer
{
public:
	static Timer* Instance();
	int getElapsedTime();
	int getElapsedTimeSec();
	void tick();

private:
	Timer();  // Private so that it can  not be called
	Timer(Timer const&){};             // copy constructor is private
	Timer& operator=(Timer const&){};  // assignment operator is private
	static Timer* m_pInstance;
	
	int ticks;
};
