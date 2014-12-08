#include <iostream>
#include <iomanip>
#include <map>
#include <fstream>
#include <string>
#include <algorithm> 
#include <vector>

using namespace std;

void clean_dish(string& plate);

int main()
{
  ifstream input_file;
  vector<string> words;
  string filename{"example.txt"};
  string current{""};
    
  cout << "Mata in filnamn: ";    
  cin >> filename;
  input_file.open(filename);

  if(!(input_file.is_open()))
  {
    cerr << "Error, file not found.\n";
    return 1;
  }

  while(input_file >> current)
  {
    string new_current;

    clean_dish(current);

    if (all_of(current.begin(), current.end(), [](char& c){ c = tolower(c); return(isalpha(c) || (c == '-'));}))
    {
      if(!(current[0] == '-' || current[current.size()-1] == '-'))
      {
        new_current = current;
      }
    }
    if(new_current.length() > 2)
    {
      words.push_back(new_current);
    }
  }

  input_file.close();
  
  for ( string t: words )
  {
    cout << t << ' ';
  }


  cout << endl;
}

void clean_dish(string& plate)
{
  string back_dirt = "\")!?;,:.'";
  string front_dirt = "\"(";
  char b = plate.back();
  char f = plate.front();
  while(back_dirt.find(b) != string::npos)
  {
    plate.erase(plate.end()-1);
    b = plate.back();
  }
  while(front_dirt.find(f) != string::npos)
  {
    plate.erase(plate.begin());
    f = plate.front();
  }
  if(plate.find("--") != string::npos)
  {
    plate = "";
  }
}
