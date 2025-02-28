// Yusuf Pisan pisan@uw.edu
// 17 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <cassert>
#include <iomanip>
#include <sstream>

// #include <iostream>
// #include <string>

using namespace std;

// copy constructor
BSTMap::BSTMap(const BSTMap &bst) {
  // deallocate memory first
  clear();

  // get copy
  root = copyTree(bst.root);
}

// copy the tree
BSTMap::Node *BSTMap::copyTree(const Node *n) const {
  Node *newN = nullptr; // "new node"

  // if n isn't null, copy n and its subtrees recursively
  if (n != nullptr) {
    newN = new Node(n->data);
    newN->left = copyTree(n->left);
    newN->right = copyTree(n->right);
  }

  return newN;
}

// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v) { insertFromVector(v); }

// destructor
BSTMap::~BSTMap() { clear(); }

// END CONSTRUCTOR SECTION

// delete all nodes in tree
void BSTMap::clear() {
  delete root;
  root = nullptr;
}

// end constructor section

// true if no nodes in BST
bool BSTMap::empty() const { return root == nullptr; }

// Number of nodes in BST
int BSTMap::size() const { return sizeHelper(root); }

// private helper for size().
int BSTMap::sizeHelper(Node *n) const {
  if (n == nullptr) {
    return 0;
  }
  return 1 + sizeHelper(n->left) + sizeHelper(n->right);
}

// true if item is in BST
bool BSTMap::contains(const key_type &key) const {
  // binary tree search for key
  return containsHelper(key, root);
}

// private helper for contains
bool BSTMap::containsHelper(const key_type &key, Node *n) const {
  if (n == nullptr) {
    return false;
  }

  if (n->data.first == key) {
    return true;
  }
  // naive solution; just checks both subtrees blindly
  return containsHelper(key, n->right) || containsHelper(key, n->left);
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {
  // check if contains first

  if (contains(k)) {
    // find the node containing k and return n->data->second
    return getValue(k);
  }

  mapped_type &ref = insertNode(k);
  return ref;
}

// helper function for operator[]

BSTMap::mapped_type &BSTMap::insertNode(const key_type &k) {

  // // cout << "[InsertNode]" << " attempting to insert key " << k << endl;
  return insertNodeHelper(k, root);
}

// helper function for insertNode
// creates a new node with the given key, and returns the inserted value
// n is the previous node accessed, or the parent of the node to be inserted
BSTMap::mapped_type &BSTMap::insertNodeHelper(const key_type &k, Node *&n) {

  // if n is null (should only happen when root is null),
  // create new node with key k
  if (n == nullptr) {
    // // cout << "[InsertionSortHelper] Node n is null. Inserting key " << k <<
    // endl;
    Node *newNode = new Node(k);
    Node *&nNodeRef = newNode;
    n = nNodeRef;

    return n->data.second;
  }

  if (k > n->data.first) {

    return insertNodeHelper(k, n->right);
  }
  return insertNodeHelper(k, n->left);
  return n->data.second;
}

// get a value associated with a key
// Pre: the map MUST contain key k! Run contains(k) before using this function!
BSTMap::mapped_type &BSTMap::getValue(const key_type &k) const {
  return getValueHelper(k, root);
}

// helper function to help search for a value
BSTMap::mapped_type &BSTMap::getValueHelper(const key_type &k, Node *n) const {
  if (n->data.first == k) {
    return n->data.second;
  }

  if (k > n->data.first) {
    // go right
    return getValueHelper(k, n->right);
  }
  return getValueHelper(k, n->left);
}

// returns a vector of key-value pairs that partially match the key
// Main function used by autocomplete
// Might traverse both left and right subbranches of a node
// Example: getall("hel")
// Return: { (hello, 10), (help, 20)}
vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  getAllHelper(v, k, root);

  return v;
}

// recursively search through the BSTMap, pushing all value pairs
// whose keys contain the prefix k into vector v
void BSTMap::getAllHelper(vector<value_type> &v, const key_type &k,
                          Node *n) const {
  if (n == nullptr) {
    return;
  }
  key_type nKey = n->data.first;

  // find substring: if (s.find(prefix) == 0)
  // where s is a given node's key
  bool hasPre = nKey.find(k) == 0;

  if (hasPre) {
    // push node's data to v
    v.push_back(n->data);
    // traverse both subtrees
    getAllHelper(v, k, n->left);
    getAllHelper(v, k, n->right);
  } else {
    // find if pre > key or pre < key
    // traverse right or left subtree respectively
    if (k > nKey) {
      // go right
      getAllHelper(v, k, n->right);
    } else if (k < nKey) {
      // go left
      getAllHelper(v, k, n->left);
    }
  }
}

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const { return getHeight(root); }

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) {
  if (n == nullptr) {
    return 0;
  }

  return 1 + max(getHeight(n->left), getHeight(n->right));
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const key_type &k) const { return contains(k) ? 1 : 0; }

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const {
  inOrderHelper(visit, root);
}

// private helper for inorder
void BSTMap::inOrderHelper(void visit(const value_type &item), Node *n) const {
  if (n == nullptr) {
    return;
  }
  inOrderHelper(visit, n->left);
  visit(n->data);
  inOrderHelper(visit, n->right);
}

// preorder traversal: root-left-right
void BSTMap::preorder(void visit(const value_type &item)) const {
  preOrderHelper(visit, root);
}

// private helper for preorder
void BSTMap::preOrderHelper(void visit(const value_type &item), Node *n) const {
  if (n == nullptr) {
    return;
  }
  visit(n->data);
  preOrderHelper(visit, n->left);
  preOrderHelper(visit, n->right);
}

// postorder traversal: left-right-root
void BSTMap::postorder(void visit(const value_type &item)) const {
  postOrderHelper(visit, root);
}

// private helper for postorder
void BSTMap::postOrderHelper(void visit(const value_type &item),
                             Node *n) const {
  if (n == nullptr) {
    return;
  }

  postOrderHelper(visit, n->left);
  postOrderHelper(visit, n->right);
  visit(n->data);
}

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {
  // create vector
  nodeData.clear();
  buildVector(nodeData, root);
  //  rebuild tree
  //  deallocate memory
  clear();

  insertFromVector(nodeData);
}

void BSTMap::buildVector(vector<value_type> &v, Node *n) {

  if (n == nullptr) {
    return;
  }

  buildVector(v, n->left);
  v.push_back(n->data);
  buildVector(v, n->right);
}

void BSTMap::insertFromVector(vector<value_type> v) {
  // calculate mid, left and right
  int mid = (static_cast<int>(v.size()) / 2);
  int left = 0;
  int right = static_cast<int>(v.size()) - 1;
  vector<int> insertOrder;
  insertFromVectorHelper(insertOrder, left, mid, right);
  for (int i : insertOrder) {
    // // cout << i << ", ";
    key_type k = v[i].first;
    (*this)[k] = v[i].second;
  }
}

void BSTMap::insertFromVectorHelper(vector<int> &order, int left, int mid,
                                    int right) {
  // recursively push indices into order

  order.push_back(mid);

  int tempLeft;
  int tempMid;
  int tempRight;

  // seeing if can/should recurse left
  tempLeft = left;
  tempRight = mid - 1;
  tempMid = mid - (tempRight - tempLeft);

  if (tempLeft == tempRight) {
    tempMid = tempLeft;
  }
  if (tempLeft <= tempRight) {
    insertFromVectorHelper(order, tempLeft, tempMid, tempRight);
  }

  // seeing if can/should recurse right
  tempLeft = mid + 1;
  tempRight = right;
  tempMid = mid + (tempRight - tempLeft);

  if (tempLeft == tempRight) {
    tempMid = tempRight;
  }
  if (tempLeft <= tempRight) {
    insertFromVectorHelper(order, tempLeft, tempMid, tempRight);
  }
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const {
  return testEquality(root, other.root);
}

// recursively test equality of this BST and another (for the == operator)
bool BSTMap::testEquality(const Node *thisN, const Node *otherN) const {
  // base case: both given nodes are nullptr
  // (return true)
  if (thisN == nullptr && otherN == nullptr) {
    return true;
  }

  // base case: one node is nullptr and other isnt (XOR)
  // return false
  if ((thisN == nullptr) ^ (otherN == nullptr)) {
    return false;
  }

  // base case: two given nodes have different keys
  // (return false)
  if (thisN->data.first != otherN->data.first) {
    return false;
  }

  // base case: two given nodes have different values
  // return false
  if (thisN->data.second != otherN->data.second) {
    return false;
  }

  // recursively test subtrees
  return testEquality(thisN->left, otherN->left) &&
         testEquality(thisN->right, otherN->right);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const { return !(*this == other); }

string BSTMap::printVector(vector<value_type> v) {
  stringstream s;
  if (!v.empty()) {
    s << "[";
    s << "(" << v[0].first << ", " << v[0].second << ")";
    for (int i = 1; i < v.size(); i++) {
      s << ", (" << v[i].first << ", " << v[i].second << ")";
    }
    s << "]";
  } else {
    s << "[]";
  }

  return s.str();
}