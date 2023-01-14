//Hilfsfunktionen die Klassen unabhängig sind und von allen Klassen verwendet werden können

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace Helper
{
	static bool ContainsChar(const vector<char>& vector, const char& c)  // Hilfsfunktion um zu prüfen ob ein vector mit chars ein bestimmten char enthält
	{
		for (int i = 0; i < vector.size(); i++) {
			if (tolower(vector.at(i)) == tolower(c))
				return true;
		}
		return false;
	}

	static bool ContainsChar(const string& str, const char& c) {         // Hilfsfunktion um zu prüfen ob ein String ein bestimmten char enthält
		for (int i = 0; i < str.length(); i++) {
			if (tolower(str.at(i)) == tolower(c))
				return true;
		}
		return false;
	}


	static bool ContainsString(const vector<std::string>& strVec, string str)
	{
		// Wandle alle Buchstaben in Kleinbuchstaben um, um die Wörter besser vergleichen zu können
		string strLower = str;
		transform(strLower.begin(), strLower.end(), strLower.begin(), ::tolower);

		for (const string& existing_word : strVec)
		{
			string word = existing_word;
			transform(word.begin(), word.end(), word.begin(), ::tolower);

			if (word == strLower)
				return true;
		}
		return false;
	}

	static bool EqualStrings(const string& string_1, const string& string_2) // Hilfsfunktion um zu prüfen ob zwei Strings gleich sind, unabhängig von der Groß- und Kleinschreibung
	{
		return std::equal(string_1.begin(), string_1.end(),
			string_2.begin(), string_2.end(),
			[](char a, char b) {
				return tolower(a) == tolower(b);
			});
	}
}