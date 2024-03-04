#include <iostream>
#include "game_of_life.h"

using namespace std;

int main(int argc, char const *argv[])
{
    // Test constructor with filename
    GameOfLife game("gamestarter.txt");
    cout << "Initial Game State:" << endl;
    cout << game;

    // Test NextGen
    game.NextGen();
    cout << "After NextGen:" << endl;
    cout << game;

    // Test NextNGen
    game.NextNGen(5);
    cout << "After NextNGen(5):" << endl;
    cout << game;

    // Test constructor with filename, live cell, dead cell chars
    GameOfLife game2("gamestarter.txt", '*', '+');
    cout << "New Game with Custom Cells:" << endl;
    cout << game2;

    // Test SetLiveCell and SetDeadCell
    try {
        game2.SetLiveCell('#');
        game2.SetDeadCell('-');
        cout << "After Changing Live/Dead Cells:" << endl;
        cout << game2;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    // Test constructor with filename, live cell, dead cell chars, and generation count
    GameOfLife game3("gamestarter.txt", '@', '.', 10);
    cout << "New Game with Custom Cells and 10 Generations Precomputed:" << endl;
    cout << game3;

    // Test arithmetic and increment operators
    game++;
    cout << "After Increment (++) Operator:" << endl;
    cout << game;

    GameOfLife game4 = game + 5;
    cout << "After Adding 5 Generations (game + 5):" << endl;
    cout << game4;

    game += 3;
    cout << "After Adding 3 Generations (game += 3):" << endl;
    cout << game;

    // Test comparison operators
    cout << "Comparing game and game4: " << endl;
    cout << "Are they equal? " << (game == game4 ? "Yes" : "No") << endl;
    cout << "Is game less than game4? " << (game < game4 ? "Yes" : "No") << endl;
    cout << "Is game greater than game4? " << (game > game4 ? "Yes" : "No") << endl;
    cout << "Is game less than or equal to game4? " << (game <= game4 ? "Yes" : "No") << endl;
    cout << "Is game greater than or equal to game4? " << (game >= game4 ? "Yes" : "No") << endl;

    return 0;
}
