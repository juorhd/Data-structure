// ==================================================================================
// Implement all functions that you listed by prototype in deck.h
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// NOTE: These are standalone functions, not part of a class.
// ==================================================================================

#include <iostream>
#include <cassert>
#include "playing_card.h"
#include "node.h"
#include "deck.h"
using namespace std;

// ==================================================================================
Node* CopyDeck( Node* &old_head ){

	if ( old_head->after == NULL){
		Node* new_head = new Node( old_head->getCard() );
		new_head->after = NULL;
		return new_head;
	} else {
	Node* new_head = new Node( old_head->getCard() );
	new_head->after = CopyDeck( old_head->after );
	new_head->after->before = new_head;
	return new_head;
	}
}
int DeckSize( Node* &head ) {
	Node* tmp = head;
	if (tmp == NULL) return 0;
	int size = 1;
	while ( tmp->after!= NULL ){
		tmp = tmp->after;
		size++;
	}
	return size;
}

bool SamePrimaryOrder( Node* &head1, Node* &head2 ){
	Node* tmp1=head1;
	Node* tmp2=head2;
	if ( tmp1 == NULL && tmp2 == NULL ) return true;
	while ( tmp1->after != NULL) {
		if ( tmp1->getCard()!= tmp2->getCard() ) return false;
		tmp1 = tmp1->after; tmp2 = tmp2->after;
	}
	return true;
}
bool ReversePrimaryOrder( Node* &head1, Node* &head2 ){
	Node* tmp1=head1;
	Node* tmp2=head2;
	if ( tmp1 == NULL && tmp2 == NULL ) return true;
	while ( tmp2->after != NULL ) tmp2 = tmp2->after;
	while ( tmp1->after != NULL) {
		if ( tmp1->getCard()!= tmp2->getCard() ) return false;
		tmp1 = tmp1->after; tmp2 = tmp2->before;
	}
	return true;
}

void CutDeck( Node* &deck, Node* &top, Node* &bottom, string str ){
	if ( deck->after == NULL ){
		top = NULL; 
		bottom = deck;
		return;
	}
	top = deck;
	bottom = deck;
	int size = 1;
	while ( bottom->after != NULL ) {
		bottom = bottom->after; size++;
	}
	int l=1, r=size;
	while ( l<r-1 ){
		bottom = bottom->before;
		l++, r--;
	} 
	bottom->before->after = NULL;
	bottom->before = NULL;
}

Node* Shuffle( Node* &top, Node* &bottom, const string str ){
	if ( top == NULL ) return bottom;
	Node* tmp = top;
	Node* tmp1 = top;
	Node* tmp2 = bottom;
	while ( top->after != NULL && bottom->after != NULL ){
		tmp1 = tmp1->after;
		tmp2 = tmp2->after;
		top->after = bottom;
		bottom->before = top;
		bottom->after = tmp1;
		tmp1->before = bottom;
		top = tmp1;
		bottom = tmp2;
	}
	if ( top->after != NULL ){
		bottom->after = top->after;
		top->after->before = bottom;
	}
	top->after = bottom;
	bottom->before = top;
	return tmp;
}

void DeleteAllCards( Node* &deck){
	Node* tmp = deck;
	while ( deck->after != NULL){
		tmp = tmp->after;
		delete deck;
		deck = tmp;
	}
	delete deck;
}

void Deal( Node* &deck, Node** hand, int num, const string str, int cardnum ){
	Node* tmp1[num];
	for (int i=0; i<num; ++i ) {
		hand[i] = deck; 
		tmp1[i] = deck;
		hand[i]->before = NULL;
		deck = deck->after;
	}
	cardnum--;

	while ( cardnum > 0){
		for (int i=0; i<num; ++i ){
			tmp1[i]->after = deck;
			deck->before = tmp1[i];
			deck = deck->after;
			tmp1[i] = tmp1[i]->after;
		}
		cardnum--;
	}
	for (int i=0; i<num; ++i ) tmp1[i]->after = NULL;
	if ( deck != NULL ) deck->before = NULL;
	
}

Node* SortHand(Node* &top){
	Node* now = top;
	Node* tmp = top;
	Node* Max = top;
	now = now->after;
	while ( now != NULL ){
		if ( now->getCard() < Max->getCard() || now->getCard() == Max->getCard() ){
			now->sorted_next = Max;
			Max->sorted_prev = now;
			Max = now;
		} else {
			tmp = Max;
			while ( now->getCard() > tmp->getCard() && tmp->sorted_next != NULL )
				tmp = tmp->sorted_next;
			if ( now->getCard() > tmp->getCard() ){
				tmp->sorted_next = now;				
				now->sorted_prev = tmp;
			} else {
				now->sorted_prev = tmp->sorted_prev;
				tmp->sorted_prev->sorted_next = now;
				tmp->sorted_prev = now;
				now->sorted_next = tmp;
			}
		}
		now = now->after;
	}
	return Max;
}

void PrintDeckSorted(const std::string &description, Node* deck) {
  std::cout << description;
  Node *tmp = deck;
  while (tmp != NULL) {
    std::cout << " " << tmp->getCard().getString();
    tmp = tmp->sorted_next;
  }
  std::cout << std::endl;
}


