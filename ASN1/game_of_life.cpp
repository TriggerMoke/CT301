// Aidan Michalos

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
        throw(runtime_error("File not found: " + filename + ". Please make sure the file exists and the path is correct."));
    }
    if (!(file_in >> this->width_))
    {
        //Invalid file format
        throw(runtime_error("Invalid file format: The first line of the file must contain a single integer representing the width of the square grid."));
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

/* Overloads the << operator to print the current state of the game.
 * Displays the generation count and the game board in a readable format. */
ostream &operator<<(ostream &os, const game_of_life &game) {
    os << "Generation: " << game.generations_ << "\n";
    for (int row = 0; row < game.width_; ++row) {
        for (int col = 0; col < game.width_; ++col) {
            int index = row * game.width_ + col;
            os << game.current_[index];
        }
        os << "\n"; // New line at the end of each row
    }
    return os;
}


/* Calculates the next generation based on the current state.
 * Applies the rules provided for Game of Life, considering wrap-around for neighbor calculations. */
void game_of_life::NextGen() {
    string next_generation = this->current_; // Create a copy of the current state for the next generation

    for (int index = 0; index < this->width_ * this->width_; ++index) {
        int row = index / this->width_;
        int col = index % this->width_;
        int alive_neighbors = 0;

        // Check all 8 neighbors with wrap around
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr == 0 && dc == 0) continue; // Skip the cell itself

                // Calculate neighbor's row and column with wrap-around
                int neighbor_row = (row + dr + this->width_) % this->width_;
                int neighbor_col = (col + dc + this->width_) % this->width_;
                int neighbor_index = neighbor_row * this->width_ + neighbor_col;

                // Check if the neighbor is alive
                if (this->current_[neighbor_index] == '*') {
                    alive_neighbors++;
                }
            }
        }

        // Apply Game of Life rules
        bool is_alive = this->current_[index] == '*';
        if (is_alive && (alive_neighbors < 2 || alive_neighbors > 3)) {
            next_generation[index] = '-'; // Die due to underpopulation or overpopulation (rule 1 and 3)
        } else if (!is_alive && alive_neighbors == 3) {
            next_generation[index] = '*'; // Become alive through 3 neighbors
        }
        // If the cell stays the same, no need to modify next_generation
    }

    this->current_ = next_generation; // Update the current generation
    this->generations_++; // Increment generation count
}

/* Advances the game by 'n' generations. Utilizes NextGen to update the game state multiple times.
 * If 'n' is less than or equal to 0, it does nothing. */
void game_of_life::NextNGen(int n) {
    while (n-- > 0) {
        NextGen();
    }
}

/* Returns the number of generations that have passed since the start of the game. */
int game_of_life::GetGenerations() const {
    return this->generations_;
}