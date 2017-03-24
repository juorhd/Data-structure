#include "playing_card.h"
#include "node.h"
using namespace std;
// ==================================================================================
// prototypes for provided functions (implemented in main.cpp)
// ==================================================================================

bool SanityCheckPrimary(Node* top);
bool SanityCheckSorted(Node* first);
Node* CreateDeck(int numCards);
void DeckPushBackCard(Node* &deck, const std::string& suit, int num);
void PrintDeckPrimary(const std::string &description, Node* deck);


// ==================================================================================
//
// Write all the prototypes for the your functions here
// (they will be implemented in deck.cpp)
//
// NOTE: These are standalone functions, not part of a class.
//
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// ==================================================================================


void PrintDeckSorted(const std::string &description, Node* deck) ;
bool SamePrimaryOrder( Node* &head1, Node* &head2 );
bool ReversePrimaryOrder( Node* &head1, Node* &head2 );
Node* CopyDeck( Node* &old_head );
void DeleteAllCards( Node* &deck);

void CutDeck( Node* &deck, Node* &top, Node* &bottom, const string str );
Node* Shuffle( Node* &top, Node* &bottom, string str );
void Deal( Node* &deck, Node** hand, int num, const string str, int cardnum );
Node* SortHand(Node* &top);


int DeckSize( Node* &head ) ;
