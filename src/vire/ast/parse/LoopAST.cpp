#pragma once

#include "ASTType.hpp"
#include "ExprAST.cpp"

#include <memory>
#include <vector>

namespace vire
{

class ForExprAST : public ExprAST
{
    std::unique_ptr<ExprAST> initExpr;
    std::unique_ptr<ExprAST> condExpr;
    std::unique_ptr<ExprAST> incrExpr;

    std::vector<std::unique_ptr<ExprAST>> body;
public:
    ForExprAST(std::unique_ptr<ExprAST> init, std::unique_ptr<ExprAST> cond, std::unique_ptr<ExprAST> incr,
    std::vector<std::unique_ptr<ExprAST>> body) :
    initExpr(std::move(init)), condExpr(std::move(cond)), incrExpr(std::move(incr)), body(std::move(body))
    , ExprAST("void",ast_for) 
    {}

    ExprAST* const getInit() const { return initExpr.get(); }
    ExprAST* const getCond() const { return condExpr.get(); }
    ExprAST* const getIncr() const { return incrExpr.get(); }

    std::unique_ptr<ExprAST> moveInit() { return std::move(initExpr); }
    std::unique_ptr<ExprAST> moveCond() { return std::move(condExpr); }
    std::unique_ptr<ExprAST> moveIncr() { return std::move(incrExpr); }

    std::vector<std::unique_ptr<ExprAST>> const& getBody() { return body; }
    std::vector<std::unique_ptr<ExprAST>> moveBody() { return std::move(body); }
};

class WhileExprAST : public ExprAST
{
    std::unique_ptr<ExprAST> condExpr;
    std::vector<std::unique_ptr<ExprAST>> body;
public:
    WhileExprAST(std::unique_ptr<ExprAST> cond, std::vector<std::unique_ptr<ExprAST>> Stms) 
    : condExpr(std::move(cond)), body(std::move(Stms)), ExprAST("void",ast_while) 
    {}

    ExprAST* const getCond() { return condExpr.get(); }
    
    std::vector<std::unique_ptr<ExprAST>> const& getBody() { return body; }
    std::vector<std::unique_ptr<ExprAST>> moveBody() {return std::move(body);}
};

class BreakExprAST : public ExprAST
{
    std::unique_ptr<ExprAST> AfterBreak;
public:
    char is_after;
    BreakExprAST() : ExprAST("",ast_break), is_after(0) {}
    BreakExprAST(std::unique_ptr<ExprAST> AfterBreak) 
    : AfterBreak(std::move(AfterBreak)), ExprAST("",ast_break), is_after(1)
    {}

    ExprAST* const getAfterBreak() { return AfterBreak.get(); }
};

class ContinueExprAST : public ExprAST
{
    std::unique_ptr<ExprAST> AfterCont;
public:
    char is_after;
    ContinueExprAST() : ExprAST("",ast_continue), is_after(0) {}
    ContinueExprAST(std::unique_ptr<ExprAST> AfterCont)
    : AfterCont(std::move(AfterCont)), ExprAST("",ast_continue), is_after(1)
    {}

    ExprAST* const getAfterCont() { return AfterCont.get(); }
};

}