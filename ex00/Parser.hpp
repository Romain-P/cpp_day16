//
// Created by romain.pillot on 1/18/18.
//

#ifndef EX00_PARSER_HPP
#define EX00_PARSER_HPP

#include <string>
#include <stack>
#include <map>
#include <functional>

enum Operator_char {
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
    MOD = '%',
    LEFT = '(',
    RIGHT = ')'
};

class Operator {
public:
    Operator(Operator_char c, int precedence, std::function<int(int, int)> apply)
            : _op(c), _precedence(precedence), _apply(std::move(apply)) {};

    Operator() = default;
    Operator &operator=(Operator const &alt) {
        _op = alt._op;
        _precedence = alt._precedence;
        _apply = alt._apply;
        return *this;
    }

    Operator(Operator const &alt) : _op(alt._op), _precedence(alt._precedence), _apply(alt._apply) {}

    Operator_char _op;
    int _precedence;
    std::function<int(int, int)> _apply;
};

class Parser {
public:

    static std::map<char, Operator> const init();
    static std::map<char, Operator> const OPS;

    void feed(std::string const &s);
    int result() const;
    void reset();

    Parser() {
        _postfix = std::string();
        _operands = std::stack<int>();
        _operators = std::stack<char>();
    }

private:
    std::string _postfix;
    int _result;
    std::stack<int> _operands;
    std::stack<char> _operators;

    int next_number(char const *s, int &i);
    std::string generate_postfix_expr(std::string const &s);
    int parse_postfix(std::string &postfix);
};


#endif //EX00_PARSER_HPP
