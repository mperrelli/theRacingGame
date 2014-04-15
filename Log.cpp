#include "template.h"
#include "Log.h"
#include <string>
#include <sstream>
using namespace AGK;
using namespace std;

// Global static pointer used to ensure a single instance of the class.
Log* Log::m_pInstance = NULL;  

/** This function is called to create an instance of the class. 
    Calling the constructor publicly is not allowed. The constructor 
    is private and is only called by this Instance function.
*/
  
Log* Log::Instance()
{
   if (!m_pInstance)   // Only allow one instance of class to be generated.
      m_pInstance = new Log();

   return m_pInstance;
}

Log::Log()
{
	agk::OpenToWrite(1, "logFile.log");
}

void Log::writeToLogFile(string line)
{
	agk::WriteLine(1, line.c_str());
}

void Log::writeToLogFile(int i)
{
	ostringstream ss;
	ss << i;
	string s(ss.str());

	writeToLogFile(s);
}

void Log::writeToLogFile(float i)
{
	ostringstream ss;
	ss << i;
	string s(ss.str());

	writeToLogFile(s);
}