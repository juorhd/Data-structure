// =======================================================
//
// IMPORTANT NOTE: Do not modify this file
//     (except to uncomment the provided test cases 
//     and add your test cases where specified)
//
// =======================================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include "undoarray.h"


// helper testing function
void SimpleTests();
void StudentTests();
void BatchTest(const char* filename, int num);


int main(int argc, char* argv[]) {
  if (argc == 1) {
    SimpleTests();
    std::cout << "Simple tests completed." << std::endl;
    StudentTests();
    std::cout << "Student tests completed." << std::endl;
  } else {
    assert (argc == 3);
    BatchTest(argv[1],atoi(argv[2]));
    std::cout << "Batch test completed." << std::endl;
  }
}


void SimpleTests() {
  // create an undo array of chars of length 7

  // Note: The ua UndoArray object is stored on the stack. 
  //   The dynamically-allocated substructures of ua are stored 
  //   on the heap.

  UndoArray<char> ua(7);

  // confirm that an empty structure of the specified length was created
  assert (ua.size() == 7);
  for (unsigned int i = 0; i < ua.size(); i++) {
    assert (ua.initialized(i) == false);
  }
  std::cout << "constructor test completed" << std::endl;

  // some set & get operations 
  ua.set(2,'a');
  assert (ua.initialized(2) == true);
  assert (ua.get(2) == 'a');
  ua.set(2,'b');
  assert (ua.initialized(2) == true);
  assert (ua.get(2) == 'b');
  ua.set(4,'c');
  assert (ua.initialized(4) == true);
  assert (ua.get(4) == 'c');
  ua.set(6,'d');
  ua.set(1,'e');
  ua.set(6,'f');
  ua.set(6,'g');
  std::cout << "set & get tests completed" << std::endl;
  
  // =======================================================  
  // 
  //     UNCOMMENT THE SECTIONS BELOW AS YOU 
  //        COMPLETE THE IMPLEMENTATION
  //
  // =======================================================  

  
  // print the structure (to help in debugging)
  ua.print();
  std::cout << "print test completed" << std::endl;
  

  
  // some undo operations 
  ua.undo(2);
  assert (ua.get(2) == 'a');
  assert (ua.get(4) == 'c');
  ua.undo(4);
  assert (ua.initialized(4) == false);  
  assert (ua.initialized(2) == true);  
  assert (ua.get(2) == 'a');
  ua.print();
  std::cout << "undo tests completed" << std::endl;
  


  // example of the copy constructor
  UndoArray<char> another(ua);
  // the structures initially look the same
  assert (another.size() == ua.size());
  for (int i = 0; i < another.size(); i++) {
    assert (another.initialized(i) == ua.initialized(i));
    if (another.initialized(i))
      assert (another.get(i) == ua.get(i));
  }
  // but future edits show they are different!
  another.undo(6);
  assert (another.get(6) == 'f');
  assert (ua.get(6) == 'g');
  ua.set(4,'h');
  assert (another.initialized(4) != ua.initialized(4));
  std::cout << "copy constructor test completed" << std::endl;
   

  // example of the assignment operator
  ua = another;
  // again the structures look the same
  for (int i = 0; i < another.size(); i++) {
    assert (another.initialized(i) == ua.initialized(i));
    if (another.initialized(i))
      assert (another.get(i) == ua.get(i));
  }
  std::cout << "assignment operator test completed" << std::endl;


  // Note: The UndoArray destructor is implicitly called for the
  //   stack-allocated variables 'ua' and 'another' when we leave the
  //   function and it goes out of scope.
}


void StudentTests() {

  // =======================================================  
  // 
  // YOU SHOULD ADD YOUR OWN TEST CASES HERE
  //
  // be sure to rigorously test:
  //   * undo arrays that store types other than char
  //   * copy constructor
  //   * assignment operator
  //   * destructor
  //   * invalid requests (comment out for final submission)
  //
  // =======================================================
    
    UndoArray<int> ua(4);

    ua.set(1, 1); 
    ua.set(1, 2); 
    ua.set(2, 3); 
    
    ua.print();
    ua.undo(1); 
    assert (ua.get(1) == 1);
    assert (ua.initialized(1) == true);
    ua.undo(1); 
    assert (ua.initialized(1) == false);
    ua.print();
    std::cout << "[Student Test Case] undo tests completed" << std::endl;

    UndoArray<int> another(ua);
    assert (another.size() == ua.size());
    for (int i = 0; i < another.size(); i++) {
    assert (another.initialized(i) == ua.initialized(i));
    if (another.initialized(i))
      assert (another.get(i) == ua.get(i));
    }
    another.undo(2);  
    assert (another.initialized(2) != ua.initialized(2));
    std::cout << "[Student Test Case] copy constructor test completed" << std::endl;

    ua = another;
    for (int i = 0; i < another.size(); i++) {
    assert (another.initialized(i) == ua.initialized(i));
    if (another.initialized(i))
      assert (another.get(i) == ua.get(i));
    }
    std::cout << "[Student Test Case] assignment operator test completed" << std::endl;

    UndoArray<char> ua2(5);
    ua2.set(0,'a'); 
    ua2.set(1,'b'); 
    ua2.set(2,'c'); 
    ua2.set(3,'d'); 
    ua2.set(1,'e'); 
    ua2.set(2,'f'); 
    ua2.set(3,'g'); 
    ua2.set(4,'i'); 
    ua2.set(2,'j'); 
    ua2.set(3,'k'); 
    ua2.set(2,'l'); 
    ua2.print();

    ua2.push_back(); 
    assert( ua2.size() == 6 );
    ua2.print();
    ua2.set(5,'n');
    ua2.print();

    ua2.pop_back(); 
    assert( ua2.size() == 5 );
    ua2.print();
    ua2.pop_back(); 
    ua2.print();
    ua2.pop_back();     
    ua2.print();
    ua2.print();
    ua2.pop_back(); 
    ua2.print();
    ua2.pop_back(); 
    ua2.print();
    ua2.push_back(); 
    ua2.print();

    std::cout << "[Student Test Case] push_back and pop_back tests completed" << std::endl;
}

// Batch test will repeatedly load & process a file with UndoArray
// operations.  If the program's working memory does not grow when the
// program is run many, many times on a large test case, the data
// structure is probably free of memory leaks.
void BatchTest(const char* filename, int num) {
  assert (num > 0);

  while (num > 0) {
    num--;

    // open the file stream for reading
    std::ifstream istr(filename);
    assert (istr);

    // read the size of the array to allocate
    char c;
    int i;
    istr >> c >> i;
    assert (c == 'a');
    // here we dynamically (explicitly) allocate memory for the UndoArray object
    UndoArray<char> *ua = new UndoArray<char>(i);

    // read in and perform various operations on the array
    while (istr >> c) {
      if (c == 's') {
	istr >> i >> c;
	ua->set(i,c);	
      } else if (c == 'g') {
	istr >> i;
	if (ua->initialized(i)) {
	  char val = ua->get(i);	
          assert (val >= 'a' && val <= 'z');
	}
      } else {
	assert (c == 'u');
	istr >> i;
	if (ua->initialized(i)) {
	  ua->undo(i);	
	}
      }
    }

    // Because the UndoArray memory was allocated dynamically (using new)
    // we need to explicitly deallocate the memory (using delete)
    delete ua;
  }
}
