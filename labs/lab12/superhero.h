#ifndef superhero_h_
#define superhero_h_
#include <iostream>
#include <string>


class Superhero
{
public:
    Superhero() : name(""), power(""), identity(""), good(true) {}
    Superhero(std::string name_, std::string identity_, std::string power_) :
    name(name_), power(power_), identity(identity_), good(true) {}
    
    // ACCESSOR
    std::string getName() const {return name;}
    std::string getPower() const {return power;}
    std::string getTrueIdentity() const {return identity;}
    bool isGood() const {return good;}
    
    bool operator== (const std::string n) {return identity == n;}
    bool operator!= (const std::string n) {return identity != n;}
    
    bool operator> (const Superhero &hero)
    {
        if (power == "Fire" && hero.getPower() == "Wood") return true;
        else if ( power == "Wood" && hero.getPower() == "Fire" ) return false;
        else if ( power == "Wood" && hero.getPower() == "Water" ) return true;
        else if ( power == "Water" && hero.getPower() == "Wood" ) return false;
        else if ( power == "Water" && hero.getPower() == "Fire" ) return true;
        else if ( power == "Fire" && hero.getPower() == "Water" ) return false;
        else if ( power.size() == hero.getPower().size() )
            return power > hero.getPower();
        else return power.size() > hero.getPower().size();
    }
    
    void operator-() {good = !good;}
    
private:
    std::string name;
    std::string power;
    std::string identity;
    bool good;
};

inline std::ostream& operator<<(std::ostream &ostr, const Superhero &hero)
{
    if (hero.isGood())
        ostr << "Superhero " << hero.getName() << " has power " << hero.getPower() << std::endl;
    else
        ostr << "Supervillain " << hero.getName() << " has power " << hero.getPower() << std::endl;
    return ostr;
}


#endif