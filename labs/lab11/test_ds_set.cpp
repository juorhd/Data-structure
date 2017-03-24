#include <iostream>
#include <string>
#include <utility>
#include <cassert>

#include "ds_set.h"


void rec( int cur, int step, ds_set<int>& set ) {
    if (step < 1) return;
    set.insert(cur+step);
    set.insert(cur-step);
    rec( cur+step, step/2.0, set );
    rec( cur-step, step/2.0, set );
}

void rec( int begin, ds_set<int>& set ) {
    set.insert(begin);
    rec( begin, begin/2.0, set );
}



int main() {
    
    ds_set<std::string> set1;
    set1.insert("hello");
    set1.insert("good-bye");
    set1.insert("friend");
    set1.insert("abc");
    set1.insert("puppy");
    set1.insert("zebra");
    set1.insert("daddy");
    set1.insert("puppy");  // should recognize that this is a duplicate!
    
    assert(set1.sanity_check());
    assert (set1.size() == 7);
    
    ds_set<std::string>::iterator p = set1.begin();
    assert(p != set1.end() && *p == std::string("abc"));
    
    p = set1.find( "foo" );
    assert (p == set1.end());
    
    p = set1.find("puppy");
    assert (p != set1.end());
    assert (*p == "puppy");
    
    std::cout << "Here is the tree, printed sideways.\n"
    << "The indentation is proportional to the depth of the node\n"
    << "so that the value stored at the root is the only value printed\n"
    << "without indentation.  Also, for each node, the right subtree\n"
    << "can be found above where the node is printed and indented\n"
    << "relative to it\n";
    set1.print_as_sideways_tree( std::cout );
    std::cout << std::endl;
    
    
    // copy the set
    ds_set<std::string> set2( set1 );
    assert(set1.sanity_check());
    assert(set2.sanity_check());
    assert(set1.size() == set2.size());
    
    
    //  Now add stuff to set2
    set2.insert( std::string("a") );
    set2.insert( std::string("b") );
    std::cout << "After inserting stuff:\n";
    set2.print_as_sideways_tree( std::cout );
    std::cout << std::endl;
    assert(set1.sanity_check());
    assert(set2.sanity_check());
    assert(set1.size() == set2.size() - 2);
    
    
    //  Now erase stuff from set2
    set2.erase("hello");
    set2.erase("a");
    set2.erase("hello"); // should recognize that it's not there anymore!
    set2.erase("abc");
    set2.erase("friend");
    std::cout << "After erasing stuff:\n";
    set2.print_as_sideways_tree( std::cout );
    std::cout << std::endl;
    assert(set1.sanity_check());
    assert(set2.sanity_check());
    assert(set1.size() == set2.size() + 2);
    
    
    // Test the iterators!
    ds_set<int> it_test;
    rec( 8, it_test );
    it_test.print_as_sideways_tree( std::cout );
    ds_set<int>::iterator it = it_test.begin();
    std::cout << "Test operator ++: ";
    for ( ; it != it_test.end(); it++ )
        std::cout << (*it) << "  ";
    std::cout << "\nTest operator --: ";
    it = it_test.end();
    while ( it != it_test.begin() )
        std::cout << (*--it) << "  ";
    
    // Create some unbalanced trees
    ds_set<int> it_test_set[5];
    for ( int i = 0; i < 5; i++ ) {
        for ( int j = 0; j < i+3; j++ ) {
            int k = j+1;
            while ( k < 21-i ) {
                it_test_set[i].insert(k);
                k = k+i+3;
            }
        }
    }
    
    // Test the iterators on those trees
    for ( int i = 0; i < 5; i++ ) {
        std::cout << "\n\nUnbalanced Tree " << i << ":" << std::endl;
        it_test_set[i].print_as_sideways_tree( std::cout );
        it = it_test_set[i].begin();
        std::cout << "\nTest operator ++: ";
        for ( ; it != it_test_set[i].end(); it++ )
            std::cout << (*it) << "  ";
        std::cout << "\nTest operator --: ";
        it = it_test_set[i].end();
        while ( it != it_test_set[i].begin() )
            std::cout << (*--it) << "  ";
    }
    std::cout << std::endl;
    
    
    // Test accumulate
    std::cout << "\nTest accumulate version 1:" << std::endl;
    std::cout << "Accumulation of 1-15: ";
    std::cout << it_test.accumulate(0) << std::endl;
    for ( int i = 0; i < 5; i++ )
        std::cout << "Accumulation of 1-" << 20-i << ": "
        << it_test_set[i].accumulate(0) << std::endl;
    std::cout << "Accumulation of set1: " << set1.accumulate("") << std::endl;
    std::cout << "Accumulation of set2: " << set2.accumulate("") << std::endl;
    
    
    std::cout << "\nTest accumulate version 2:" << std::endl;
    std::cout << "Accumulation of 1-15: ";
    std::cout << it_test.accumulate_(0) << std::endl;
    for ( int i = 0; i < 5; i++ )
        std::cout << "Accumulation of 1-" << 20-i << ": "
        << it_test_set[i].accumulate_(0) << std::endl;
    std::cout << "Accumulation of set1: " << set1.accumulate_("") << std::endl;
    std::cout << "Accumulation of set2: " << set2.accumulate_("") << std::endl;
    
 
    return 0;
}