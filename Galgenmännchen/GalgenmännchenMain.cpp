#include <iostream>
#include "Game.h"
#include <random>

int main()
{
    //std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
    ////seed the random number generator
    //std::srand(std::time(nullptr));
    ////shuffle the vector
    //std::random_shuffle(v.begin(), v.end());

    ////print out the shuffled vector
    //for (auto const& i : v)
    //    std::cout << i << ' ';
    //std::cout << '\n';

    //return 0;

    Game game = Game();
    game.Setup();
    bool continuePlaying = true;
    do
    {
        continuePlaying = game.StartRound();
    } while (continuePlaying);

    return 0;
}
