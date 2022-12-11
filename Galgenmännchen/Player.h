#pragma once
#include <string>

class Player
{
public:
	Player(std::string Name);
	~Player() {};
private:
	std::string mName;
	int mWrongTrys;
	int mWinScore;

};