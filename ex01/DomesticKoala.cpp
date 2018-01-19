//
// Created by romain.pillot on 1/19/18.
//

#include <algorithm>
#include "DomesticKoala.hpp"

DomesticKoala::DomesticKoala(KoalaAction &action)
        : _action(action), _actions(std::vector<methodPointer_t>()), _commands(std::vector<char>()) {}

DomesticKoala::DomesticKoala(const DomesticKoala &alt)
        : _action(alt._action), _actions(std::vector<methodPointer_t>(alt._actions)),
          _commands(std::vector<char>(alt._commands)) {}


DomesticKoala &DomesticKoala::operator=(const DomesticKoala &alt) {
    _action = alt._action;
    _actions = std::vector<methodPointer_t>(alt._actions);
    _commands = std::vector<char>(alt._commands);
}

std::vector<methodPointer_t> const *DomesticKoala::getActions() const {
    return &_actions;
}

void DomesticKoala::learnAction(unsigned char command, methodPointer_t action) {
    _commands.push_back(command);
    _actions.push_back(action);
}

void DomesticKoala::doAction(unsigned char command, const std::string &param) {
    long index = std::find(_commands.begin(), _commands.end(), command) - _commands.begin();

    if (index < _commands.size())
        (_action.*_actions[index])(param);
}

void DomesticKoala::setKoalaAction(KoalaAction &action) {
    _action = action;
}

void DomesticKoala::unlearnAction(unsigned char command) {
    long index = std::find(_commands.begin(), _commands.end(), command) - _commands.begin();
    _commands.erase(_commands.begin() + index);
    _actions.erase(_actions.begin() + index);
}