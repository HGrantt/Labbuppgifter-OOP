#include <iostream>
#include <iomanip>
#include <map>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm> 
#include <vector>

using namespace std;

void clean_dish(string& plate);

int main()
{
  ifstream input_file;
  map<string, int> words;
  string filename{"example.txt"};
  string current{""};
  int count{0};
  unsigned int longest_word{0};

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
      ++words[new_current];
    }
	
    if(new_current.length() > longest_word)
    {
      longest_word = new_current.length();
    }    
  }

  input_file.close();
  
  cout << "Orden alfabetiskt:" << endl;

  vector<pair<string, int>> _words;
  for (pair<string, int> w: words)
  {
    pair<string, int> current{w.first, w.second};
    _words.push_back(current);
  }

  stable_sort(_words.begin(), _words.end(), 
              []( pair<string, int> a, pair<string, int> b){ return a.second > b.second;});

  for ( pair<string, int> t: _words )
  {
    ++count;
    cout << right << setw(longest_word) << t.first << " : " << t.second << endl;
  }

  cout << endl <<  "words found: " << count << endl << endl;
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
