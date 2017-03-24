#include <iostream>
#include <vector>
#include <list>
#include <string>
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

typedef vector< pair< string, pair< int, vector<Name> > > > COSTUME_SHOP_TYPE;
typedef vector< pair< Name, string > > PEOPLE_TYPE;

// prototypes for the helper functions
void addCostume( COSTUME_SHOP_TYPE &costume_shop);
void rentCostume( COSTUME_SHOP_TYPE &costume_shop, PEOPLE_TYPE& people);
void lookup( COSTUME_SHOP_TYPE& costume_shop);
void printPeople( PEOPLE_TYPE& people);

int main(int argc,char* argv[]) {

  COSTUME_SHOP_TYPE costume_shop;
  PEOPLE_TYPE people;
  char c;
  while (cin >> c) {
    if (c == 'a') { addCostume(costume_shop); } 
    else if (c == 'r') { rentCostume(costume_shop,people);  } 
    else if (c == 'l') { lookup(costume_shop); } 
    else if (c == 'p') {  printPeople(people); } 
    else { cerr << "error unknown char " << c << endl; exit(0); }
  }
  return 0;
}

void addCostume( COSTUME_SHOP_TYPE& costume_shop) {
  string costume_name;
  int num;
  cin >> costume_name >> num;

  bool find = false;
  for ( int i=0; i<costume_shop.size(); ++i ){
  	if (costume_shop[i].first == costume_name){
  		find = true;
  		costume_shop[i].second.first += num;
  	}
  }
  if ( !find ){
  	vector<Name> NAME;
  	costume_shop.push_back ( make_pair( costume_name, make_pair(num, NAME) ) );
  }

  cout << "Added " << num << ' ' << costume_name << " costume" << (num>1 ? "s.\n" : ".\n" );
}


void rentCostume( COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people) {
  string first_name;  
  string last_name;
  string costume_name;
  cin >> first_name >> last_name >> costume_name;

  int index = -1;
  for ( int i=0; i<costume_shop.size(); ++i )
  	if (costume_shop[i].first == costume_name) {
  	 index = i;
  	 break;
  }
  if ( index == -1 ){
  	cout << "The shop doesn't carry " << costume_name << " costumes.\n";
  	bool find = false;
  	for ( int i=0; i<people.size(); ++i)
  		if ( people[i].first.getfirstname() == first_name && people[i].first.getlastname() == last_name )
  			{ find = true; break; }
  	if ( !find )  people.push_back( make_pair( Name(first_name, last_name), "") );
  } else {
  	if ( !costume_shop[index].second.first ){
  		cout<< "No " << costume_name <<  " costumes available.\n";
		bool find = false;
  		for ( int i=0; i<people.size(); ++i)
  			if ( people[i].first.getfirstname() == first_name && people[i].first.getlastname() == last_name )
  				{ find = true; break; }
  		if ( !find )  people.push_back( make_pair( Name(first_name, last_name), "") );
  	} else {
  		int pos = -1;
  		for ( int i=0; i<people.size(); ++i)
  			if ( people[i].first.getfirstname() == first_name && people[i].first.getlastname() == last_name )
  				{ pos = i; break; }
  		if ( pos == -1 ){
  			costume_shop[index].second.first--;
  			costume_shop[index].second.second.push_back( Name(first_name, last_name) );
  			people.push_back( make_pair( Name(first_name, last_name), costume_name) );
  			cout << first_name << ' ' << last_name << " rents a " << costume_name << " costume.\n";
  		} else {
  			string str = people[pos].second;
  			if ( !str.size() ){
  				costume_shop[index].second.first--;
  				costume_shop[index].second.second.push_back( Name(first_name, last_name) );
				people[pos].second = costume_name;
  				cout << first_name << ' ' << last_name << " rents a " << costume_name << " costume.\n";
  			} else {
  				if ( str == costume_name ) 
  					cout << first_name << ' ' << last_name << " already has a " << str << " costume.\n";
  				else {
  					for ( int j=0; j<costume_shop.size(); ++j )
  						if ( costume_shop[j].first == str ){
  							costume_shop[j].second.first++;
  							for ( vector<Name>::iterator itr = costume_shop[j].second.second.begin(); itr != costume_shop[j].second.second.end(); ++itr)
  					  			if ( itr->getfirstname() == first_name && itr->getlastname() == last_name )
  						 			{ costume_shop[j].second.second.erase(itr); break; }
  							break;
  						}
  					costume_shop[index].second.first--;
  					costume_shop[index].second.second.push_back( Name(first_name, last_name) );
  					people[pos].second = costume_name; 
   				  	cout << first_name << ' ' << last_name << " returns a " << str << " costume before renting a " 
  					     << costume_name << " costume.\n"; 
  				}
  			}
  		}
	}
  }
}


void lookup( COSTUME_SHOP_TYPE& costume_shop) {
  string costume_name;
  cin >> costume_name;

  int index = -1;
  for ( int i=0; i<costume_shop.size(); ++i )
    if (costume_shop[i].first == costume_name) {
     index = i;
     break;
  }
  if ( index == -1 ) cout << "The shop doesn't carry " << costume_name << " costumes.\n";
  else {
      cout << "Shop info for " << costume_name << " costumes:\n";
      if ( costume_shop[index].second.first != 0 ){
        int costum_num = costume_shop[index].second.first;
        cout << "  " << costum_num << " cop" << ( costum_num>1 ? "ies" : "y" ) << " available\n";
      }
      if ( costume_shop[index].second.second.size() != 0 ){
        int people_num = costume_shop[index].second.second.size();
        cout << "  " << people_num <<  " cop" << ( people_num>1 ? "ies" : "y" ) << " rented by:\n";
        for (int i=0; i<people_num; ++i)
          cout << "    " << costume_shop[index].second.second[i].getfirstname() << ' '
             << costume_shop[index].second.second[i].getlastname() << endl;
      }
  }
}

bool Alphabetically( const pair< Name, string > &P1, const pair< Name, string > &P2){
	if ( P1.first.getlastname() == P2.first.getlastname() )
		return P1.first.getfirstname() < P2.first.getfirstname();
	return P1.first.getlastname() < P2.first.getlastname();
}

void printPeople( PEOPLE_TYPE& people) {
	sort(people.begin(), people.end(), Alphabetically);
	int people_num = people.size();
	cout << "Costume info for the " << people_num << " party attendee" << ( people_num>1 ? "s:\n" : ":\n" ); 
	for ( int i=0; i<people.size(); ++i ){
		cout << "  " << people[i].first.getfirstname() << ' ' << people[i].first.getlastname();
		if ( !people[i].second.size() ) 
			cout << " does not have a costume.\n";
		else cout << " is wearing a " << people[i].second << " costume.\n";
	} 
}