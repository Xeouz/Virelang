#pragma once

#include <string>

#include "ASTType.hpp"
#include "ExprAST.cpp"

#include <vector>
#include <memory>

namespace vire
{
// IntExprAST - Class for representing ints, eg - 123
class IntExprAST : public ExprAST
{
    int val;
public:
    IntExprAST(int val, std::unique_ptr<Viretoken> token=nullptr) : val(val), ExprAST("int",ast_int,std::move(token)) {}

    const int& getValue() const {return val;}
};

// FloatExprAST - Class for representing floats, eg 1.23
class FloatExprAST: public ExprAST 
{
    float val;
public:
    FloatExprAST(float val, std::unique_ptr<Viretoken> token=nullptr) : val(val), ExprAST("float",ast_float, std::move(token)) {}

    const float& getValue() const {return val;}
};

// DoubleExprAST - Class for representing doubles, eg 1.23
class DoubleExprAST: public ExprAST
{
    double val;
public:
    DoubleExprAST(double val, std::unique_ptr<Viretoken> token) : val(val), ExprAST("double",ast_double,std::move(token)) {}

    const double& getValue() const {return val;}
};

// CharExprAST - Class for representing characters, eg - 'a'
class CharExprAST : public ExprAST
{
    char val;
public:
    CharExprAST(char val, std::unique_ptr<Viretoken> token=nullptr) : val(val), ExprAST("char",ast_char,std::move(token)) {}

    const char& getValue() const {return val;}
};

// StrExprAST - Class for representing strings, eg - "abc"
class StrExprAST : public ExprAST
{
    std::string val;
public:
    StrExprAST(const std::string& val, std::unique_ptr<Viretoken> token=nullptr) : val(val), ExprAST("str",ast_str,std::move(token)) {}

    const std::string& getValue() const {return val;}
};

// ArrayExprAST - CLass for representing Arrays, eg - [1,2,3,4,5]
class ArrayExprAST : public ExprAST
{
    std::vector<std::unique_ptr<ExprAST>> Elements;
public:
    ArrayExprAST(std::vector<std::unique_ptr<ExprAST>> Elements)
    :   Elements(std::move(Elements)), ExprAST("arr", ast_array) {}

    std::vector<std::unique_ptr<ExprAST>> const& getElements() const {return Elements;}
};

}