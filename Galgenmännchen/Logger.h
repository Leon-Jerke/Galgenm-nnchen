#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Logger						// Singleton Klasse = es kann nur ein einziges Objekt dieser Klasse erzeugt werden
{
public:
	static Logger* GetInstance();	// Gibt einen Pointer auf ein Logger Objekt zurück
	void Log(string msg);			// Logt den String und zeigt ihn in der Konsole an
	void LogOnly(string msg);		// Logt den String ohne ihn anzuzeigen
private:
	Logger();						// Konstruktor ist private damit keine Objekte vom Logger auserhalb erzeugt werden können
	~Logger();

	static Logger* mLoggerInstance;	// Pointer auf das einzige existierende Logger Objekt
	ofstream mLogfile;				// Log Datei
};