#ifndef _BIDIRECTIONAL_H_
#define _BIDIRECTIONAL_H_

#include <iostream>
#include <cassert>
#include <string>
#include <vector> 
#include <utility>
#include <algorithm>
#include <cstdlib>
using namespace std;

// -------------------------------------------------------------------
// TREE NODE CLASS
template <class T1, class T2>
class Node {
public:
    Node() : left(NULL), right(NULL), parent(NULL), link(NULL) {}
    Node(const T1& init) : value(init), left(NULL), right(NULL), parent(NULL), link(NULL) {}
    //representatives
    T1 value;
    Node* left;
    Node* right;
    Node* parent; 
    Node<T2, T1>* link;
};

template <class T1, class T2> class bidirectional_map;

// -------------------------------------------------------------------
// TREE NODE ITERATOR CLASS

template <class T1, class T2>
class tree_iterator {
public:
	//default constructor
    tree_iterator() : ptr_(NULL), bimap_(NULL) {}
    tree_iterator(Node<T1, T2>* p) : ptr_(p) {}
    tree_iterator(const tree_iterator& old) : ptr_(old.ptr_), bimap_(old.bimap_) {}
    
    //operators
    tree_iterator& operator=(const tree_iterator& old) { ptr_ = old.ptr_; bimap_ = old.bimap_; return *this; } 
    // operator* gives constant access to the value at the pointer
    const pair<T1, T2> operator*() const {  return make_pair(ptr_->value, ptr_->link->value); }
    // comparions operators are straightforward
    bool operator== (const tree_iterator& rgt) { return ptr_ == rgt.ptr_; }
  	bool operator!= (const tree_iterator& rgt) { return ptr_ != rgt.ptr_; }
    
    // increment & decrement operators 
    tree_iterator<T1, T2> & operator++() {
        if (ptr_->right != NULL) { // find the leftmost child of the right node
            ptr_ = ptr_->right;
            while (ptr_->left != NULL) { ptr_ = ptr_->left; }
        } else { // go upwards along right branches...  stop after the first left
            while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { ptr_ = ptr_->parent; }
            ptr_ = ptr_->parent;
        }
        return *this;
    }
    tree_iterator<T1, T2> operator++(int) {
        tree_iterator<T1, T2> temp(*this);
        ++(*this);
        return temp;
    }
    tree_iterator<T1, T2> & operator--() {
        if ( ptr_ == NULL ) {
            ptr_ = bimap_->key_root;
            while ( ptr_->right ) { ptr_ = ptr_->right; }
        } else if ( ptr_->left != NULL ) {  
            // find the rightmost child of the left node
            ptr_ = ptr_->left;
            while ( ptr_->right != NULL ) { ptr_ = ptr_->right; }
        } else {
            // go upwards along left brances, stop after the first right
            while ( ptr_->parent != NULL && ptr_->parent->left == ptr_ ) 
            	{ ptr_ = ptr_->parent; }
            ptr_ = ptr_->parent;
        }
        return *this;
    }
    tree_iterator<T1, T2> operator--(int) {
        tree_iterator<T1, T2> temp(*this);
        --(*this);
        return temp;
    }
    
    void make_link(Node<T2, T1>* matched) { ptr_->link = matched; }
    Node<T1, T2> * ptr() const {return ptr_;}
    Node<T2, T1> * follow_link() { return ptr_->link; }
private:
    // representation
    Node<T1, T2>* ptr_;
    const bidirectional_map<T1, T2>* bimap_;
};

template <class T1, class T2> 
class bidirectional_map{
public:
	//constructor
	bidirectional_map() : key_root(NULL), value_root(NULL), size_(0) {}
	bidirectional_map(const bidirectional_map<T1, T2>& old) : size_(old.size_) {
		key_root = this->copy_tree(old.key_root, NULL);
		value_root = this->copy_tree(old.value_root, NULL);
		link_(old.key_root, key_root);
        link_(old.value_root, value_root); }
	//destructor
	~bidirectional_map() {
		this->destroy_tree(key_root);
		this->destroy_tree(value_root);
		key_root = NULL; value_root = NULL; size_ = 0; }

	int size() const { return size_; }

	typedef tree_iterator<T1, T2> key_iterator;
    friend class tree_iterator<T1, T2>;
    typedef tree_iterator<T2, T1> value_iterator;
    friend class tree_iterator<T2, T1>;

	//operators
	bidirectional_map& operator=(const bidirectional_map<T1, T2>& old) {
      	if (&old != this) {
        	this->destroy_tree(key_root);
			this->destroy_tree(value_root);
        	key_root = this->copy_tree(old.key_root, NULL);
			value_root = this->copy_tree(old.value_root, NULL);
            link_(old.key_root, key_root);
          	link_(old.value_root, value_root);
          	size_ = old.size_;
      	}
      	return *this;
  	}	

	bool operator==(const bidirectional_map<T1, T2>& old) const 
    { return (old.key_root == this->key_root && old.value_root == this->value_root); }
    bool operator!=(const bidirectional_map<T1, T2>& old) const 
    { return (old.key_root != this->key_root || old.value_root != this->value_root); }

    T2 operator[](T1 key_value)  {return find_linked_value(key_value, this->key_root);}
    T1 operator[](T2 value_value)  {return find_linked_value(value_value, this->value_root);}

    //modifier and accessor
	key_iterator find(const T1& key_value) { return find(key_value, key_root); }
	value_iterator find(const T2& value_value) { return find(value_value, value_root); }

	pair< key_iterator, bool > insert(const pair<T1, T2>& new_node) {
		pair< key_iterator, bool > key_pos = insert(new_node.first, key_root, NULL);
		pair< value_iterator, bool > value_pos = insert(new_node.second, value_root, NULL);
		if (key_pos.second && value_pos.second){
			//make the links and increase size
			key_pos.first.make_link(value_pos.first.ptr());
			value_pos.first.make_link(key_pos.first.ptr());
			this->size_++; 
		}
		return key_pos;
	}

	int erase(T1 const& key_value) { 
		//delete at both side
		if (find(key_value, key_root)==NULL) return 0;
		T2 value_value = (*find(key_value, key_root)).second; 
		int num_erase = erase(key_value, key_root); 
		erase(value_value, value_root);
		if (num_erase) this->size_--;
		return num_erase;
	}

	//ITERATORS
	//for key part
	key_iterator key_begin() const {
		if (!key_root) return key_iterator(NULL);
		Node<T1, T2>* p = key_root;
		while (p->left) p = p->left;
		return key_iterator(p);
	}
	key_iterator key_end() const{ return key_iterator(NULL); }

	//for value part
	value_iterator value_begin() const {
		if (!value_root) return value_iterator(NULL);
		Node<T2, T1>* p = value_root;
		while (p->left) p = p->left;
		return value_iterator(p);
	}
	value_iterator value_end() const{ return value_iterator(NULL); }

    // OUTPUT & PRINTING
    void print(ostream& ostr) const {
    	cout << string(49, '=') << endl;
    	
    	cout << "KEYS:\n";
        print_as_sideways_tree(ostr, key_root, 0);
        cout << string(49, '-') << endl;

        cout << "VALUES:\n";
        print_as_sideways_tree(ostr, value_root, 0);
        cout << string(49, '=') << endl;
    }

private:
	// REPRESENTATION
	Node<T1, T2>* key_root;
	Node<T2, T1>* value_root;
	int size_;

	// PRIVATE HELPER FUNCTIONS
	// link two node
	void link_(Node<T1, T2>* n1, Node<T1, T2>* n2) {
      	if (n1) {
        	T2 v = n1->link->value;
        	n2->link = (find(v, value_root).ptr());
        	link_(n1->left, n2->left);
        	link_(n1->right, n2->right);
      	}
    }

    void link_(Node<T2, T1>* n1, Node<T2, T1>* n2) {
     	if (n1) {
        	T1 k = n1->link->value;
        	n2->link = (find(k, key_root).ptr());
        	link_(n1->left, n2->left);
        	link_(n1->right, n2->right);
      	}
    }
    //copy the tree
    Node<T1, T2>*  copy_tree(Node<T1, T2>* key_old_root, Node<T1, T2>* the_parent) {
        if (key_old_root == NULL)
            return NULL;
        Node<T1, T2> *answer = new Node<T1, T2>();
        answer->value = key_old_root->value;
        answer->left = copy_tree(key_old_root->left,answer);
        answer->right = copy_tree(key_old_root->right,answer);
        answer->parent = the_parent;
        return answer;
    }

    Node<T2, T1>*  copy_tree(Node<T2, T1>* value_old_root, Node<T2, T1>* the_parent) {
        if (value_old_root == NULL)
            return NULL;
        Node<T2, T1> *answer = new Node<T2, T1>();
        answer->value = value_old_root->value;
        answer->left = copy_tree(value_old_root->left,answer);
        answer->right = copy_tree(value_old_root->right,answer);
        answer->parent = the_parent;
        return answer;
    }
    //destroy the tree
    void destroy_tree(Node<T1, T2>* p) {
        if (!p) return;
        destroy_tree(p->right);
        destroy_tree(p->left);
        delete p;
    }    
    void destroy_tree(Node<T2, T1>* p) {
        if (!p) return;
        destroy_tree(p->right);
        destroy_tree(p->left);
        delete p;
    }

	// insert for key
	pair<key_iterator,bool> insert(const T1& key_value, Node<T1, T2>*& p, Node<T1, T2>* the_parent) {
        if (!p) {
            p = new Node<T1, T2>(key_value);
            p->parent = the_parent;
            return pair<key_iterator,bool>(key_iterator(p), true);
        }
        else if (key_value < p->value) return insert(key_value, p->left, p);
        else if (key_value > p->value) return insert(key_value, p->right, p);
        else return pair<key_iterator,bool>(key_iterator(p), false);
    }

    // insert for value
    pair<value_iterator,bool> insert(const T2& value_value, Node<T2, T1>*& p, Node<T2, T1>* the_parent) {
        if (!p) {
            p = new Node<T2, T1>(value_value);
            p->parent = the_parent;
            return pair<value_iterator,bool>(value_iterator(p), true);
        }
        else if (value_value < p->value) return insert(value_value, p->left, p);
        else if (value_value > p->value) return insert(value_value, p->right, p);
        else return pair<value_iterator,bool>(value_iterator(p), false);
    }

    //find for key
    key_iterator find(const T1& key_value, Node<T1, T2>* p) {
        if (!p) return key_end();
        if (p->value > key_value) return find(key_value, p->left);
        else if (p->value < key_value) return find(key_value, p->right);
        else return key_iterator(p);
    }

    //find for value
    value_iterator find(const T2& value_value, Node<T2, T1>* p) {
        if (!p) return value_end();
        if (p->value > value_value) return find(value_value, p->left);
        else if (p->value < value_value) return find(value_value, p->right);
        else return value_iterator(p);
    }
    
    T2 find_linked_value(const T1& key_value, Node<T1, T2>* p) {
        if (p->value == key_value) return p->link->value;
        if (p->value > key_value) return find_linked_value(key_value, p->left);
        else return find_linked_value(key_value, p->right);
    }

    T1 find_linked_value(const T2& value_value, Node<T2, T1>* p) {
        if (p->value == value_value) return p->link->value;
        if (p->value > value_value) return find_linked_value(value_value, p->left);
        else return find_linked_value(value_value, p->right);
    }
    
    //erase for key
    int erase(T1 const& key_value, Node<T1, T2>* &p) {
        if (!p) return 0;
        
        // look left & right
        if (p->value < key_value)
            return erase(key_value, p->right);
        else if (p->value > key_value)
            return erase(key_value, p->left);
        
        // Found the node.  Let's delete it
        assert (p->value == key_value);
        if (!p->left && !p->right) { // 
            delete p;
            p=NULL;
        } else if (!p->left) { // no left child
            Node<T1, T2>* q = p;
            p=p->right;
            assert (p->parent == q);
            p->parent = q->parent;
            delete q;
        } else if (!p->right) { // no right child
            Node<T1, T2>* q = p;
            p=p->left;
            assert (p->parent == q);
            p->parent = q->parent;
            delete q;
        } else { // Find rightmost node in left subtree
            Node<T1, T2>* q = p->left;
            while (q->right) q = q->right;
            p->value = q->value;
            p->link = q->link;
            q->link->link = p;
            // recursively remove the value from the left subtree
            erase(q->value, p->left);
        }
        return 1;
    }

    //erase for value
    int erase(T2 const& key_value, Node<T2, T1>* &p) {
        if (!p) return 0;
        
        // look left & right
        if (p->value < key_value)
            return erase(key_value, p->right);
        else if (p->value > key_value)
            return erase(key_value, p->left);
        
        // Found the node.  Let's delete it
        assert (p->value == key_value);
        if (!p->left && !p->right) { // leaf
            delete p;
            p=NULL;
        } else if (!p->left) { // no left child
            Node<T2, T1>* q = p;
            p=p->right;
            assert (p->parent == q);
            p->parent = q->parent;
            delete q;
        } else if (!p->right) { // no right child
            Node<T2, T1>* q = p;
            p=p->left;
            assert (p->parent == q);
            p->parent = q->parent;

            delete q;
        } else { // Find rightmost node in left subtree
            Node<T2, T1>* q = p->left;
            while (q->right) q = q->right;
            p->value = q->value;
            p->link = q->link;
            q->link->link = p;
            // recursively remove the value from the left subtree
            erase(q->value, p->left);
        }
        return 1;
    }

    //print
    void print_as_sideways_tree(std::ostream& ostr, const Node<T1, T2>* p, int depth) const {
        if (p) {
            print_as_sideways_tree(ostr, p->right, depth+1);
            for (int i=0; i<depth; ++i) ostr << "    ";
            ostr << p->value << " [" << p->link->value << "]\n";
            print_as_sideways_tree(ostr, p->left, depth+1);
        }
    }
    void print_as_sideways_tree(std::ostream& ostr, const Node<T2, T1>* p, int depth) const {
        if (p) {
            print_as_sideways_tree(ostr, p->right, depth+1);
            for (int i=0; i<depth; ++i) ostr << "    ";
            ostr << p->value << " [" << p->link->value << "]\n";
            print_as_sideways_tree(ostr, p->left, depth+1);
        }
    }
};

#endif