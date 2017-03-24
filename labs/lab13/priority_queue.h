#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
    m_heap = values;
    for (int index=(m_heap.size()-1)/2; index>=0; --index){
      int l_child_index = index*2+1;

      while ( l_child_index < m_heap.size() ){
        int r_child_index = index*2+2;
        int smaller_child = l_child_index;
        if ( r_child_index < m_heap.size() ){
          if ( m_heap[r_child_index] < m_heap[l_child_index] )
            smaller_child = r_child_index;
        }
        if ( m_heap[smaller_child] < m_heap[index] ){
          swap( m_heap[smaller_child], m_heap[index] );
          index = smaller_child;
          l_child_index = index*2+1;
        }
        else break;
      }
    }
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry )
  {
    m_heap.push_back(entry);
    int index = m_heap.size()-1;
    while ( index != 0 ){
      int parent_index = (index-1)/2;
      if ( m_heap[index]< m_heap[parent_index] ){
        swap( m_heap[index], m_heap[parent_index] );
        index = parent_index;
      }
      else break;
    }
  }

  void pop() 
  {
    assert( !m_heap.empty() );
    if ( m_heap.size() == 1 )
      m_heap.pop_back();
    else {
      swap ( m_heap[0], m_heap[m_heap.size()-1] );
      m_heap.pop_back();
      int index = 0;
      int l_child_index = index*2+1;

      while ( l_child_index < m_heap.size() ){
        int r_child_index = index*2+2;
        int smaller_child = l_child_index;
        if ( r_child_index < m_heap.size() ){
          if ( m_heap[r_child_index] < m_heap[l_child_index] )
            smaller_child = r_child_index;
        }
        if ( m_heap[smaller_child] < m_heap[index] ){
          swap( m_heap[smaller_child], m_heap[index] );
          index = smaller_child;
          l_child_index = index*2+1;
        }
        else break;
      }
    }
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
    if ( heap.size() == 0 || heap.size() == 1 )
      return true;
    int index = 0;
    while ( index < heap.size() ){
      int l_child_index = index*2+1;
      int r_child_index = index*2+2;
      if ( l_child_index < heap.size() ){
        if ( heap[index] > heap[l_child_index] ) return false;
        if ( r_child_index < heap.size() ){
          if ( heap[index] > heap[r_child_index] ) return false;
        }
      }
      if ( index % 2 == 0 ) index = l_child_index;
      else index++;
    }
    return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v )
{
  if ( !v.size() || v.size()==1 ) return;
  for (int index=(v.size()-1)/2; index>=0; --index){
    int l_child_index = index*2+1;

    while ( l_child_index < v.size() ){
      int r_child_index = index*2+2;
      int greater_child = l_child_index;
      if ( r_child_index < v.size() ){
        if ( v[r_child_index] > v[l_child_index] )
          greater_child = r_child_index;
      }
      if ( v[greater_child] > v[index] ){
        swap( v[greater_child], v[index] );
        index = greater_child;
        l_child_index = index*2+1;
      }
      else break;
    }
  }
      for ( unsigned int i=0; i<v.size(); ++i )
      cout << i << ": " << v[i] << std::endl;

  int index = 0;
  int current_last = v.size()-1;
  while ( current_last != 0 ){
    swap (v[index], v[current_last]);  
    int l_child_index = index*2+1;
    while ( l_child_index < current_last ){
      int r_child_index = index*2+2;
      int greater_child = l_child_index;
      if ( r_child_index < current_last ){
        if ( v[r_child_index] > v[l_child_index] )
          greater_child = r_child_index;
      } 
      if ( v[greater_child] > v[index] ){
        swap( v[greater_child], v[index] );
        index = greater_child;
        l_child_index = index*2+1;
      }
      else break;
    }
    current_last--;
    index = 0;
  }
}

#endif
