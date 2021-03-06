#pragma once

#include "vire/parse/include.hpp"
#include "vire/ast/include.hpp"
#include "vire/errors/include.hpp"

namespace vire
{

class VAnalyzer
{
    // Symbol Tables
    std::unique_ptr<CodeAST> codeast;

    FunctionAST* current_func;

    // Error Builder
    errors::ErrorBuilder* const& builder;

    // Source Code
    std::string code;

    // Scope Stack
    std::map<std::string, VariableDefAST*> scope;

    // Functions
    void addVar(VariableDefAST* const& var);
    void removeVar(VariableDefAST* const& var);
    void addFunction(std::unique_ptr<FunctionBaseAST> func);
    void addClass(std::unique_ptr<ClassAST> class_);
    bool isVarDefined(std::string const& name, bool check_globally_only=false);

    VariableDefAST* const getVar(std::string const& name);
public:
    VAnalyzer(errors::ErrorBuilder* const& builder, std::string const& code="")
    : builder(builder), code(code) {}

    errors::ErrorBuilder* const getErrorBuilder() const { return builder; }

    bool isStructDefined(std::string const& name);
    bool isUnionDefined(std::string const& name);
    bool isClassDefined(std::string const& name);
    bool isFuncDefined(std::string const& name);
    bool isStdFunc(std::string const& name);
    unsigned int getFuncArgCount(std::string const& name);

    types::Base getType(ExprAST* const& expr);
    types::Base getType(ArrayExprAST* const& arr);

    FunctionBaseAST* const getFunc(const std::string& name);
    types::Base getFuncReturnType(const std::string& name="");

    CodeAST* const getCode();

    // Verification functions

    ReturnExprAST* const getReturnStatement(std::vector<std::unique_ptr<ExprAST>> const& block);

    bool verifyVar(VariableExprAST* const& var);
    bool verifyIncrDecr(VariableIncrDecrAST* const& var);
    bool verifyVarDef(VariableDefAST* const& var, bool check_globally_only=false);
    bool verifyTypedVar(TypedVarAST* const& var);
    bool verifyVarAssign(VariableAssignAST* const& var);

    // Constant/Literal verification due to overflows and invalid escape sequences
    bool verifyInt(IntExprAST* const& int_); 
    bool verifyFloat(FloatExprAST* const& float_);
    bool verifyDouble(DoubleExprAST* const& double_);
    bool verifyChar(CharExprAST* const& char_);
    bool verifyStr(StrExprAST* const& str);
    bool verifyArray(ArrayExprAST* const& array);
    
    // Loop verifications
    bool verifyFor(ForExprAST* const& for_);
    bool verifyWhile(WhileExprAST* const& while_);
    bool verifyBreak(BreakExprAST* const& break_); // verification needed for break execution statement
    bool verifyContinue(ContinueExprAST* const& continue_); // verification needed for continue execution statements
    
    // Function verifications
    bool verifyCall(CallExprAST* const& call);
    bool verifyPrototype(PrototypeAST* const& proto);
    bool verifyProto(PrototypeAST* const& proto);
    bool verifyExtern(ExternAST* const& extern_);
    bool verifyFunction(FunctionAST* const& func);
    bool verifyReturn(ReturnExprAST* const& return_);

    // Operator verifications
    bool verifyUnop(UnaryExprAST* const& unop);
    bool verifyBinop(BinaryExprAST* const& binop);

    // Class verifications
    bool verifyClass(ClassAST* const& class_);
    bool verifyNew(NewExprAST* const& new_);
    bool verifyDelete(DeleteExprAST const& delete_);

    // Struct/Union verifications
    bool verifyUnionStructBody(std::vector<std::unique_ptr<ExprAST>> const& body);
    bool verifyUnion(UnionExprAST* const& union_);
    bool verifyStruct(StructExprAST* const& struct_);

    // If-Else verifications
    bool verifyIfThen(IfThenExpr* const& if_);
    bool verifyIf(IfExprAST* const& if_);

    // Memory-related verifications
    bool verifyUnsafe(UnsafeExprAST* const& unsafe);
    bool verifyReference(ReferenceExprAST* const& reference);

    // Block verifications
    bool verifyBlock(std::vector<std::unique_ptr<ExprAST>> const& block);

    // Entry point for verification
    bool verifyCode(std::unique_ptr<CodeAST> code);

    // Helper functions
    bool verifyExpr(ExprAST* const& expr);

    std::vector<std::string> getErrors();
};

}