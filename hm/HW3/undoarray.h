#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
using namespace std;

template <typename T> class UndoArray {

public:
    // constructor 
	UndoArray( int size) { this->create(size); }
    UndoArray( UndoArray& Ua);

    //accessor
    unsigned int* counts() const { return counts_; }
    T** values() const { return values_; }

    //modifiers
    bool initialized( int n ) const  { return counts_[n] != 0; } 
    const T &get( int n ) const{ return values_[n][ counts_[n]-1 ]; }   
    int size() const { return size_; };
    void set( int n, T t );
    void undo( int n );
    void print() const;
    UndoArray& operator= (const UndoArray& Ua);
    void push_back(); 
    void pop_back();


    //destructor
    ~UndoArray() { this->delete_(); }

private:
    void create( int size );
    void delete_();

    unsigned int size_;
    unsigned int* counts_;
    T** values_;
};

template <class T> UndoArray<T>::UndoArray( UndoArray& Ua) {
    this->size_=Ua.size_;
    this->counts_ = new unsigned int[size_];
    this->values_ = new T*[size_];
    for ( int i=0; i<this->size_; ++i ) {
        this->counts_[i] = Ua.counts()[i];
        this->values_[i] = new T[Ua.counts()[i]];
        for (int j=0; j<this->counts_[i]; ++j){
            this->values_[i][j] = Ua.values()[i][j];
        }
    }
}

template <class T> UndoArray<T>& UndoArray<T>::operator= (const UndoArray& Ua){
    if (this == &Ua) return *this;
    this->delete_();
    this->size_=Ua.size_;
    this->counts_ = new unsigned int[size_];
    this->values_ = new T*[size_];
    for ( int i=0; i<this->size_; ++i ) {
        this->counts_[i] = Ua.counts()[i];
        this->values_[i] = new T[Ua.counts()[i]];
        for (int j=0; j<this->counts_[i]; ++j)
            this->values_[i][j] = Ua.values()[i][j];
    } return *this;
}

template <class T> void UndoArray<T>::push_back(){

    unsigned int* tmp_count = new unsigned int[++size_];
    for (int i=0; i<size_-1; ++i) tmp_count[i] = counts_[i];
    tmp_count[size_-1] = 0;
    delete [] counts_;
    counts_ = tmp_count;

    T** tmp_value = values_;
    values_ = new T*[size_];
    for (int i=0; i<size_; ++i){
        this->values_[i] = new T[counts_[i]];
        for (int j=0; j<counts_[i]; ++j)
            this->values_[i][j] = tmp_value[i][j];
    }
    for (int i=0; i<size_-1; ++i) delete [] tmp_value[i];
    delete [] tmp_value;
}

template <class T> void UndoArray<T>::pop_back(){
    assert( this->size_ != 0 );
    unsigned int* tmp_count = new unsigned int[--size_];
    for (int i=0; i<size_; ++i) tmp_count[i] = counts_[i];
    delete [] counts_;
    counts_ = tmp_count;

    T** tmp_value = values_;
    values_ = new T*[size_];
    for (int i=0; i<size_; ++i){
        this->values_[i] = new T[counts_[i]];
        for (int j=0; j<counts_[i]; ++j)
            this->values_[i][j] = tmp_value[i][j];
    }
    for (int i=0; i<size_+1; ++i) delete [] tmp_value[i];
    delete [] tmp_value;
}


template <class T> void UndoArray<T>::create( int size) {
        this->size_ = size;
        this->counts_ = new unsigned int[size_];
        for ( int i = 0; i < size_; ++i )  counts_[i] = 0;

        this->values_ = new T*[size_];
        for ( int i = 0; i < size_; ++i )  values_[i] = new T[0];
}
    
template <class T> void UndoArray<T>::delete_() {
        for ( int i = 0; i < size_; ++i )   delete [] values_[i];
        delete [] values_;
        delete [] counts_;
}

            
template <class T> void UndoArray<T>::set( int n, T t ) {
        T* tmp = new T[ counts_[n]+1 ];
        for ( int i = 0; i < counts_[n]; ++i )
            tmp[i] = values_[n][i];
        tmp[ counts_[n] ] = t;
        counts_[n]++;
        delete [] values_[n];
        values_[n] = tmp;
}
        
template <class T> void UndoArray<T>::undo( int n ) {
        assert( counts_[n] != 0 );
        T* tmp = new T[ counts_[n]-1 ];
        for ( int i = 0; i < counts_[n]-1; ++i )
            tmp[i] = values_[n][i];
        counts_[n]--;
        delete [] values_[n];
        values_[n] = tmp;
    }
    
template <class T> void UndoArray<T>::print() const{
        cout << "size_:    " << size_ << endl;
        cout << "counts_:";
        int MAX = 0;
        for ( int i = 0; i < size_; ++i )
            cout << "  " << counts_[i];
        cout << endl;
        cout << "values_:";
        for ( int i = 0; i < size_; ++i ) {
            if ( counts_[i] == 0 ) cout << "  /";
            else cout << "  .";
            if ( counts_[i] > MAX ) MAX = counts_[i];
        }
        cout << endl;
        for ( int i = 0; i < MAX; ++i ) {
            cout << "        ";
            for ( int j = 0; j < size_; ++j ) {
                if ( counts_[j] > i ) cout << "  " << values_[j][i];
                else cout << "   ";
            }
            cout << endl;
        }
    }

