#include <iostream>
#include "game_of_life.h"
using namespace std;

int main(int argc, char const *argv[])
{
    game_of_life game("gamestarter.txt");
    cout << game;
    game.NextGen();
    cout << game;
    game.NextNGen(2);
    cout << game;
    return 0;
}
