#ifndef __event_h_
#define __event_h_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "swimmer.h"
#include "participant.h"
using namespace std;

class Event{

public:
	int get_num() const{ return num; }
	int swimmersize() const { return Swimmers.size(); }
	const string& get_type() const { return event_type; }
	const string& get_event_name() const { return event_name; }
    bool swimmer_iscountry( int _num ){ return Swimmers[_num].get_is_country(); }

	void clear_swimmer(){ Swimmers.clear(); }   //clean old swimmer data
	void set_num( int number ){ num=number; }
	void set_type ( string str ) { event_type=str; }
	void add_event_name ( string Name )  { event_name = Name; }
	void add_swimmer( Swimmer one_swimmer_ )  { Swimmers.push_back( one_swimmer_ );} //add swimmer
	void give_medal_to_relay_swimmer();  //associate winning country with its subordinate swimmers

	void print_events( ofstream& fout, int _num, string STR) const;
	void print_events_medals( ofstream& fout, int _num, string STR) const;
	void sort_swimmer_speed(){ sort(Swimmers.begin(), Swimmers.end(), by_speed); }
	void record_participants( Participant &P1, int _num);
	void add_stats( Participant &P1, int _num);
	void calc_medals() ;
private:
	string event_name;
	string event_type;
	vector<Swimmer> Swimmers;
	int num;

};
	int judge_num_50ms( string str_ ) ;    //return the number of intermediate time required to record
	bool Alphabetical ( const Event& E1, const Event& E2 ) ;

#endif