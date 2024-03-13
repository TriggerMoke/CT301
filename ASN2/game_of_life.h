#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED

/* * * * * * * * * * * * *
 *                       *
 *    USING OPTION 1     *
 *                       *
 * * * * * * * * * * * * */

#include <string>
#include <iostream>


class GameOfLife
{
    std::string current_;
    int generations_ = 0, width_ = 0, height_ = 0;
    char deadCell_ = '-', liveCell_ = '*';
public:
    GameOfLife() = delete;
    GameOfLife(std::string filename);
    GameOfLife(std::string filename, int genCount);
    GameOfLife(std::string filename, char liveCell, char deadCell);
    GameOfLife(std::string filename, char liveCell, char deadCell, int genCount);

    // The Big Five
    GameOfLife(const GameOfLife& other) = default; // Copy constructor
    GameOfLife& operator=(const GameOfLife& other) = default; // Copy assignment operator
    ~GameOfLife() = default; // Destructor
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
    void GameOfLife::UpdateCellChars(char oldChar, char newChar);

    GameOfLife operator+(int n) const;
    GameOfLife& operator+=(int n);
    GameOfLife& operator++();
    GameOfLife operator++(int);

    // Comparison operators
    bool operator==(const GameOfLife&) const;
    bool operator<(const GameOfLife&) const;
    bool operator>(const GameOfLife&) const;
    bool operator<=(const GameOfLife&) const;
    bool operator>=(const GameOfLife&) const;
};

// Operator Overload for << for game state output
std::ostream &operator<<(std::ostream &os, const GameOfLife &game);
#endif