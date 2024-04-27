#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED

#include <string>
#include <iostream>
#include <array>

struct game_save_state {
    std::string game_board;
    char live;
    char dead;
};

class GameOfLife
{
    // Keep getting this annoying error about order of declaration...
    int height_ = 0; int width_ = 0; char liveCell_ = '*'; char deadCell_ = '-';

    std::string current_;
    int generations_ = 0;
    int safeGenerations_ = 0;
    std::array<game_save_state, 100> previousGenerations_;

    
private:
    GameOfLife(int height, int width, std::string gameBoard, char liveCell, char deadCell);
public:
    GameOfLife() = delete;
    GameOfLife(std::string filename);
    GameOfLife(std::string filename, int genCount);
    GameOfLife(std::string filename, char liveCell, char deadCell);
    GameOfLife(std::string filename, char liveCell, char deadCell, int genCount);

    // The Big Five
    GameOfLife(const GameOfLife& other); // Copy constructor
    GameOfLife& operator=(const GameOfLife& other); // Copy assignment operator
    ~GameOfLife(); // Destructor
    GameOfLife(GameOfLife&& other) noexcept = default; // Move constructor
    GameOfLife& operator=(GameOfLife&& other) noexcept = default; // Move assignment operator

    friend std::ostream &operator<<(std::ostream &os, const GameOfLife &game);

    void NextGen();
    void NextNGen(int n);
    int GetGenerations() const;

    // Changes the current Live or Dead cell to a new character. 
    //It cannot be set to whatever the current Dead/Live Cell character is.
    //It throws a runtime error if the display characters are duplicated
    void SetLiveCell(char liveCell);
    void SetDeadCell(char deadCell);

    GameOfLife& operator++();
    GameOfLife operator++(int);

    GameOfLife& operator+=(int gens); // Increment the game by a certain number of generations
    GameOfLife& operator-=(int gens); // Decrement the game by a certain number of generations
    GameOfLife operator+(int gens) const; // Return a new game incremented by a certain number of generations
    GameOfLife operator-(int gens) const; // Return a new game decremented by a certain number of generations
    GameOfLife& operator--(); // Decrement the game by one generation
    GameOfLife operator--(int); // Decrement the game by one generation and return a copy of the game state prior to the decrementation
    GameOfLife operator-() const; // Return a copy of the game where all cells have swapped live/dead states


    // Comparison operators
    bool operator==(const GameOfLife&) const;
    bool operator<(const GameOfLife&) const;
    bool operator>(const GameOfLife&) const;
    bool operator<=(const GameOfLife&) const;
    bool operator>=(const GameOfLife&) const;

    // More functions!
    std::string GenWindow(int row, int col, int height, int width);
    GameOfLife GenSubGame(int row, int col, int height, int width);
    void ToggleCell(int index);
    void ToggleCell(int row, int col);
    bool IsStillLife();
    int GetAvailableGens();
};

// Operator Overload for << for game state output
std::ostream &operator<<(std::ostream &os, const GameOfLife &game);

#endif