/*
Driver code for testing your AVL Tree
This is NOT the test code for grading,
instead for you to get an idea of how to test the tree
 */
#include "AVLTree.h"
#include <iostream>
#include <ranges>
#include <string>
#include <vector>
using namespace std;

int main()
{
    AVLTree tree;
    bool insertResult;
    insertResult = tree.insert("F", 'F');
    insertResult = tree.insert("F", 'F'); // false, no duplicates allowed
    insertResult = tree.insert("K", 'K');
    insertResult = tree.insert("X", 'X'); // single rotate left
    cout << endl << endl;
    cout << tree << endl;

    insertResult = tree.insert("C", 'C');
    insertResult = tree.insert("A", 'A'); // single rotate right
    cout << endl << endl;
    cout << tree << endl;

    insertResult = tree.insert("D", 'D'); // double rotate right
    cout << endl << endl;
    cout << tree << endl;

    insertResult = tree.insert("R", 'R'); // double rotate left
    cout << endl << endl;
    cout << tree << endl;

    insertResult = tree.insert("V", 'V');
    insertResult = tree.insert("A", 'A'); // false, duplicate
    insertResult = tree.insert("Z", 'Z');
    insertResult = tree.insert("M", 'M');
    insertResult = tree.insert("D", 'D'); // false, duplicate
    cout << endl << endl;
    cout << tree << endl;

    // size and getHeight
    cout << "tree size: " << tree.size() << endl;          // 10
    cout << "tree height: " << tree.getHeight() << endl;   // 3
    cout << "tree balance: " << tree.getBalance() << endl; // 3
    cout << endl;

    /*
                {Z: 90}
        {X: 88}
                {V: 86}
{R: 82}
                        {M: 77}
                {K: 75}
        {F: 70}
                        {D: 68}
                {C: 67}
                        {A: 65}
*/

    // contains
    cout << "-- CONTAINS --" << endl;
    bool containsResult;
    containsResult = tree.contains("A"); // true
    cout << containsResult << endl;
    containsResult = tree.contains("N"); // false
    cout << containsResult << endl;

    // get
    optional<int> getResult;

    cout << endl << "-- GET --" << endl;
    getResult = tree.get("A"); // 65
    cout << "A: " << getResult.value() << endl;

    getResult = tree.get("C"); // 67
    cout << "C: " << getResult.value() << endl;

    getResult = tree.get("Q"); // getResult has no value
    cout << "Q: " << getResult.has_value() << endl; // print 0
    cout << endl;

    // findRange
    cout << endl << "-- FIND RANGE --" << endl;
    vector<size_t> rangeTest = tree.findRange("D", "W");
    // 70 68 82 75 77 86
    for (auto val : rangeTest) {
        cout << val << " ";
    }
    cout << endl << endl;

    // operator[]
    cout << endl << "-- OPERATOR[] --" << endl;
    tree["A"] = 108;
    cout << tree << endl;
    cout << endl;

    tree["E"] = 110;
    cout << tree << endl;
    cout << endl;

    /*
                        {Z: 90}
                {X: 88}
                        {V: 86}
        {R: 82}
                        {M: 77}
                {K: 75}
{F: 70}
                        {E: 110}
                {D: 68}
        {C: 67}
                {A: 108}
*/

    // 110
    cout << tree.get("E").value() << endl;

    // keys
    cout << endl << "-- KEYS --" << endl;

    vector<std::string> keysTest = tree.keys();
    // 70 68 82 75 77 86
    for (const std::string &val : keysTest) {
        cout << val << " ";
    }
    cout << endl << endl;

    // remove
    cout << endl << "-- REMOVE --" << endl;

    bool removeResult;
    removeResult = tree.remove("A"); // "A" is a leaf
    cout << endl << endl;
    cout << tree << endl;

    removeResult = tree.remove("C"); // "C" has one child, single rotate left
    cout << endl << endl;
    cout << tree << endl;

    removeResult = tree.remove("F"); // "F" has two children
    cout << endl << endl;
    cout << tree << endl;

    removeResult = tree.remove("V");
    removeResult = tree.remove("X");
    removeResult = tree.remove("Z"); // double rotate right
    cout << endl << endl;
    cout << tree << endl;

    /*
        {R: 82}
                {M: 77}
{K: 75}
                {E: 110}
        {D: 68}
*/

    // copy stuff
    cout << endl << "-- FINAL TREE --" << endl;
    cout << tree << endl;

    cout << endl << "-- ASSIGNMENT --" << endl;
    AVLTree assignTree = tree;
    cout << assignTree << endl;

    cout << endl << "-- COPY CONSTRUCTOR --" << endl;
    AVLTree copyTree(tree);
    cout << copyTree << endl;

    // test to see if copyTree just references the same thing
    copyTree.remove("E");
    cout << copyTree << endl;
    cout << tree << endl;

    return 0;
}
