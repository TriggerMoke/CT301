#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;
// TODO: Enter your First & Last Name
// TODO: Enter your Net ID

// Aidan Michalos
// aidanmih

string program_name;
// No Changes needed, this method queries a user for input
bool GetMadLibFile(ifstream& input_file){
    if (input_file.is_open()){
        input_file.close();
    }

    cout << "Please enter a valid Mad Libs File or 'exit' to close: ";
    string filename;
    getline(cin, filename);
    string temp = filename;
    transform(filename.begin(), filename.end(), filename.begin(), [](unsigned char c){return tolower(c);});

    if (filename == "exit"){
        cout << "Exiting program, Thanks for playing!\n";
        return false;
    }

    input_file.open(temp, ifstream::in);
    if (!input_file){
        cerr << program_name << ", Function: GetMadLibFile. Error File cannot be found/opened: " << filename << ".\n";
        return false;
    }
    
    return true;
}

bool IsFillInBlank(const string &word){
  // Return true if string begins with '_' and ends with either '_' or a punctuation mark following '_'
  return word.front() == '_' && (word.back() == '_' || (word[word.size() - 2] == '_' && ispunct(word.back())));
}

string GetUserResponse(string &fill_in) {
  // Trim the '_' off of the fill in word and query the user for a replacement.
  // See https://www.techiedelight.com/replace-occurrences-character-string-cpp/
  // Use the std library "replace" function to replace all instances of '_' with ' '
  // Remember to remove any floating ' ' characters from the begining and end of the string before requesting the fill in word
  // When getting data back from the user you need to get all of what the user types, they should be able to enter multiple words as their fill in the blank

  // Replace all instances of '_' with ' '
  replace(fill_in.begin(), fill_in.end(), '_', ' ');

  // If the last character is punctuation, remove it
  if (ispunct(fill_in.back())) {
    fill_in.pop_back();
  }

  // Remove any floating ' ' characters from the beginning and end of the string
  fill_in.erase(0, fill_in.find_first_not_of(' '));
  fill_in.erase(fill_in.find_last_not_of(' ') + 1);

  // Query the user for a replacement
  cout << "Please enter a \"" << fill_in << "\": ";
  string user_input;
  getline(cin, user_input);
  return user_input;
}

int main(int, char* argv[]) {
  program_name = argv[0];
  // Create the File reading ifstream.
  ifstream input_file;
  while (GetMadLibFile(input_file)) {
    // Get a line, check to see if any of the words in the line are a fill in word.
    // Remember that getline returns false if the filstream its reading from is in a working state
    // Look into stringstreams as a method to read one word at a time from a string, strinstreams by default white space deliminate each word
    string line;  // A string to save each line of the input file to
    string output;  // A string to save your in progress mad lib file
    // Output the finished madlib like so "Your MadLib!\n\n" followed by their madlib and a new line at the end

    while (getline(input_file, line)) {
      stringstream stream(line);
      string word;
      while (stream >> word) {
        if (IsFillInBlank(word)) {
          string user_input = GetUserResponse(word);
          output += user_input + " ";
        } else {
          output += word + " ";
        }
      }
      output += "\n";
    }
    cout << "Your MadLib!\n\n" << output << "\n";
  }
}


