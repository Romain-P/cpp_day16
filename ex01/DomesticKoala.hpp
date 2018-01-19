//
// Created by romain.pillot on 1/19/18.
//

#ifndef EX00_DOMESTICKOALA_HPP
#define EX00_DOMESTICKOALA_HPP

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "KoalaAction.hpp"

/**
class KoalaAction {
public:
    void eat(std::string const &s) {
        std::cout << "I eat: " << s << std::endl;
    }

    void goTo(std::string const &s) {
        std::cout << "I go to: " << s << std::endl;
    }

    void sleep(std::string const &s) {
        std::cout << "I sleep, and dream of: " << s << std::endl;
    }

    void reproduce(std::string const &s) {
        std::cout << "I attempt to reproduce with: " << s << std::endl;
    }
}; **/

class DomesticKoala;
using  methodPointer_t = void (KoalaAction::*)(std::string const &);

class DomesticKoala {
private:
    KoalaAction &_action;
    std::vector<methodPointer_t> _actions;
    std::vector<char> _commands;
public:
    explicit DomesticKoala(KoalaAction  &);
    ~DomesticKoala () = default;
    DomesticKoala(const  DomesticKoala  &);
    DomesticKoala &operator=(const  DomesticKoala &);
    const  std::vector <methodPointer_t > *getActions () const;
    void  learnAction(unsigned  char  command , methodPointer_t  action);
    void  unlearnAction(unsigned  char  command);
    void  doAction(unsigned  char  command , const  std:: string &param);
    void  setKoalaAction(KoalaAction  &);
};


#endif //EX00_DOMESTICKOALA_HPP
