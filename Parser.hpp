//
// Created by romain.pillot on 1/18/18.
//

#ifndef EX00_PARSER_HPP
#define EX00_PARSER_HPP

#include <string>
#include <stack>
#include <map>

enum Operator_char {
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
    MOD = '%',
    LEFT = '(',
    RIGHT = ')'
};

template<typename T>
class Entity {

};

class Operator {
public:
    Operator(Operator_char c, int precedence) : _op(c), _precedence(precedence) {}
    Operator() = default;
    Operator &operator=(Operator const &alt) {
        _op = alt._op;
        _precedence = alt._precedence;
    }
    Operator(Operator const &alt) : _op(alt._op), _precedence(alt._precedence) {}

    Operator_char _op;
    int _precedence;
};

class Parser {
public:

    static std::map<char, Operator> const init();
    static std::map<char, Operator> const OPS;

    void feed(std::string const &s);
    int result() const;
    void reset();

    Parser() {
        _result = std::string();
        _operands = std::stack<int>();
        _operators = std::stack<char>();
    }

private:
    std::string _result;
    std::stack<int> _operands;
    std::stack<char> _operators;
};


#endif //EX00_PARSER_HPP
