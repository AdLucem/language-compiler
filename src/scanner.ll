%{
    #include <cstdlib>
    #include <iostream>

    #include "AST.h"
    #include "dcc.tab.h"

    #define YY_DECL extern "C" int yylex()
%}

%option nounput
%option noyywrap
%option yylineno

%%

[\"][[:alnum:][:punct:][:blank:]]*[\"]    { 
    return STRING; 
}

[ \t\r]    { 
    /* eat white spaces */  
}

"int"|"uint"|"char"|"string"|"bool"|"array"|"matrix"    { 
    return TYPE; 
}

"+"|"-"|"*"|"/"|"||"|"++"|"=="|"%"    { 
    return OPERATOR; 
}

"="|"+="|"-="    { 
    return ASSIGNMENT; 
}

[0-9]+    {
    return NUMBER; 
}

[a-zA-Z][a-zA-Z0-9\_]*    {
    return NAME;
}

[\{]    { 
    return LBRACE;
}

[\}]    {
    return RBRACE;
}

[\(]    {
    return LBRACKET;
}

[\)]    {
    return RBRACKET;
}

[\[]    {
    return LSQBRACE;
}

[\]]    {
    return RSQBRACE;
}

\n    { 
    ++lineno; 
}

.    {
    printf("Line No %d: Unrecognized character '%c'\n", lineno, yytext[0]);
}

%%