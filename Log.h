#pragma once
#include "template.h"
#include <string>
using namespace std;

class Log
{
public:
	static Log* Instance();
	void writeToLogFile(string line);

private:
	Log();  // Private so that it can  not be called
	Log(Log const&){};             // copy constructor is private
	Log& operator=(Log const&){};  // assignment operator is private
	static Log* m_pInstance;

};
