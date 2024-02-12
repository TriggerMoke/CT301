#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "game_of_life.h"

using namespace std;

game_of_life::game_of_life(string filename)
{
    //Create a file input using the user's input
    fstream file_in(filename);
    if (!file_in)
    {
        //File not found
        throw(runtime_error("File not found"));
    }
    if (!(file_in >> this->width_))
    {
        //Invalid file format
        throw(runtime_error("Invalid file format"));
    }
    //Pre Load Current with the "dead_cell" character as a square table
    this->current_ = string(this->width_ * this->width_, '-');
    string line;
    getline(file_in, line); //Skipping the end of the first line to get to the data
    //For all rows in the file
    for (int row = 0; row < this->width_; ++row)
    {
        getline(file_in, line);
        //For all Columns in the row
        for (int col = 0; col < this->width_; ++col)
        {
            if (line[col] == '*')
            {
                //Only updates the character if It needs to be
                this->current_[col + (row * this->width_)] = '*';
            }
        }
    }
}
ostream &operator<<(ostream &os, const game_of_life &game)
{
    return os;
}
