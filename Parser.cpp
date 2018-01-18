//
// Created by romain.pillot on 1/18/18.
//

#include <iostream>
#include "Parser.hpp"


std::map<char, Operator> const Parser::OPS = init();

std::map<char, Operator> const Parser::init() {
    std::map<char, Operator> map = std::map<char, Operator>();

    map[ADD] = Operator(ADD, -1);
    map[SUB] = Operator(SUB, -1);
    map[DIV] = Operator(DIV, 0);
    map[MUL] = Operator(MUL, 0);
    map[MOD] = Operator(MOD, 0);
    map[RIGHT] = Operator(RIGHT, 1);
    map[LEFT] = Operator(LEFT, 1);

    return map;
}

void Parser::feed(std::string const &s) {
    auto is_operator = [](char c) -> bool { return OPS.find(c) != OPS.end(); };

    auto next_number = [](char const *s, int &j) -> int {
        int nb = 0;
        int index = 0;
        while (s[index] >= '0' && s[index] <= '9')
            nb = nb * 10 + (s[index++] - '0');
        j += index - 1;
        return nb;
    };

    auto add_to_result = [](std::string &result, int body, bool op) -> void {
        if (!result.empty())
            result += ' ';
        if (op)
            result += (char) body;
        else
            result += std::to_string(body);
    };

    char c;
    for (int i = 0; (c = s[i]); ++i) {
        if (c == LEFT)
            _operators.push(c);
        else if (c == RIGHT) {
            while (!_operators.empty() && _operators.top() != LEFT) {
                add_to_result(_result, _operators.top(), true);
                _operators.pop();
            }
            _operators.pop();
        } else if (is_operator(c)) {
            if (!_operators.empty() && _operators.top() != LEFT) {
                while (!_operators.empty() &&
                       _operators.top() != LEFT &&
                       OPS.at(c)._precedence <= OPS.at(_operators.top())._precedence) {
                    add_to_result(_result, _operators.top(), true);
                    _operators.pop();
                }
            }
            _operators.push(c);
        } else
            add_to_result(_result, next_number(s.c_str() + i, i), false);
    }

    while (!_operators.empty()) {
        add_to_result(_result, _operators.top(), true);
        _operators.pop();
    }
    std::cout << _result << std::endl;
}

void Parser::reset() {
    _operands = std::stack<int>();
    _operators = std::stack<char>();
    _result = std::string();
}

int Parser::result() const {

}