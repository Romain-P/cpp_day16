//
// Created by romain.pillot on 1/18/18.
//

#include <iostream>
#include <utility>
#include "Parser.hpp"


std::map<char, Operator> const Parser::OPS = init();

std::map<char, Operator> const Parser::init() {
    std::map<char, Operator> map = std::map<char, Operator>();

    map[ADD] = Operator(ADD, -1, [](int a, int b) -> int { return a + b; });
    map[SUB] = Operator(SUB, -1, [](int a, int b) -> int { return a - b; });
    map[DIV] = Operator(DIV, 0, [](int a, int b) -> int { return a / b; });
    map[MUL] = Operator(MUL, 0, [](int a, int b) -> int { return a * b; });
    map[MOD] = Operator(MOD, 0, [](int a, int b) -> int { return a % b; });
    map[RIGHT] = Operator(RIGHT, 1, nullptr);
    map[LEFT] = Operator(LEFT, 1, nullptr);

    return map;
}

std::string Parser::generate_postfix_expr(std::string const &s) {
    auto add_to_result = [](std::string &result, int body, bool op) -> void {
        if (!result.empty())
            result += ' ';
        if (op)
            result += (char) body;
        else
            result += std::to_string(body);
    };

    std::string postfix;

    char c;
    for (int i = 0; (c = s[i]); ++i) {
        if (c == LEFT)
            _operators.push(c);
        else if (c == RIGHT) {
            while (!_operators.empty() && _operators.top() != LEFT) {
                add_to_result(postfix, _operators.top(), true);
                _operators.pop();
            }
            _operators.pop();
        } else if (OPS.find(c) != OPS.end()) {
            if (!_operators.empty() && _operators.top() != LEFT) {
                while (!_operators.empty() &&
                       _operators.top() != LEFT &&
                       OPS.at(c)._precedence <= OPS.at(_operators.top())._precedence) {
                    add_to_result(postfix, _operators.top(), true);
                    _operators.pop();
                }
            }
            _operators.push(c);
        } else if (c != ' ')
            add_to_result(postfix, next_number(s.c_str() + i, i), false);
    }

    while (!_operators.empty()) {
        add_to_result(postfix, _operators.top(), true);
        _operators.pop();
    }

    return postfix;
}

int Parser::parse_postfix(std::string &postfix) {
    char c;
    for (int i=0; (c = postfix[i]); ++i) {
        if (OPS.find(c) != OPS.end()) {
            int a = _operands.top();
            _operands.pop();
            int b = _operands.top();
            _operands.pop();
            _operands.push(OPS.at(c)._apply(b, a));
        } else if (c != ' ') {
            int next = next_number(postfix.c_str() + i, i);
            _operands.push(next);
        }
    }

    _result = _postfix.empty() ? _operands.top() : _result + _operands.top();
    _postfix = postfix;
    _operands.pop();

    return _result;
}

void Parser::feed(std::string const &s) {
    std::string postfix = generate_postfix_expr(s);
    parse_postfix(postfix);
}

int Parser::next_number(char const *s, int &j) {
    int nb = 0;
    int index = 0;
    while (s[index] >= '0' && s[index] <= '9')
        nb = nb * 10 + (s[index++] - '0');
    j += index - 1;
    return nb;
};

int Parser::result() const {
    return _result;
}

void Parser::reset() {
    _operands = std::stack<int>();
    _operators = std::stack<char>();
    _postfix = std::string();
    _result = 0;
}