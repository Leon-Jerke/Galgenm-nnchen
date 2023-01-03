#include "Logger.h"

Logger::Logger(string filename)
{
	mLogfile.open(filename);
}

Logger::~Logger()
{
	mLogfile.close();
}

void Logger::Log(string message)
{
	mLogfile << message << endl;
	cout << message << endl;
}