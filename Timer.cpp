#include "template.h"
#include <ctime>
#include "Timer.h"
#include "Globals.h"
using namespace AGK;
using namespace std;

// Global static pointer used to ensure a single instance of the class.
Timer* Timer::m_pInstance = NULL;  

/** This function is called to create an instance of the class. 
    Calling the constructor publicly is not allowed. The constructor 
    is private and is only called by this Instance function.
*/
  
Timer* Timer::Instance()
{
   if (!m_pInstance)   // Only allow one instance of class to be generated.
      m_pInstance = new Timer();

   return m_pInstance;
}

Timer::Timer()
{
	ticks = 0;
}

int Timer::getElapsedTime()
{
	return ticks;
}

int Timer::getElapsedTimeSec()
{
	return ticks / TICKS_PER_SEC;
}

void Timer::tick()
{
	ticks++;
}