#pragma once

namespace vire
{
enum asttype
{
    ast_code,
    ast_var,
    ast_vardef,
    ast_varassign,

    ast_for,
    ast_while,
    
    ast_int,
    ast_float,
    ast_double,
    ast_char,
    ast_str,

    ast_call,
    ast_proto,
    ast_extern,
    ast_function,

    ast_unop,
    ast_binop,

    ast_class,

    ast_union,
    ast_typedvar,
    ast_struct,

    ast_return,
    ast_break,
    ast_continue,

    ast_if,
    ast_ifelse,

    ast_new,
    ast_delete,
    ast_unsafe,
    
    ast_reference,

    ast_try,

    ast_class_access,

    ast_array,

    ast_varincrdecr,
};
}