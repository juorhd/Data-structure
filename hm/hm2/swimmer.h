#ifndef __swimmer_h_
#define __swimmer_h_

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

class Swimmer{

public:
	const string& get_first_name() const { return first_name; }
    const string& get_last_name() const { return last_name; }
    const string& get_country() const { return country; }
    const string& get_country_abbr() const { return country_abbr; }
    const string& get_appendix() const { return appendix; }
    const string& get_final_time() const { return final_time; }
    const string& get_intermediate_time( int index ) const { return intermediate_timing[index]; }

    int get_gold() const { return gold; }
	int get_silver() const { return silver; }
	int get_bronze() const { return bronze; }
	int get_heat() const { return heat; }
	int get_semi() const { return semi; }
	int get_final() const { return final; }
	int get_final_size() const { return final_time.size(); }
	bool get_is_country() const { return is_country; }
	double get_time_double() const {return TimeString_to_Timefloat(final_time);}

	void increase_gold()  { gold++; }
	void increase_silver()  { silver++; }
	void increase_bronze()  { bronze++; }
	void increase_heat()  { heat++; }
	void increase_semi()  { semi++; }
	void increase_final()  { final++; }
	void set_appendix( string str ) { appendix = str; }
	void seperate_time( vector<string> &Time );
	void initialize_member() {	heat=semi=final=gold=silver=bronze=is_country=0; }

	void read( ifstream& fin, string TYPE, int num );
	void read_relay( ifstream& fin, string TYPE, int num );
	void read_relay_swimmer( ifstream& fin, Swimmer _swimmer);
	double TimeString_to_Timefloat ( string TIME ) const;
	string Timefloat_to_TimeString ( double TIME ) const;




private:
	int heat, semi, final; 
	int gold, silver, bronze; 
	bool is_country;

	string first_name, last_name, appendix;
	string country, country_abbr;
	string final_time;
	vector<string> intermediate_timing;

};
	bool by_speed( const Swimmer& S1, const Swimmer& S2 );

#endif