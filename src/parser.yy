%{
  #include <iostream>
  #include <string>
  #include <vector>

  #include "AST.h"

  extern "C" FILE * yyin;
  extern "C" int yylex();
  extern "C" int yylineno;
  extern "C" int yyparse();
  
  void yyerror(const char *s);
  extern ASTGoal * programBlock;
%}

%union {
  ASTTypeDecl* typeDecl;
  ASTConstant* constant;
  ASTName* name;
  ASTExpr* expr;
  ASTLine* line;
  ASTBlock* block;
  ASTGoal* goal;
  AssignOp assign;
  Datatype dtype;
  BinaryOp binOp;
  UnaryOp unOp;
}

%token <name> NAME
%token <constant> STRING
%token <constant> NUMBER
%token OPERATOR
%token <assign> ASSIGNMENT
%token <dtype> TYPE
%token LBRACE
%token RBRACE
%token LBRACKET
%token RBRACKET
%token LSQBRACE
%token RSQBRACE


%type <block> Block;
%type <line> Line;
%type <constant> Constant;
%type <expr> Expr;
%type <typeDecl> TypeDecl;
%type <binOp> BinOp;
%type <unOp> UnOp;
%type <goal> Goal;

%%

Goal:     LBRACE Block RBRACE         { programGoal->blocks.push_back( $<block>2 ); }
    |     Goal LBRACE Block RBRACE    { $1->blocks.push_back( $<block>3 ); }
    ;
Block:    Line        { $$ = new ASTBlock( $<line>1 ); }
     |    Block Line  { $1->lines.push_back( $<line>2 ); }
     ;
Line:    TypeDecl NAME               { $$ = new ASTNameDeclLine( $<typeDecl>1, $2 ); }
    |    NAME ASSIGNMENT Expr        { $$ = new ASTAssignmentLine( $<name>1, $<expr>3 );}
    ;
Expr:    Constant        { $$ = new ASTUnaryExpr( none, $<constant>1 )}
    |    LBRACKET OPERATOR Expr RBRACKET    { $$ = new ASTUnaryExpr( $<unOp>2, $<expr>3 ); }
    |    LBRACKET Expr OPERATOR Expr RBRACKET  { $$ = new ASTBinaryExpr( $<binOp>3, $<expr>2, $<expr>4); }
    ;
Constant:    STRING    { $$ = new ASTStringConstant( $1 ); }
        |    NUMBER    { $$ = new ASTIntegerConstant( $1 ); }
        ;
TypeDecl : TYPE    { $$ = new ASTTypeDecl( $1 ); }
         | TYPE Constant { $$ = new ASTTypeDecl( $1 ); $$->args.push_back( $<constant>2 ); }
         | TYPE Constant Constant { $$ = new ASTTypeDecl( $1 ); $$->args.push_back( $<constant>2 ); $$->args.push_back( $<constant>3 ); }
         ;
%%


void yyerror (const char *s) {
  std::cerr << "Parse Error on Line : " << yylineno << std::endl << "Message : " << s << std::endl;
  exit(-1);
}


%%

