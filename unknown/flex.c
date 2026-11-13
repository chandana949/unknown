
%option noyywrap

%{
#include <stdio.h>
%}

%%

"int"|"float"|"char"|"if"|"else"|"for"|"while"|"return" {
    printf("KEYWORD : %s\n",yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("IDENTIFIER : %s\n",yytext);
}

[0-9]+ {
    printf("CONSTANT : %s\n",yytext);
}

"//".* {
    printf("COMMENT\n");
}

\"[^\"]*\" {
    printf("STRING : %s\n",yytext);
}

\'[^']\' {
    printf("CHARACTER : %s\n",yytext);
}

"=="|"!="|"<="|">="|"<"|">" {
    printf("RELATIONAL : %s\n",yytext);
}

"=" {
    printf("ASSIGNMENT : %s\n",yytext);
}

"++"|"--"|"+="|"-="|"+"|"-"|"*"|"/"|"%" {
    printf("ARITHMETIC : %s\n",yytext);
}

"&&"|"||" {
    printf("LOGICAL : %s\n",yytext);
}

"("|")"|"{"|"}"|"["|"]"|","|";"|":" {
    printf("SEPARATOR : %s\n",yytext);
}

[ \t\n]+ { }

. {
    printf("INVALID : %s\n",yytext);
}

%%

int main()
{
    yylex();
    return 0;
}



sudo dnf install flex gcc vim -y
mkdir week2
cd week2
vi lexer.l
i
ctrl shift v
esc
:wq
enter
ls
flex filename.l
ls
gcc lex.yy.c -ll
ls
./a.out
