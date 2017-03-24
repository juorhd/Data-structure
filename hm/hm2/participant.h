#ifndef __participant_h_
#define __participant_h_

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

class Participant{
public:
	const string& first_name() const { return fstname; }
    const string& last_name() const { return lstname; }
    const string& country_abbr() const { return countryabbr; }

    int gold_num() const { return gold__; }
	int silver_num() const { return silver__; }
	int bronze_num() const { return bronze__; }
	int heat_num() const { return heat__; }
	int semi_num() const { return semi__; }
	int final_num() const { return final__; }

    void set_first_name( string NAME ) { fstname=NAME; }
    void set_last_name( string NAME ) { lstname=NAME; }
    void initialize(){ heat__=semi__=final__=gold__=silver__=bronze__=0;}
    void clean_itself();

    void set_gold_num( int _num )  { gold__=_num; }
	void set_silver_num( int _num )  {  silver__=_num; }
	void set_bronze_num( int _num )  {  bronze__=_num; }
	void set_heat_num( int _num )  {  heat__=_num; }
	void set_semi_num( int _num )  {  semi__=_num; }
	void set_final_num( int _num )  {  final__=_num; }
	void set_country_abbr( string STR ) { countryabbr=STR; }

	void increase_gold_num( int _num ) { gold__ += _num ; }
	void increase_silver_num( int _num ) { silver__ += _num ; }
	void increase_bronze_num( int _num ) { bronze__ += _num ; }
	void increase_heat_num( int _num ) { heat__ += _num ; }
	void increase_semi_num( int _num ) {  semi__ += _num ; }
	void increase_final_num( int _num ) {  final__ += _num ; }

private:
  	int heat__, semi__, final__; 
	int gold__, silver__, bronze__; 
	string fstname, lstname;
	string countryabbr;
};

bool by_name (const Participant& P1, const Participant& P2);
bool by_country( const Participant& P1, const Participant& P2);
void clean_itself( vector<Participant> &P1 );
void printevents( ofstream &fout, vector<Participant> P1 ) ;
void printeventsmedals( ofstream &fout, vector<Participant> P1 ) ;


#endif