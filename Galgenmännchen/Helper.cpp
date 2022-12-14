//Hilfsfunktionen die Klassen unabh?ngig sind und von allen Klassen verwendet werden k?nnen

#include <fstream>
#include <vector>
#include <string>

using namespace std;

namespace Helper
{
	static bool ContainsChar(const vector<char>& vector, const char& c)  // Hilfsfunktion um zu pr?fen ob ein vector mit chars ein bestimmten char enth?lt
	{
		for (int i = 0; i < vector.size(); i++) {
			if (tolower(vector.at(i)) == tolower(c))
				return true;
		}
		return false;
	}

	static bool ContainsChar(const string& str, const char& c) {         // Hilfsfunktion um zu pr?fen ob ein String ein bestimmten char enth?lt
		for (int i = 0; i < str.length(); i++) {
			if (tolower(str.at(i)) == tolower(c))
				return true;
		}
		return false;
	}

	static bool EqualStrings(const string& string_1, const string& string_2) // Hilfsfunktion um zu pr?fen ob zwei Strings gleich sind, unabh?ngig von der Gro?- und Kleinschreibung
	{
		return std::equal(string_1.begin(), string_1.end(),
			string_2.begin(), string_2.end(),
			[](char a, char b) {
				return tolower(a) == tolower(b);
			});
	}
}