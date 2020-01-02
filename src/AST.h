#ifndef _AST_H
#define _AST_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


/********** Leaf Nodes ************/
class ASTTypeDecl;
class ASTConstant;
class ASTStringConstant;
class ASTIntegerConstant;
class ASTName;
/********* Combination Nodes ***********/
class ASTExpr;
class ASTUnaryExpr;
class ASTBinaryExpr;
/********* Line-Level Nodes *************/
class ASTLine;
class ASTNameDeclLine;
class ASTAssignmentLine; 
/********* Block-Level Node ************/
class ASTBlock;
/********* Top-Level Node ************/
class ASTGoal;


enum class AssignOp {
    none,
    plus_equal,
    minus_equal,
    equal
};

enum class BinaryOp {
    plus_op,
    minus_op,
    multiply_op,
    divide_op,
    modulo_op,
    lessthan_op,
    greaterthan_op,
    lessequal_op,
    greaterequal_op,
    notequal_op,
    equalequal_op,
    and_op,
    or_op
};

enum class Datatype {
    int_type,
    uint_type,
    char_type,
    string_type,
    bool_type,
    array_type,
    matrix_type
};

enum class UnaryOp {
    minus_op,
    not_op
};

class ASTNode {
public:
    ASTNode() {
    }
    ~ASTNode() {
    }
};

class ASTTypeDecl : public ASTNode
{
    std::string id;
    Datatype type;
    std::vector<ASTConstant> args;
public:
    ASTTypeDecl(std::string id, Datatype type){
        this.id = id;
        this.type = type;
    };
    std::string getId(){
        return this.id;
    };
    Datatype getType(){
        return this.type;
    };
    std::vector<int> getArgs(){
        return this.args;
    };
    ~ASTTypeDecl() {
    };
};

class ASTName : public ASTNode
{
    std::string id;
    std::string name;
public:
    ASTName(std::string id, std::string name){
        this->id = id;
        this->name = name;
    };
    std::string getId(){
        return this->id;
    };
    Datatype getName(){
        return this->name;
    };
    ~ASTName() {
    };
};

/***** Defining constants in our AST *****/

class ASTConstant : public ASTNode
{
public:
    ASTConstant(){
    };
    virtual ~ASTConstant() {
    };
};

class ASTIntegerConstant : public ASTConstant
{
    std::string id;
    int value;
public:
    ASTIntegerConstant(std::string id, int value){
        this->id = id;
        this->value = value;
    };
    std::string getId(){
        return this->id;
    };
    int getValue(){
        return this->value;
    };
    ~ASTIntegerConstant() {};
};

class ASTStringConstant : public ASTConstant
{
    std::string id;
    std::string value;
public:
    ASTStringConstant(std::string id, std::string value){
        this->id = id;
        this->value = value;
    };
    std::string getId(){
        return this->id;
    };
    std::string getValue {
        return this->value;
    };
}

/***** Handling expressions in the AST *****/

class ASTExpr : public ASTNode
{
public:
    ASTExpr(){
    };
    virtual ~ASTExpr() {};
};

class ASTUnaryExpr : public ASTExpr
{
    std::string id;
    UnaryOp op;
    ASTExpr expr;
public:
    ASTUnaryExpr(std::string id, UnaryOp op, ASTExpr expr){
        this->id = id;
        this->op = op;
        this->expr = expr;
    };
    std::string getId(){
        return this->id;
    };
    UnaryOp getOp(){
        return this->op;
    };
    ASTExpr getExpr(){
        return this->expr;
    };
    ~ASTUnaryExpr() {};
};

class ASTBinaryExpr : public ASTExpr
{
    std::string id;
    BinaryOp op;
    ASTExpr lhs;
    ASTExpr rhs;
public:
    ASTBinaryExpr(std::string id, BinaryOp op, ASTExpr lhs, ASTExpr rhs){
        this->id = id;
        this->op = op;
        this->lhs = lhs;
        this->rhs = rhs;
    };
    std::string getId(){
        return this->id;
    };
    BinaryOp getOp(){
        return this->op;
    };
    ASTExpr getLhs(){
        return this->lhs;
    };
    ASTExpr getRhs(){
        return this->rhs;
    };
    ~ASTBinaryExpr() {};
};

/***** Handling lines in the AST *****/

class ASTLine : public ASTNode
{
public:
    ASTLine(){
    };
    virtual ~ASTLine() {};
};

class ASTNameDeclLine : public ASTLine
{
    std::string id;
    ASTTypeDecl typeDecl;
    ASTName name;
public:
    ASTNameDeclLine(std::string id, ASTTypeDecl type_decl, ASTName name){
        this->id = id;
        this->typeDecl = typeDecl;
        this->name = name;
    };
    std::string getId(){
        return this->id;
    };
    ASTTypeDecl getTypeDecl(){
        return this->typeDecl;
    };
    ASTName getName(){
        return this->name;
    };
    ~ASTNameDeclLine() {};
};

class ASTAssignmentLine : public ASTLine
{
    std::string id;
    ASTName name;
    ASTExpr expr;
public:
    ASTAssignmentLine(std::string id, ASTName name, ASTExpr expr){
        this->id = id;
        this->name = name;
        this->expr = expr;
    };
    std::string getId(){
        return this->id;
    }
    ASTName getName(){
        return this->name;
    }
    ASTExpr getExpr(){
        return this->expr;
    }
    ~ASTAssignmentLine() {};
};

/***** Block-Level Nodes *****/

class ASTBlock : public ASTNode
{
    std::string id;
    std::vector<ASTLine* > *lines;
public:
    ASTBlock(std::string id, ASTLine initLine){
        this->id = id;
        this->lines.push_back(initLine);
    };
    std::string getId(){
        return this->id;
    }
    std::vector<ASTLine* > *getLines(){
        return this->lines;
    }
    ~ASTBlock() {};
};

/***** Top-Level Node *****/


class ASTGoal : public ASTNode
{
    std::string id;
    std::vector<ASTBlock* > *blocks;
public:
    ASTBlock(std::string id){
        this->id = id;
    };
    std::string getId(){
        return this->id;
    }
    std::vector<ASTBlock* > getBlocks(){
        return this->blocks;
    }
    ~ASTGoal() {};
};

#endif