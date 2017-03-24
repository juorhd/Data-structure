#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class Name {
public:
	Name(string FN, string LN): first_name(FN), last_name(LN) {}
	const string& getlastname() const{ return last_name; }
	const string& getfirstname() const{ return first_name; }
private:
	string first_name;	
	string last_name;
};

typedef map< string, pair< int, vector<Name> > > COSTUME_SHOP_TYPE;
typedef map< Name, string > PEOPLE_TYPE;
typedef vector< pair< string, pair< int, vector<Name> > > > COSTUME_SHOP_TYPE2;
typedef vector< pair< Name, string > > PEOPLE_TYPE2;

bool operator< (const Name& left, const Name& right) {
    return left.getlastname() < right.getlastname() ||
           (left.getlastname() == right.getlastname() && left.getfirstname() < right.getfirstname());
}

// prototypes for the helper functions
void addCostume( COSTUME_SHOP_TYPE &costume_shop);
void rentCostume( COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people);
void lookup( COSTUME_SHOP_TYPE& costume_shop);
void printPeople( PEOPLE_TYPE& people);

// prototypes for the helper functions in none-map version
void addCostume_nonemap( COSTUME_SHOP_TYPE2 &costume_shop2);
void rentCostume_nonemap( COSTUME_SHOP_TYPE2 &costume_shop2, PEOPLE_TYPE2& people2);
void lookup_nonemap( COSTUME_SHOP_TYPE2& costume_shop2);
void printPeople_nonemap( PEOPLE_TYPE2& people2);


int main(int argc,char* argv[]) {

  int none_map = false;
  if (argc == 2) none_map = true;      //extra credit for none-map
  COSTUME_SHOP_TYPE costume_shop;
  PEOPLE_TYPE people;

  COSTUME_SHOP_TYPE2 costume_shop2;
  PEOPLE_TYPE2 people2;
  char c;
  while (cin >> c) {
    if (!none_map) {
      if (c == 'a') { addCostume(costume_shop); } 
      else if (c == 'r') { rentCostume(costume_shop,people);  } 
      else if (c == 'l') { lookup(costume_shop); } 
      else if (c == 'p') {  printPeople(people); } 
      else { cerr << "error unknown char " << c << endl; exit(0); }
    }
    else { //extra credit for none-map
      if (c == 'a') { addCostume_nonemap(costume_shop2); } 
      else if (c == 'r') { rentCostume_nonemap(costume_shop2,people2);  } 
      else if (c == 'l') { lookup_nonemap(costume_shop2); } 
      else if (c == 'p') {  printPeople_nonemap(people2); } 
      else { cerr << "error unknown char " << c << endl; exit(0); }
    }
  }
  return 0;
}


void addCostume( COSTUME_SHOP_TYPE& costume_shop) {
  string costume_name;
  int num;
  cin >> costume_name >> num;

  if ( costume_shop.find(costume_name) == costume_shop.end() ){ //if not find just insert
  	vector<Name> NAME;
  	costume_shop.insert( make_pair( costume_name, make_pair(num, NAME) ) );
  } else 
  		costume_shop[costume_name].first+= num; //else just add number

  cout << "Added " << num << ' ' << costume_name << " costume" << (num>1 ? "s.\n" : ".\n" );
}


void rentCostume( COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people) {
  string first_name;  
  string last_name;
  string costume_name;
  cin >> first_name >> last_name >> costume_name;

  //if shop never import just cout doesn't carry that type costume
  if ( costume_shop.find(costume_name) == costume_shop.end() ){  
    cout << "The shop doesn't carry " << costume_name << " costumes.\n";
    if ( people.find( Name(first_name, last_name) ) == people.end() )
      people.insert( make_pair( Name(first_name, last_name), "") );
  } else {
    //if all the costume is rented by others, just cout no available 
    if ( !costume_shop[costume_name].first ){
      cout<< "No " << costume_name <<  " costumes available.\n";
      if ( people.find( Name(first_name, last_name) ) == people.end() )
        people.insert( make_pair( Name(first_name, last_name), "") );
    } else {
      // if the people is find with or without costume
      if ( people.find( Name(first_name, last_name) ) != people.end() ){
        PEOPLE_TYPE::iterator itr = people.find( Name(first_name, last_name) );
        string str = itr->second;
          //without costume
          if ( !str.size() ){
              costume_shop[costume_name].first--;
              costume_shop[costume_name].second.push_back( Name(first_name, last_name) );
              itr->second = costume_name;
              cout << first_name << ' ' << last_name << " rents a " << costume_name << " costume.\n";
          } else {
              //with the same costume
              if ( str == costume_name )
            cout << first_name << ' ' << last_name << " already has a " << str << " costume.\n";
          else {
              //with different costume
              costume_shop[str].first++;  //add returned one
              //delete name from old list
              for ( vector<Name>::iterator i = costume_shop[str].second.begin(); i != costume_shop[str].second.end(); ++i)
                if ( i->getfirstname() == first_name && i->getlastname() == last_name )
                { costume_shop[str].second.erase(i); break; }
              //delete borrowed one
              costume_shop[costume_name].first--;
              costume_shop[costume_name].second.push_back( Name(first_name, last_name) );

              itr->second = costume_name;
              cout << first_name << ' ' << last_name << " returns a " << str << " costume before renting a " 
                 << costume_name << " costume.\n"; 
            }
          }
          //without costume
      } else {
        costume_shop[costume_name].first--;
        costume_shop[costume_name].second.push_back( Name(first_name, last_name) );
        people.insert( make_pair( Name(first_name, last_name), costume_name) );
        cout << first_name << ' ' << last_name << " rents a " << costume_name << " costume.\n";
      }
    }
  }
}


void lookup( COSTUME_SHOP_TYPE& costume_shop) {
  string costume_name;
  cin >> costume_name;

  //if shop never import just cout doesn't carry that type costume
  if ( costume_shop.find(costume_name) == costume_shop.end() )
    cout << "The shop doesn't carry " << costume_name << " costumes.\n";
  else {
      cout << "Shop info for " << costume_name << " costumes:\n";
      //cout if the map shop has that costume
      if ( costume_shop[costume_name].first != 0 ){
        int costum_num = costume_shop[costume_name].first;
        cout << "  " << costum_num << " cop" << ( costum_num>1 ? "ies" : "y" ) << " available\n";
      }
      //cout the people who rent costume from the shop
      if ( costume_shop[costume_name].second.size() != 0 ){
        int people_num = costume_shop[costume_name].second.size();
        cout << "  " << people_num <<  " cop" << ( people_num>1 ? "ies" : "y" ) << " rented by:\n";
        for (int i=0; i<people_num; ++i)
          cout << "    " << costume_shop[costume_name].second[i].getfirstname() << ' '
             << costume_shop[costume_name].second[i].getlastname() << endl;
      }
  }
}


//print function
void printPeople( PEOPLE_TYPE& people) {
	int people_num = people.size();
	cout << "Costume info for the " << people_num << " party attendee" << ( people_num>1 ? "s:\n" : ":\n" ); 
	for ( PEOPLE_TYPE::const_iterator itr = people.begin(); itr != people.end(); ++itr ){
		cout << "  " << itr->first.getfirstname() << ' ' << itr->first.getlastname();
		if ( !itr->second.size() )
			cout << " does not have a costume.\n";
		else cout << " is wearing a " << itr->second << " costume.\n";
	} 
}


// below is the extra credit part.
void addCostume_nonemap( COSTUME_SHOP_TYPE2& costume_shop2) {
  string costume_name;
  int num;
  cin >> costume_name >> num;

  bool find = false;
  for ( int i=0; i<costume_shop2.size(); ++i ){
    if (costume_shop2[i].first == costume_name){ //if not find just insert
      find = true;
      costume_shop2[i].second.first += num;
    }
  }
  if ( !find ){             //else just insert
    vector<Name> NAME;
    costume_shop2.push_back ( make_pair( costume_name, make_pair(num, NAME) ) );
  }

  cout << "Added " << num << ' ' << costume_name << " costume" << (num>1 ? "s.\n" : ".\n" );
}

void rentCostume_nonemap( COSTUME_SHOP_TYPE2& costume_shop2, PEOPLE_TYPE2& people2) {
  string first_name;  
  string last_name;
  string costume_name;
  cin >> first_name >> last_name >> costume_name;

  int index = -1;
  for ( int i=0; i<costume_shop2.size(); ++i )
    if (costume_shop2[i].first == costume_name) {
     index = i;
     break;
  }

  //if shop never import just cout doesn't carry that type costume
  if ( index == -1 ){
    cout << "The shop doesn't carry " << costume_name << " costumes.\n";
    bool find = false;
    for ( int i=0; i<people2.size(); ++i)
      if ( people2[i].first.getfirstname() == first_name && people2[i].first.getlastname() == last_name )
        { find = true; break; }
    if ( !find )  people2.push_back( make_pair( Name(first_name, last_name), "") );
  } else {
    //if all the costume is rented by others, just cout no available 
    if ( !costume_shop2[index].second.first ){
      cout<< "No " << costume_name <<  " costumes available.\n";
    bool find = false;
      for ( int i=0; i<people2.size(); ++i)
        if ( people2[i].first.getfirstname() == first_name && people2[i].first.getlastname() == last_name )
          { find = true; break; }
      if ( !find )  people2.push_back( make_pair( Name(first_name, last_name), "") );
    } else {
      // if the people is find with or without costume
      int pos = -1;
      for ( int i=0; i<people2.size(); ++i)
        if ( people2[i].first.getfirstname() == first_name && people2[i].first.getlastname() == last_name )
          { pos = i; break; }
      if ( pos == -1 ){           //without costume
        costume_shop2[index].second.first--;
        costume_shop2[index].second.second.push_back( Name(first_name, last_name) );
        people2.push_back( make_pair( Name(first_name, last_name), costume_name) );
        cout << first_name << ' ' << last_name << " rents a " << costume_name << " costume.\n";
      } else {
        string str = people2[pos].second;
        if ( !str.size() ){
          costume_shop2[index].second.first--;
          costume_shop2[index].second.second.push_back( Name(first_name, last_name) );
        people2[pos].second = costume_name;
          cout << first_name << ' ' << last_name << " rents a " << costume_name << " costume.\n";
        } else {
          if ( str == costume_name )                //with the same costume
            cout << first_name << ' ' << last_name << " already has a " << str << " costume.\n";
          else {               //with different costume
            for ( int j=0; j<costume_shop2.size(); ++j )
              if ( costume_shop2[j].first == str ){
                costume_shop2[j].second.first++; //add returned one
                //delete name from old list
                for ( vector<Name>::iterator itr = costume_shop2[j].second.second.begin(); itr != costume_shop2[j].second.second.end(); ++itr)
                    if ( itr->getfirstname() == first_name && itr->getlastname() == last_name )
                    { costume_shop2[j].second.second.erase(itr); break; }
                break;
              }
            //delete borrowed one
            costume_shop2[index].second.first--;
            costume_shop2[index].second.second.push_back( Name(first_name, last_name) );
            people2[pos].second = costume_name; 
              cout << first_name << ' ' << last_name << " returns a " << str << " costume before renting a " 
                 << costume_name << " costume.\n"; 
          }
        }
      }
  }
  }
}


void lookup_nonemap( COSTUME_SHOP_TYPE2& costume_shop2) {
  string costume_name;
  cin >> costume_name;

  int index = -1;
  for ( int i=0; i<costume_shop2.size(); ++i )
    if (costume_shop2[i].first == costume_name) {
     index = i;
     break;
  }
  if ( index == -1 ) cout << "The shop doesn't carry " << costume_name << " costumes.\n";
  else {
      cout << "Shop info for " << costume_name << " costumes:\n";
      if ( costume_shop2[index].second.first != 0 ){
        int costum_num = costume_shop2[index].second.first;
        cout << "  " << costum_num << " cop" << ( costum_num>1 ? "ies" : "y" ) << " available\n";
      }
      if ( costume_shop2[index].second.second.size() != 0 ){
        int people2_num = costume_shop2[index].second.second.size();
        cout << "  " << people2_num <<  " cop" << ( people2_num>1 ? "ies" : "y" ) << " rented by:\n";
        for (int i=0; i<people2_num; ++i)
          cout << "    " << costume_shop2[index].second.second[i].getfirstname() << ' '
             << costume_shop2[index].second.second[i].getlastname() << endl;
      }
  }
}

bool Alphabetically( const pair< Name, string > &P1, const pair< Name, string > &P2){
  if ( P1.first.getlastname() == P2.first.getlastname() )
    return P1.first.getfirstname() < P2.first.getfirstname();
  return P1.first.getlastname() < P2.first.getlastname();
}

void printPeople_nonemap( PEOPLE_TYPE2& people2) {
  sort(people2.begin(), people2.end(), Alphabetically);
  int people2_num = people2.size();
  cout << "Costume info for the " << people2_num << " party attendee" << ( people2_num>1 ? "s:\n" : ":\n" ); 
  for ( int i=0; i<people2.size(); ++i ){
    cout << "  " << people2[i].first.getfirstname() << ' ' << people2[i].first.getlastname();
    if ( !people2[i].second.size() ) 
      cout << " does not have a costume.\n";
    else cout << " is wearing a " << people2[i].second << " costume.\n";
  } 
}
