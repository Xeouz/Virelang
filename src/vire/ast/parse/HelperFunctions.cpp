#pragma once

#include "ASTType.hpp"
#include "ExprAST.cpp"
#include "FunctionAST.cpp"

#include <memory>

namespace vire
{

template<typename T>
std::unique_ptr<T> cast_dynamic(std::unique_ptr<ExprAST> expr)
{
    auto castAST=dynamic_cast<T*>(expr.release());
    if(castAST==nullptr) return nullptr;
    std::unique_ptr<T> newAST(castAST);

    return std::move(newAST);
}

template<typename T>
std::unique_ptr<T> cast_static(std::unique_ptr<ExprAST> expr)
{
    auto castAST=static_cast<T*>(expr.release());
    if(castAST==nullptr) return nullptr;
    std::unique_ptr<T> newAST(castAST);

    return std::move(newAST);
}

template<typename T>
std::unique_ptr<T> cast_dynamic(std::unique_ptr<FunctionBaseAST> expr)
{
    auto castAST=dynamic_cast<T*>(expr.release());
    if(castAST==nullptr) return nullptr;
    std::unique_ptr<T> newAST(castAST);

    return std::move(newAST);
}

template<typename T>
std::unique_ptr<T> cast_static(std::unique_ptr<FunctionBaseAST> expr)
{
    auto castAST=static_cast<T*>(expr.release());
    if(castAST==nullptr) return nullptr;
    std::unique_ptr<T> newAST(castAST);

    return std::move(newAST);
}

}