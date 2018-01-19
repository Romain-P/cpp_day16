//
// Created by romain.pillot on 1/19/18.
//

#include "Ratatouille.hpp"

Ratatouille::Ratatouille() : _stream(std::stringstream()) {};

Ratatouille::Ratatouille(Ratatouille const &other) : _stream(std::stringstream()) {
    _stream << other._stream.str();
}

Ratatouille &Ratatouille::operator =(const  Ratatouille &rhs) {
    _stream = std::stringstream();
    _stream << rhs._stream.str();
    return *this;
}

Ratatouille &Ratatouille::addVegetable(unsigned char c) {
    _stream << c;
    return *this;
}

Ratatouille &Ratatouille::addCondiment(unsigned int i) {
    _stream << i;
    return *this;
}

Ratatouille &Ratatouille::addSpice(double d) {
    _stream << d;
    return *this;
}

Ratatouille &Ratatouille::addSauce(const std::string &s) {
    _stream << s;
    return *this;
}

std::string Ratatouille::kooc() {
    return _stream.str();
}