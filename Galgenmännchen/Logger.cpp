#include "Logger.h"

Logger::Logger()
{
	mLogfile.open("GameLog.txt");
}

Logger::~Logger()
{
	mLogfile.close();
}

Logger* Logger::mLoggerInstance = nullptr; // Pointer muss einmal deklariert werden

Logger* Logger::GetInstance()
{
	if (mLoggerInstance == nullptr)		// Wenn noch kein Logger Objekt existiert, muss erst eins erzeugt werden
	{
		mLoggerInstance = new Logger();
	}

	return mLoggerInstance;
}

void Logger::Log(string message)
{
	mLogfile << message << endl;
	cout << message << endl;
}

void Logger::LogOnly(string message)
{
	mLogfile << message << endl;
}