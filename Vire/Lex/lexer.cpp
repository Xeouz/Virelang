#pragma once

#include <iostream> // cout, endl
#include <string> // string
#include <memory> // unique_ptr
#include <cctype> // isspace
#include <cstddef> // size_t

#include "token.hpp"
#include "token.cpp"
#include "../Exceptions/error.cpp"

namespace vire
{

class Virelex
{
protected:
    char cur;
    std::size_t indx;
    
public:
    unsigned char jit;
    std::string code;
    std::size_t len;

    Virelex(std::string code, unsigned char jit=0)
    {
        this->cur=' ';
        this->indx=-1;

        if(jit==0)
        {
            this->code=std::string(code);
            this->len=code.length();
        }
        else
        {
            this->code=std::string(" ");
            this->len=0;
        }
        this->jit=jit;
    }

    char getNext(char move_amt=0)
    {
        if(this->indx+move_amt+1==this->len)
            return EOF;
        
        this->indx+=move_amt+1;
        
        return this->code.at(this->indx);
    }

    char peekNext(char amt)
    {
        if(this->indx+amt>this->len-1)  return EOF;

        return this->code.at(this->indx+amt);
    }

    std::string gatherId()
    {
        std::string id="";

        while(isalnum(this->cur) || this->cur=='_')
        {
            if(this->cur==EOF)
                break;
            id+=this->cur;
            this->cur=getNext();   
        }

        return id;
    }

    std::unique_ptr<Viretoken> gatherNum()
    {
        std::string numstr;
        char type=0; // 0=int, 1=float, 2=double

        do
        {
            numstr+=this->cur;
            this->cur=getNext();

            if(this->cur=='.' && type==0)
                type=1;
            else if(this->cur=='.' && type==1)
                LogExc("Invalid float, has 2 decimal points");
                
        } while (isdigit(this->cur) || this->cur=='.');
        
        int ttype=0;
        if(type==0)
            ttype=tok_int;
        else if(type==1)
            ttype=tok_float;
        else if(type==2)
            ttype=tok_double;

        return nomove_makeToken(numstr,ttype);
    }

    std::unique_ptr<Viretoken> gatherStr()
    {
        std::string str="";
        this->cur=getNext(); // consume the start d-quote

        while(this->cur!='\"' && this->cur!=EOF)
        {
            str+=this->cur;
            this->cur=getNext();
        }

        this->cur=getNext(); // consume the end d-quote

        auto tok=std::make_unique<Viretoken>(str.c_str(),tok_str);
        return std::move(tok);
    }

    std::unique_ptr<Viretoken> nomove_makeToken(std::string value, int type)
    {
        auto tok=std::make_unique<Viretoken>(value,type);
        return std::move(tok);
    }

    std::unique_ptr<Viretoken> makeToken(std::string value, int type, char move=0)
    {
        this->cur=this->getNext(move);
        auto tok=this->nomove_makeToken(value,type);

        return std::move(tok);
    }

    std::unique_ptr<Viretoken> makeToken(const char* value, int type, char move=0)
    {
        this->cur=this->getNext(move);
        auto tok=this->nomove_makeToken(std::string(value),type);

        return std::move(tok);
    }

    std::unique_ptr<Viretoken> getToken()
    {
        while(isspace(this->cur))
            this->cur=getNext();
        
        // Checks
        if(isalpha(this->cur))
        {
            auto id_str=gatherId();
            int toktype=0;
            std::unique_ptr<Viretoken> tok;

            if(id_str=="func")
            {
                toktype=tok_func;
            }
            else if(id_str=="var")
            {
                toktype=tok_vardef;
            }
            else if(id_str=="let")
            {
                toktype=tok_let;
            }
            else if(id_str=="const")
            {
                toktype=tok_const;
            }
            else if(id_str=="new")
            {
                toktype=tok_new;
            }
            else if(id_str=="delete")
            {
                toktype=tok_delete;
            }
            else if(id_str=="class")
            {
                toktype=tok_class;
            }
            else if(id_str=="union")
            {
                toktype=tok_union;
            }
            else if(id_str=="struct")
            {
                toktype=tok_struct;
            }
            else if(id_str=="extern")
            {
                toktype=tok_extern;
            }
            else if(id_str=="for")
            {
                toktype=tok_for;
            }
            else if(id_str=="while")
            {
                toktype=tok_while;
            }
            else if(id_str=="return")
            {
                toktype=tok_return;
            }
            else if(id_str=="break")
            {
                toktype=tok_break;
            }
            else if(id_str=="continue")
            {
                toktype=tok_continue;
            }
            else if(id_str=="returns")
            {
                toktype=tok_returns;
            }
            else if(id_str=="proto")
            {
                toktype=tok_proto;
            }
            else if(id_str=="extends")
            {
                toktype=tok_extends;
            }
            else if(id_str=="try")
            {
                toktype=tok_try;
            }
            else if(id_str=="catch")
            {
                toktype=tok_catch;
            }
            else if(id_str=="except")
            {
                toktype=tok_catch;
            }
            else if(id_str=="unsafe")
            {
                toktype=tok_unsafe;
            }
            else
            {
                toktype=tok_id;
            }

            tok=nomove_makeToken(id_str.c_str(),toktype);
            return std::move(tok);
        }

        if(isdigit(this->cur))
            return gatherNum();

        char peek=peekNext((char)1);

        switch(this->cur)
        {
            case ';': return makeToken(";",tok_semicol);

            case '{': return makeToken("{",tok_lbrace);
            case '}': return makeToken("}",tok_rbrace);
            case '[': return makeToken("[",tok_lbrack);
            case ']': return makeToken("]",tok_rbrack);
            case '(': return makeToken("(",tok_lparen);
            case ')': return makeToken(")",tok_rparen);
            case ':': return makeToken(":",tok_colon);
            case ',': return makeToken(",",tok_comma);

            case '=': {
                if(peek=='=') return makeToken("==",tok_dequal,1);
                return makeToken("=",tok_equal);
            }

            case '+': {
                if(peek=='+') return makeToken("++",tok_incr,1);
                return makeToken("+",tok_plus);
            }

            case '-': {
                if(peek=='-') return makeToken("--",tok_decr,1);
                else if(peek=='>') return makeToken("->",tok_rarrow,1);
                return makeToken("-",tok_minus);
            }

            case '*': return makeToken("*",tok_mul);
            case '/': return makeToken("/",tok_div);
            case '%': return makeToken("%",tok_mod);

            case '|': {
                if(peek=='|') return makeToken("||",tok_or,1);
                return nullptr;
            }

            case '&': {
                if(peek=='&') return makeToken("&&",tok_and,1);
                return makeToken("&",tok_reference);
            }

            case '<':{
                if(peek=='=')   return makeToken("<=",tok_lesseq,1);
                return makeToken("<",tok_lessthan);
            }
            case '>':{
                if(peek=='=')   return makeToken(">=",tok_moreeq,1);
                return makeToken(">",tok_morethan);
            }

            case '.': return makeToken(".",tok_dot);

            case '"': return gatherStr();

            case EOF: return makeToken("",tok_eof);

            default: std::cout << "Unknown character: " << this->cur << std::endl; return nullptr;
        }
    }
    std::unique_ptr<Viretoken> getToken(std::string str)
    {
        auto old_str=code;
        code=str;
        auto tkn=getToken();
        old_str=code;
        return std::move(tkn);
    }
};

}