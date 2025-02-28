// /**
//  * Testing BST - Binary Search Tree functions
//  *
//  * This file has series of tests for BST
//  * Each test is independent and uses assert statements
//  * Test functions are of the form
//  *
//  *      test_netidXX()
//  *
//  * where netid is UW netid and XX is the test number starting from 01
//  *
//  * Test functions can only use the public functions from BST
//  * testBSTAll() is called from main in main.cpp
//  * testBSTAll calls all other functions
//  * @author Multiple
//  * @date ongoing
//  */

#include "bstmap.h"
#include <cassert>
#include <sstream>

using namespace std;

// global value for testing
// NOLINTNEXTLINE
stringstream globalSS;

// need to reset SS before calling this
void printer(const BSTMap::value_type &p) {
  globalSS << "[" << p.first << "=" << p.second << "]";
}

// // Testing == and []
void test01() {
  cout << "Starting test01" << endl;
  // cout << "* Testing ==, !=, [] and copy constructor" << endl;
  BSTMap b1;
  // cout << "Created b1!" << endl;

  auto val = b1["hello"];
  // cout << b1 << endl;
  //  cout << b1["hello"] << endl;
  assert(val == 0);
  b1["hello"] = 5;

  val = b1["hello"];
  assert(val == 5);
  b1["world"] = 42;

  BSTMap b2;
  assert(b1 != b2);
  b2["hello"] = 5;
  b2["world"] = 42;
  assert(b1 == b2);

  BSTMap b3(b2);
  assert(b1 == b3);
  // cout << b1 << endl;
  cout << "Ending tes01" << endl;
}

// Testing traversal
void test02() {
  cout << "Starting test02" << endl;
  // cout << "* Testing traversal" << endl;
  BSTMap b;
  b["x"] = 10;
  // cout << b["x"] << endl;

  b["f"] = 5;

  // cout << b["f"] << endl;
  b["b"] = 3;
  // cout << b["b"] << endl;

  b["e"] = 4;
  // cout << b["e"] << endl;
  b["z"] = 50;
  cout << b << endl;
  //  cout << b["z"] << endl;
  //    cout << b;

  globalSS.str("");
  cout << "[TestBST] Testing inorder traversal" << endl;
  b.inorder(printer);
  string order = globalSS.str();
  cout << "printing order: " << order << endl;
  assert(order == "[b=3][e=4][f=5][x=10][z=50]");

  globalSS.str("");
  cout << "[TestBST] Testing preorder traversal" << endl;
  b.preorder(printer);
  order = globalSS.str();
  cout << "printing order: " << order << endl;
  assert(order == "[x=10][f=5][b=3][e=4][z=50]");

  globalSS.str("");
  cout << "[TestBST] Testing postorder traversal" << endl;
  b.postorder(printer);
  order = globalSS.str();
  cout << "printing order: " << order << endl;
  assert(order == "[e=4][b=3][f=5][z=50][x=10]");
  cout << "Ending test02" << endl;
}

// Testing rebalance
void test03() {
  cout << "Starting test03" << endl;
  // cout << "* Testing rebalance" << endl;
  BSTMap b;
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;

  assert(b.height() == 6);
  // cout << b << endl;
  b.rebalance();

  // cout << b << endl;
  assert(b.height() == 3);
  // cout << b << endl;
  b.clear();
  assert(b.height() == 0);
  cout << "Ending test03" << endl;
}

// // Calling all test functions
void testBSTAll() {
  test01();
  test02();
  test03();
}