#include "autocomplete.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void testBSTAll();

// builds phrases by reading a file
void Autocomplete::readFile(const string &fileName) {
  // // cout << "Reading file " << fileName << endl;
  ifstream ifs(fileName);

  // ifs.open(fileName);
  // traverse the file
  string line;
  getline(ifs, line);

  while (getline(ifs, line)) {
    // // cout << "line: " << line << endl;
    stringstream ss(line);
    int number;
    string name;
    ss >> number;
    getline(ss >> ws, name);

    phrases[name] = number;
  }
  // cout << "[ReadFile] phrases size: " << phrasesSize() << endl;
  ifs.close();
  // cout << "[ReadFile] rebalancing!" << endl;
  phrases.rebalance();
}

// usage: sot(v.begin(),v.end(),sortByWeight(a,b))
bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

// Calls getAll, then sorts the resultint vector before
// returing the final result
vector<BSTMap::value_type>
Autocomplete::complete(const BSTMap::key_type &prefix) const {
  vector<BSTMap::value_type> v = phrases.getAll(prefix);
  // TODO(student)
  sort(v.begin(), v.end(), sortByWeight);
  return v;
}

// debugging method for printing all of phrases
void Autocomplete::printPhrases() { cout << phrases << endl; }

// returns the size of phrases
int Autocomplete::phrasesSize() const { return phrases.size(); }
