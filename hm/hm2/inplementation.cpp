#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "event.h"
#include "participant.h"

using namespace std;

void Event::print_events(ofstream& fout, int number, string STR ) const{ // print events only
	fout << event_name;
	for (int i=1; i<=39-event_name.size(); ++i) fout<<' ';
	for (int i=1; i<=number; ++i) {
		if (i >= 19 && i <30) fout<<i*50<<'m'<<"   ";
		else fout<<i*50<<'m'<<"     ";
	}
	fout << "  FINAL"<<endl;
	for (int i=1; i<=number*9+45; ++i) fout<<'-';
	fout <<endl;
	for (int i=0; i<5; ++i){
		if (STR == "Relay") fout<<Swimmers[i].get_country();
		else fout<<Swimmers[i].get_first_name()<<' '<<Swimmers[i].get_last_name();
		int namelength;
		if (STR == "Relay") namelength = Swimmers[i].get_country().size();
		else namelength = Swimmers[i].get_first_name().size()+Swimmers[i].get_last_name().size()+1;
		for (int j=1; j<=37-namelength; ++j) fout<<' ';
		for (int j=0; j<number; ++j) fout<<Swimmers[i].get_intermediate_time(j)<<"    ";
		for (int j=1; j<=8-Swimmers[i].get_final_size(); ++j) fout<<' ';
		fout<<Swimmers[i].get_final_time()<<endl;
	} fout<<endl;
}

void Event::print_events_medals(ofstream& fout, int number, string STR) const{ //print events&medals
	bool gold_, silver_, bronze_, non_medalist;
	gold_ = silver_ = bronze_ = true;
	non_medalist=false;
	int gold_total, silver_total, bronze_total; 
	gold_total=silver_total=bronze_total=0;

	fout << event_name;
	for (int i=1; i<=39-event_name.size(); ++i) fout<<' ';	
	for (int i=1; i<=number; ++i) {
		if (i >= 19 && i <30) fout<<i*50<<'m'<<"    ";
		else fout<<i*50<<'m'<<"     ";
	}
	fout << "  FINAL    MEDALS"<<endl;
	for (int i=1; i<=number*9+55; ++i) fout<<'-';
	fout <<endl;
	for (int i=0; i<Swimmers.size(); ++i){
		if ( (!gold_ && !silver_ && !bronze_ && i>4 && non_medalist) ) break;
		if (STR == "Relay") fout<<Swimmers[i].get_country();
		else fout<<Swimmers[i].get_first_name()<<' '<<Swimmers[i].get_last_name();
		int namelength;
		if (STR == "Relay") namelength = Swimmers[i].get_country().size();
		else namelength = Swimmers[i].get_first_name().size()+Swimmers[i].get_last_name().size()+1;
		if ( Swimmers[i].get_appendix() != "FINAL" ) {
			fout<<" ("<<Swimmers[i].get_appendix()<<')';
			namelength += Swimmers[i].get_appendix().size()+3;
		}
		for (int j=1; j<=37-namelength; ++j) fout<<' ';
		for (int j=0; j<number; ++j) fout<<Swimmers[i].get_intermediate_time(j)<<"    ";
		for (int j=1; j<=8-Swimmers[i].get_final_size(); ++j) fout<<' ';
		fout<<Swimmers[i].get_final_time();
		if ( Swimmers[i].get_appendix() == "FINAL" ){
			if ( gold_total >= 3 ){
				if ( bronze_ ) bronze_ = false;
				if ( silver_ ) silver_ = false;
			}
			if ( gold_total == 2 )
				if ( bronze_ ) bronze_ = false;

			if ( gold_total == 1 )
				if ( silver_total >=3 )
					if ( bronze_ ) bronze_ = false;
			if (gold_){
				fout<<"      GOLD"<<endl;     
				gold_total++,gold_=false; 
				if (Swimmers[i+1].get_final_time() == Swimmers[i].get_final_time()) gold_ = true;
				continue;
			} 
			if (silver_){
				fout<<"    SILVER"<<endl;  
				silver_total++,silver_=false; 
				if (Swimmers[i+1].get_final_time() == Swimmers[i].get_final_time()) silver_ = true;
				continue;
			}			
			if (bronze_){
				fout<<"    BRONZE"<<endl;  
				bronze_total++,bronze_=false; 
				if (Swimmers[i+1].get_final_time() == Swimmers[i].get_final_time()) bronze_ = true; 
				continue;
			}
			non_medalist=true;fout<<"          "<<endl; continue; 
		} fout<<"          "<<endl;
	} fout<<endl;
}

void Event::calc_medals() {                        //judge the medals for events.
	bool gold_, silver_, bronze_, non_medalist;
	gold_ = silver_ = bronze_ = true;
	non_medalist=false;
	int gold_total, silver_total, bronze_total; 
	gold_total=silver_total=bronze_total=0;

	for (int i=0; i<Swimmers.size(); ++i){
		if ( (!gold_ && !silver_ && !bronze_ && i>4 && non_medalist) ) break; //first non-medalist prerequizite
		if ( Swimmers[i].get_appendix() == "FINAL" ){
			if ( gold_total >= 3 ){
				if ( bronze_ ) bronze_ = false;
				if ( silver_ ) silver_ = false;
			}
			if ( gold_total == 2 )
				if ( bronze_ ) bronze_ = false;

			if ( gold_total == 1 )
				if ( silver_total >=3 )
					if ( bronze_ ) bronze_ = false;
			if (gold_){
				Swimmers[i].increase_gold();
				gold_total++,gold_=false; 
				if (Swimmers[i+1].get_final_time() == Swimmers[i].get_final_time()) gold_ = true;
				continue;
			} 
			if (silver_){
				Swimmers[i].increase_silver();
				silver_total++,silver_=false; 
				if (Swimmers[i+1].get_final_time() == Swimmers[i].get_final_time()) silver_ = true;
				continue;
			}			
			if (bronze_){
				Swimmers[i].increase_bronze();
				bronze_total++,bronze_=false; 
				if (Swimmers[i+1].get_final_time() == Swimmers[i].get_final_time()) bronze_ = true; 
				continue;
			}
			non_medalist=true; continue; 
		} 
	} 
}

void Event::give_medal_to_relay_swimmer(){  //associate relay_swimmer to its country, pass medals to them.
	for (int k=0; k<Swimmers.size(); ++k){
		if ( Swimmers[k].get_gold() == 1 && Swimmers[k].get_is_country() ){
			for (int l=0; l<Swimmers.size(); ++l){
				if (l==k) continue;
				if ( Swimmers[l].get_country_abbr()==Swimmers[k].get_country_abbr() 
					&& !Swimmers[l].get_is_country() && Swimmers[l].get_appendix()=="FINAL" )
					Swimmers[l].increase_gold();
			}
		}
		if ( Swimmers[k].get_silver() == 1 && Swimmers[k].get_is_country() ){
			for (int l=0; l<Swimmers.size(); ++l){
				if (l==k) continue;
				if ( Swimmers[l].get_country_abbr()==Swimmers[k].get_country_abbr() 
					&& !Swimmers[l].get_is_country() && Swimmers[l].get_appendix()=="FINAL" )
					Swimmers[l].increase_silver();
			}
		}
		if ( Swimmers[k].get_bronze() == 1 && Swimmers[k].get_is_country() ){
			for (int l=0; l<Swimmers.size(); ++l){
				if (l==k) continue;
				if ( Swimmers[l].get_country_abbr()==Swimmers[k].get_country_abbr() 
					&& !Swimmers[l].get_is_country() && Swimmers[l].get_appendix()=="FINAL" )
					Swimmers[l].increase_bronze();
			}
		}
	}
}

void Event::record_participants( Participant &P1, int _num ){ //record participants from swimmers
    P1.initialize();
    P1.set_first_name( Swimmers[_num].get_first_name() );
    P1.set_last_name( Swimmers[_num].get_last_name() );
    P1.set_gold_num( Swimmers[_num].get_gold() );
    P1.set_silver_num( Swimmers[_num].get_silver() );
    P1.set_bronze_num( Swimmers[_num].get_bronze() );
    P1.set_heat_num( Swimmers[_num].get_heat() );
    P1.set_semi_num( Swimmers[_num].get_semi() );
    P1.set_final_num( Swimmers[_num].get_final() );
    P1.set_country_abbr( Swimmers[_num].get_country_abbr() );
}

void Swimmer::seperate_time( vector<string> &Time ){ //substract time and get time for every "50m"
	for ( int i=Time.size()-1; i>0; --i )
		Time[i]=Timefloat_to_TimeString(TimeString_to_Timefloat(Time[i])-TimeString_to_Timefloat(Time[i-1]));
}

void Swimmer::read (ifstream& fin, string TYPE, int num_) { //add non-relay swimmer in the event
	string _time, round, lane;
	initialize_member();
	intermediate_timing.clear();


	if ( TYPE == "FINAL" ) {
		increase_final();
		set_appendix("FINAL");
		fin >> lane >> first_name >> last_name >> country_abbr;
		for (int i=1; i<=num_; ++i ){
			fin>>_time; 
			if ( i == num_ ) final_time = _time;			
			intermediate_timing.push_back(_time);
		}
		seperate_time(intermediate_timing); 
	}
	else {
		if ( TYPE == "HEAT" ) {
			increase_heat();
			set_appendix("HEAT");
		}
		if ( TYPE == "SEMI" ) {
			increase_semi();
			set_appendix("SEMI");
		}

		fin >> round >> lane >> first_name >> last_name >> country_abbr;
		for (int i=1; i<=num_; ++i ){
			fin>>_time; 
			if ( i == num_ ) final_time = _time;
			intermediate_timing.push_back(_time);
		}
		seperate_time(intermediate_timing); 
	}
}

void Swimmer::read_relay( ifstream& fin, string TYPE, int num_){ //add relay contry in the event
	string _time, round, lane;
	initialize_member();
	intermediate_timing.clear();
	is_country = true;

	if ( TYPE == "FINAL" ) {
		increase_final();
		set_appendix("FINAL");
		fin >> lane >> country >> country_abbr;

		for (int i=1; i<=num_; ++i ){
			fin>>_time;
			if ( i == num_ ) final_time = _time;			
			intermediate_timing.push_back(_time);
		}
		seperate_time(intermediate_timing);
	}
	else {
		if ( TYPE == "HEAT" ) {
			increase_heat();
			set_appendix("HEAT");
		}
		if ( TYPE == "SEMI" ) {
			increase_semi();
			set_appendix("SEMI");
		}

		fin >> round >> lane >> country >> country_abbr;

		for (int i=1; i<=num_; ++i ){
			fin>>_time;
			if ( i == num_ ) final_time = _time;			
			intermediate_timing.push_back(_time);
		}
		seperate_time(intermediate_timing);
	}
}

void Swimmer::read_relay_swimmer( ifstream& fin, Swimmer _swimmer){ //add the relay swimmer in the event
	initialize_member();
	final_time="40:00.00"; //set it as "40:00.00 in order to seperate it from its country's time"
	string F_Name, L_name;
	fin>>F_Name>>L_name;
	first_name = F_Name;
	last_name = L_name;
	appendix = _swimmer.appendix;
	country_abbr = _swimmer.country_abbr;
	heat = _swimmer.heat;
	semi = _swimmer.semi;
	final = _swimmer.final;
	gold = _swimmer.gold;
	silver = _swimmer.silver;
	bronze = _swimmer.bronze;
}

double Swimmer::TimeString_to_Timefloat ( string TIME ) const{
	unsigned int minute = 0; 
	double second;
	unsigned int position = TIME.find(':');  
	unsigned int length = TIME.size();
	if ( position == -1 ) second = stod(TIME);
	else{
		string _minute (TIME, 0, position ); 
		string _second (TIME, position+1, length-1); 
		minute = stod( _minute );
		second = stod( _second );
	}
	return minute*60 + second;
}

string Swimmer::Timefloat_to_TimeString ( double TIME ) const{
	int minute_ = TIME/60;
	double second_ = TIME-minute_*60;
	string _Minute = to_string(minute_);
	string Sec;
	if ( second_ < 10 )
		Sec = '0'+ to_string(second_);
	else Sec = to_string(second_);
	string _Second (Sec, 0, 5);
	string TIME_String;
	if ( _Minute == "0") TIME_String=_Second;
	else TIME_String= _Minute+':'+_Second;
	return TIME_String;
}

void clean_itself( vector<Participant> &P1 ){ //judge same swimmer in different events, add them in one participant.
	int INDEX=0;
	while (INDEX<P1.size()-1)
		if ( P1[INDEX].first_name() == P1[INDEX+1].first_name() && P1[INDEX].last_name() == P1[INDEX+1].last_name() ){
			P1[INDEX+1].increase_gold_num( P1[INDEX].gold_num() );
			P1[INDEX+1].increase_silver_num( P1[INDEX].silver_num() );
			P1[INDEX+1].increase_bronze_num( P1[INDEX].bronze_num() );
			P1[INDEX+1].increase_heat_num( P1[INDEX].heat_num() );
			P1[INDEX+1].increase_semi_num( P1[INDEX].semi_num() );
			P1[INDEX+1].increase_final_num( P1[INDEX].final_num() );
			P1.erase(P1.begin()+INDEX);
		}
		else INDEX++;
}

void printevents(ofstream &fout,  vector<Participant> P1 ) {
	fout<<"COUNTRY  PARTICIPANT                HEATS  SEMIS  FINALS"<<endl;
	fout<<"--------------------------------------------------------"<<endl;
	for (int i=0; i<P1.size(); ++i){
		int namelength = P1[i].first_name().size()+P1[i].last_name().size()+1;
		fout<<P1[i].country_abbr()<<"      ";
		fout<<P1[i].first_name()<<' '<<P1[i].last_name();
		for (int j=1; j<=27-namelength; ++j) fout<<' ';
			fout << "    "<<P1[i].heat_num()<<"      "<<P1[i].semi_num()<<"       "<<P1[i].final_num()<<endl;
	}
}

void printeventsmedals( ofstream &fout, vector<Participant> P1 ){
	fout<<"COUNTRY  PARTICIPANT                HEATS  SEMIS  FINALS    GOLD  SILVER  BRONZE"<<endl;
	fout<<"--------------------------------------------------------------------------------"<<endl;
	for (int i=0; i<P1.size(); ++i){
		int namelength = P1[i].first_name().size()+P1[i].last_name().size()+1;
		fout<<P1[i].country_abbr()<<"      ";
		fout<<P1[i].first_name()<<' '<<P1[i].last_name();
		for (int j=1; j<=27-namelength; ++j) fout<<' ';
		fout << "    ";
		if (P1[i].heat_num()==0) fout<<' ';
		else fout<<P1[i].heat_num();
		fout << "      ";
		if (P1[i].semi_num()==0) fout<<' ';
		else fout<<P1[i].semi_num();
		fout << "       ";
		if (P1[i].final_num()==0) fout<<' ';
		else fout<<P1[i].final_num();
		fout << "       ";
		if (P1[i].gold_num()==0) fout<<' ';
		else fout<<P1[i].gold_num();
		fout << "       ";
		if (P1[i].silver_num()==0) fout<<' ';
		else fout<<P1[i].silver_num();
		fout << "       ";
		if (P1[i].bronze_num()==0) fout<<' '<<endl;
		else fout<<P1[i].bronze_num()<<endl;
	}
}


int judge_num_50ms( string str_ ){
    if ( str_ == "50m") return 1;
    else if ( str_ == "100m") return 2;
    else if ( str_ == "200m") return 4;
    else if ( str_ == "400m" || str_ == "4x100m") return 8;
    else if ( str_ == "800m" || str_ == "4x200m") return 16;
    else return 30;
}

bool by_speed ( const Swimmer& S1, const Swimmer& S2 ) {   //sort by speed, last name then first name
 	if ( S1.get_time_double() == S2.get_time_double() ){
 		if ( S1.get_last_name() == S2.get_last_name() )
 			return S1.get_first_name()<S2.get_first_name();
 		return S1.get_last_name()<S2.get_last_name();
 	} return S1.get_time_double()<S2.get_time_double();
 }

bool by_country ( const Participant& P1, const Participant& P2 ) { //sort by country, last name then first name
 	if ( P1.country_abbr() == P2.country_abbr() ){
 		if ( P1.last_name() == P2.last_name() )
 			return P1.first_name()<P2.first_name();
 		return P1.last_name()<P2.last_name();
 	} return P1.country_abbr()<P2.country_abbr();
 }

bool by_name(const Participant &P1, const Participant &P2){ //sort by first name, then last name
	if ( P1.last_name() == P2.last_name() )
 			return P1.first_name()<P2.first_name();
 	return P1.last_name()<P2.last_name();
}

bool Alphabetical ( const Event& E1, const Event& E2 ) {return E1.get_event_name()<E2.get_event_name();}

