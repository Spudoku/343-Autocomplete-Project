#include "autocomplete.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
void printVector(const vector<BSTMap::value_type> v) {
  // cout << "; size = " << v.size() << endl;
  for (int i = 0; i < v.size(); i++) {
    // cout << "(" << v[i].first << ", " << v[i].second << "), " << endl;
  }
  // cout << endl;
}
void testAC01() {
  // cout << "Starting AC test01" << endl;
  // cout << "* Testing basic autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("hel");
  assert(v.size() == 2);
  ac.printPhrases();
  assert(v[0].first == "help");
  assert(v[0].second == 20);
  assert(v[1].first == "hello");
  assert(v[1].second == 10);
  // cout << "Ending tesAC01" << endl;
}

void testAC02a() {
  // cout << "Starting AC test02" << endl;
  // cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  // cout << "reading file cities.txt" << endl;
  ac.readFile("cities.txt");
  // ac.printPhrases();
  // cout << "testing complete with 'Sea'" << endl;
  auto v = ac.complete("Seas");

  printVector(v);
}

void testAC02b() {
  // cout << "Starting AC test02" << endl;
  // cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  // cout << "reading file cities.txt" << endl;
  ac.readFile("cities.txt");
  // cout << "number of phrases actually inserted: " << ac.phrasesSize() <<
  // endl;
  assert(ac.phrasesSize() == 93827);
  // ac.printPhrases();
  // // cout << "testing complete with 'Zat'" << endl;
  auto v = ac.complete("Zat");

  printVector(v);
}
void testAC02() {
  // cout << "Starting AC test02" << endl;
  // cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  // cout << "reading file cities.txt" << endl;
  ac.readFile("cities.txt");
  // ac.printPhrases();
  // cout << "testing complete with 'Sea'" << endl;
  auto v = ac.complete("Sea");

  assert(v.size() == 47);
  assert(v[0].first == "Seattle, Washington, United States");
  assert(v[0].second == 608660);
  assert(v[46].first == "Seabeck, Washington, United States");
  assert(v[46].second == 1105);
  // cout << "Ending tesAC02" << endl;
}

void testAC03() {
  // cout << "Starting AC test03" << endl;
  Autocomplete ac;
  ac.readFile("wiktionary.txt");
  auto v = ac.complete("is");
  assert(v.size() == 13);
  auto v2 = ac.complete("as");
  assert(v2.size() == 58);
  // cout << "Ending tesAC03" << endl;
}

// // Calling all test functions
void testACAll() {
  testAC01();
  // testAC02a();
  // testAC02b();
  // testAC02();
  testAC03();
}