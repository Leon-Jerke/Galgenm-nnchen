#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Logger
{
public:
	Logger(string filename);
	~Logger();
	void Log(string msg);
	void LogOnly(string msg);

private:
	ofstream mLogfile;
};