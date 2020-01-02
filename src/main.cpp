#include <iostream>
#include "AST.h"
extern ASTGoal* programBlock;
extern int yyparse();

int main(int argc, char **argv)
{
    yyparse();
    std::cout << programBlock << std::endl;
    return 0;
}
