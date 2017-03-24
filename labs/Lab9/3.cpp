
#include <iostream>
#include <map>
#include <string>

void add(std::map<int, std::string> &phonebook, int number, std::string const& name) {
    if (phonebook.find(number) == phonebook.end()) {
        phonebook.insert(std::make_pair(number, name));
        std::cout << name << "'s number added" << std::endl;
    }
    else 
        std::cout <<  "This number is already existed" << std::endl;
}


void identify(const std::map<int, std::string> &phonebook, int number) {
    if (phonebook.find(number) == phonebook.end())
        std::cout << "unknown caller!" << std::endl;
    else
        std::cout << phonebook.find(number)->second << " is calling!" << std::endl;
}


int main() {
    std::map<int , std::string> phonebook;
    
    add(phonebook, 2274282, "A");
    add(phonebook, 4669691, "B");
    add(phonebook, 2279625, "C");
    add(phonebook, 2274282, "A2");
    
    identify(phonebook, 2274282);
    identify(phonebook, 4444444);
}
