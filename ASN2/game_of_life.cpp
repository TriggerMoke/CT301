// Aidan Michalos

/* * * * * * * * * * * * *
 *                       *
 *    USING OPTION 1     *
 *                       *
 * * * * * * * * * * * * */

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "game_of_life.h"

using namespace std;

// Constructors

GameOfLife::GameOfLife(string filename)
{
  fstream file_in(filename);
  if (!file_in)
  {
    throw(runtime_error("File not found: " + filename + ". Please make sure the file exists and the path is correct."));
  }

  if (!(file_in >> this->width_ >> this->height_))
  {
    throw(runtime_error("Invalid file format: The first two lines of the file must contain two integers representing the width and the height of the grid."));
  }

  this->current_ = string(this->width_ * this->height_, this->deadCell_);
  string line;
  getline(file_in, line); // Skipping the end of the first line

  for (int row = 0; row < this->height_; ++row)
  {
    getline(file_in, line);
    for (int col = 0; col < this->width_; ++col)
    {
      if (line[col] == this->liveCell_)
      {
        this->current_[col + (row * this->width_)] = this->liveCell_;
      }
    }
  }
}

GameOfLife::GameOfLife(string filename, int genCount) : GameOfLife(filename)
{
  NextNGen(genCount);
}

GameOfLife::GameOfLife(string filename, char liveCell, char deadCell) : GameOfLife(filename)
{
  SetLiveCell(liveCell);
  SetDeadCell(deadCell);
}

GameOfLife::GameOfLife(string filename, char liveCell, char deadCell, int genCount) : GameOfLife(filename)
{
  SetLiveCell(liveCell);
  SetDeadCell(deadCell);
  NextNGen(genCount);
}

// Setters for live and dead cells
void GameOfLife::SetLiveCell(char liveCell)
{
  if (liveCell == deadCell_)
  {
    throw runtime_error("Live cell character cannot be the same as dead cell character.");
  }
  liveCell_ = liveCell;
}

void GameOfLife::SetDeadCell(char deadCell)
{
  if (deadCell == liveCell_)
  {
    throw runtime_error("Dead cell character cannot be the same as live cell character.");
  }
  deadCell_ = deadCell;
}

// Operator Overloads

/* Overloads the << operator to print the current state of the game.
 * Displays the generation count and the game board in a readable format. */
ostream &operator<<(ostream &os, const GameOfLife &game)
{
  os << "Generation: " << game.generations_ << "\n";
  for (int row = 0; row < game.height_; ++row)
  {
    for (int col = 0; col < game.width_; ++col)
    {
      int index = row * game.width_ + col;
      os << (game.current_[index] == game.liveCell_ ? game.liveCell_ : game.deadCell_);
    }
    os << "\n";
  }
  return os;
}

GameOfLife GameOfLife::operator+(int n) const
{
  GameOfLife temp = *this;
  temp.NextNGen(n);
  return temp;
}

GameOfLife &GameOfLife::operator+=(int n)
{
  NextNGen(n);
  return *this;
}

GameOfLife &GameOfLife::operator++()
{
  NextGen();
  return *this;
}

GameOfLife GameOfLife::operator++(int)
{
  GameOfLife temp = *this;
  NextGen();
  return temp;
}

// Comparison operators
bool GameOfLife::operator==(const GameOfLife &other) const
{
  double tolerance = 0.005; // 0.5%
  double thisPercent = static_cast<double>(count(this->current_.begin(), this->current_.end(), this->liveCell_)) / (this->width_ * this->height_);
  double otherPercent = static_cast<double>(count(other.current_.begin(), other.current_.end(), other.liveCell_)) / (other.width_ * other.height_);
  return abs(thisPercent - otherPercent) <= tolerance;
}

bool GameOfLife::operator<(const GameOfLife &other) const
{
  double thisPercent = static_cast<double>(count(this->current_.begin(), this->current_.end(), this->liveCell_)) / (this->width_ * this->height_);
  double otherPercent = static_cast<double>(count(other.current_.begin(), other.current_.end(), other.liveCell_)) / (other.width_ * other.height_);
  return thisPercent < otherPercent;
}

bool GameOfLife::operator>(const GameOfLife &other) const
{
  return other < *this;
}

bool GameOfLife::operator<=(const GameOfLife &other) const
{
  return !(other < *this);
}

bool GameOfLife::operator>=(const GameOfLife &other) const
{
  return !(*this < other);
}

/* Calculates the next generation based on the current state.
 * Applies the rules provided for Game of Life, considering wrap-around for neighbor calculations. */
void GameOfLife::NextGen()
{
  string next_generation = this->current_; // Create a copy of the current state for the next generation

  for (int row = 0; row < this->height_; ++row)
  {
    for (int col = 0; col < this->width_; ++col)
    {
      int index = row * this->width_ + col;
      int alive_neighbors = 0;

      // Check all 8 neighbors with wrap around
      for (int dr = -1; dr <= 1; ++dr)
      {
        for (int dc = -1; dc <= 1; ++dc)
        {
          if (dr == 0 && dc == 0)
            continue; // Skip the cell itself

          int neighbor_row = (row + dr + this->height_) % this->height_;
          int neighbor_col = (col + dc + this->width_) % this->width_;
          int neighbor_index = neighbor_row * this->width_ + neighbor_col;

          // Check if the neighbor is alive
          if (this->current_[neighbor_index] == this->liveCell_)
          {
            alive_neighbors++;
          }
        }
      }

      // Apply Game of Life rules
      bool is_alive = this->current_[index] == this->liveCell_;
      if (is_alive && (alive_neighbors < 2 || alive_neighbors > 3))
      {
        next_generation[index] = this->deadCell_; // Die due to underpopulation or overpopulation
      }
      else if (!is_alive && alive_neighbors == 3)
      {
        next_generation[index] = this->liveCell_; // Become alive through reproduction
      }
      // Cells that do not change state remain as they are in next generation
    }
  }

  this->current_ = next_generation; // Update the current generation
  this->generations_++;             // Increment generation count
}

/* Advances the game by 'n' generations. Utilizes NextGen to update the game state multiple times.
 * If 'n' is less than or equal to 0, it does nothing. */
void GameOfLife::NextNGen(int n)
{
  while (n-- > 0)
  {
    NextGen();
  }
}

/* Returns the number of generations that have passed since the start of the game. */
int GameOfLife::GetGenerations() const
{
  return this->generations_;
}
