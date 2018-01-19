//
// Created by romain.pillot on 1/19/18.
//

#ifndef EX00_RATATOUILLE_HPP
#define EX00_RATATOUILLE_HPP

#include <string>
#include <sstream>

class Ratatouille {
public:
    Ratatouille ();
    Ratatouille(Ratatouille const &other);
    ~Ratatouille() = default;

    Ratatouille &operator =(const  Ratatouille &rhs);
    Ratatouille &addVegetable(unsigned  char);
    Ratatouille &addCondiment(unsigned  int);
    Ratatouille &addSpice(double);
    Ratatouille &addSauce(const  std::string  &);

    std::string  kooc();

private:
    std::stringstream _stream;
};


#endif //EX00_RATATOUILLE_HPP
