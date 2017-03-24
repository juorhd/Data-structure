#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "event.h"
#include "participant.h"
using namespace std;

int main ( int argc, char* argv[] ){
	if (argc != 4 && argc != 5){
		cerr << "invalid command line number";
		exit(1);
	}
    //open file and check
    ifstream fin(argv[1]);
    if( !fin.good() ){
        cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }
    //creat file to write
    ofstream fout(argv[2]);
    if( !fout.good() ){
        cerr << "Can't open " << argv[2] << " to read.\n";
        exit(1);
    }

	string event, type;
	string gender, match_length, match_type, relay_or_medley;
	vector<Event> events;
	Event one_event;
	Swimmer one_swimmer;

	fin >> event;
    while ( event == "EVENT" ){
    	one_event.clear_swimmer();
    	fin >> gender >> match_length >> match_type;  
    	int num_of_50ms=judge_num_50ms(match_length); 
		one_event.set_num( num_of_50ms );
    	if ( match_length == "4x100m" || match_length == "4x200m" ){ // judge if it's relay or not
    		fin >> relay_or_medley;
    		one_event.set_type("Relay");
       		one_event.add_event_name(gender+' '+match_length+' '+match_type+' '+relay_or_medley);
			fin >> type;

       		while ( type == "HEAT" || type == "SEMI"|| type == "FINAL")	{ //read file and judge type
       			if(fin.eof()) break;
    		    one_swimmer.read_relay( fin, type, num_of_50ms );  //put swimmer info into swimmer profile
    		    Swimmer relay_swimmer; 
    		    one_event.add_swimmer(one_swimmer);   //put swimmer into event
    		    for (int i=1; i<=4; ++i){
    		    	relay_swimmer.read_relay_swimmer(fin, one_swimmer);
    		    	one_event.add_swimmer(relay_swimmer);
    		    }
   				fin >> type; 
       		}	
    	}
       	else {
       		if ( match_type == "Individual" ){ 
       			fin >> relay_or_medley;
       			one_event.set_type("Individual");
       			one_event.add_event_name(gender+' '+match_length+' '+match_type+' '+relay_or_medley); //store name
       		}
       		else {
       			one_event.add_event_name(gender+' '+match_length+' '+match_type);
       			one_event.set_type("Individual");
       		}
     		fin >> type;  
       		while ( type == "HEAT" || type == "SEMI"|| type == "FINAL")	{
       			if(fin.eof()) break;
    		    one_swimmer.read( fin, type, num_of_50ms ); 
    			one_event.add_swimmer(one_swimmer); 
    			fin >> type; 
       		}
    	}   
       	one_event.sort_swimmer_speed(); 
    	events.push_back(one_event);
    	if(fin.eof()) break;
	}
	if (string(argv[3])=="events"){
		sort(events.begin(), events.end(), Alphabetical); //sort event name alphabetically 
		if (argc == 4){
			for (int i=0; i<events.size(); ++i) 
				events[i].print_events(fout, events[i].get_num(),events[i].get_type()); //print events
		}
		else if (argc == 5 && string(argv[4])=="medals")
			for (int i=0; i<events.size(); ++i) 
				events[i].print_events_medals(fout, events[i].get_num(),events[i].get_type()); //print events&medals
		
	}
	if (string(argv[3])=="participants"){
    for (int i=0; i<events.size(); ++i) 
      events[i].calc_medals();              //calculate events medals 
    for (int i=0; i<events.size(); ++i)
      if (events[i].get_type()=="Relay")
        events[i].give_medal_to_relay_swimmer(); //pass medals from winning country to its swimmers

		vector<Participant> participants;      //create another class to store printing participants.
		Participant one_participant;
		for (int i=0; i<events.size(); ++i)
			for (int j=0; j<events[i].swimmersize(); ++j){
				if ( events[i].swimmer_iscountry(j) ) continue;
				else {
					events[i].record_participants(one_participant, j);
					participants.push_back(one_participant);
				}
			}
		sort (participants.begin(), participants.end(), by_name);
		clean_itself(participants);                  //put same swimmmer in one participant
		sort (participants.begin(), participants.end(), by_country);
		if (argc == 4) printevents(fout, participants);
		else if (argc == 5 && string(argv[4])=="medals")  printeventsmedals(fout, participants);
	}
	return 0;
}