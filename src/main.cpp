#include "Vire/AST-Parse/Include.hpp"
#include "Vire/Proto/Include.hpp"
#include "Vire/VAnalyzer/Include.hpp"
#include "Vire/Error-Builder/Include.hpp"

int main()
{
    auto file=vire::proto::openFile("resources/test.ve");
    auto code=vire::proto::readFile(file, 1);

    //std::cout << code << std::endl;

    auto lexer=std::make_unique<vire::Virelex>(code);
    auto parser=std::make_unique<vire::Vireparse>(std::move(lexer));

    parser->getNextToken();

    auto var=parser->ParseVariableDef();
    std::cout << "On line: " << var->getCharpos () << std::endl;

    //std::unique_ptr<vire::VariableDefAST> f(static_cast<vire::VariableDefAST*>(parser->ParseVariableDef().release()));

    //auto v=std::make_unique<vire::VAnalyzer>();
    //v->verifyVarDef(f);

    //auto e=new vire::errors::ErrorBuilder();

    //e->addError<vire::errors::lex_unknown_char>('a','b');
    //e->showErrors();

    //delete e;

    return 0;
}