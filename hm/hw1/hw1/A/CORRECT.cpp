
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
using namespace std;

int readthewords(ifstream& fin, int now, int width, vector<string> &words){
    string line, _index; now=0;
    while ( fin>>line)
    {   
        
        while (line.size() > width)           //when the words are superlong, split them;
        {        
            _index.erase();
            for (int i=0; i<width-1; i++) _index+=line[i];

            _index.push_back('-');
            words.push_back(_index); now++;
            line.erase(0, width-1);
        }
        words.push_back(line); now++; 
    }
    words.push_back("");
    return now;
}

void flush_left(ofstream& fout, int num, int length, vector<string> &words){
    int start=0;
    unsigned long total_length;
    while ( start < num )
    {
        total_length=words[start++].size(); 
        if (start >= words.size()) break;
        fout << "| ";

        
        while ( total_length+words[start].size() < length && start < num) //justify how many words should be in the line.
        {
            words[start-1]+=' ';
            fout<<words[start-1];
            total_length+=words[start++].size()+1;
        }
        while ( total_length < length )   //add spare "space" at the right hand side
        {
            
            words[start-1]+=' ';
            total_length++;
            
        }
        
        fout<<words[start-1]<<" |"<<endl; 
    }
}

void flush_right(ofstream& fout, int num, int length, vector<string> &words){
    int start=0, point=0;
    unsigned long total_length;
    while ( start < num )
    {
        point=start;                                     //variable point to store the most left word's position
        
        total_length=words[start++].size();
        if (start >= words.size()) break;
        fout << "| ";
        
        while ( total_length+words[start].size() < length && start < num) //justify how many words should be in the line.
        {
            words[start-1]+=' ';
            total_length+=words[start++].size()+1;
        }
        while ( total_length < length )   //add spare "space" at the left hand side
        {
            words[point]=' '+words[point];
            total_length++;
        }

        for ( int i=point; i<start; i++ ) fout<<words[i]; 
        fout<<" |"<<endl; 
    }
}

void full_justify(ofstream& fout, int num, int length, vector<string> &words){
    
    int start=0, point=0, index=0;
    unsigned long total_length;
    while ( start < num )
    {
        index=point=start;
        total_length=words[start++].size();

        fout << "| ";
        
        while ( total_length+words[start].size() < length && start < num)   //justify how many words should be in the line.
        {
            words[start-1]+=' ';
            total_length+=words[start++].size()+1;
        }

        if ( point != (start-1) && start < num )
            while ( total_length < length )
            {
                if ( index == (start-1) ) index=point;     //distribute the "space" along the line, from left to right, 
                words[index++]+=' ';                   //if reach the last words, automatically return to the first one;
                total_length++;
            }
        else if ( start != num+1 )
        {
            while ( total_length < length )
            {
                words[start-1]+=' ';
                total_length++;
            }
        }
        for ( int i=point; i<start; i++ ) fout<<words[i];
        fout<<" |"<<endl; 
    }
}


int main(int argc,char* argv[]) {
    //open file and check
    ifstream fin(argv[1]);
    if(!fin.good()){
        cerr<<"Can't open "<<argv[1]<<" to read.\n";
        exit(1);
    }
    //creat file to write
    ofstream fout(argv[2]);
    if(!fout.good()){
        cerr<<"Can't open "<<argv[2]<<" to read.\n";
    }
    int text_width;
    string command;
    
    text_width = atoi(argv[3]);
    command = argv[4];
    vector<string> _words;
    

    int number = readthewords(fin, 0, text_width, _words); 
    for (int k=1; k<=text_width+4; k++) fout<<'-';fout<<endl;
    
    if ( command == "flush_left" ) flush_left(fout, number, text_width, _words);
    if ( command == "flush_right" ) flush_right(fout, number, text_width, _words);
    if ( command == "full_justify" ) full_justify(fout, number, text_width, _words);

    for (int k=1; k<=text_width+4; k++) fout<<'-';fout<<endl;
    
    return 0;
    
    
}
