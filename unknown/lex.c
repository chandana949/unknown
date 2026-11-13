#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *f=fopen("input.txt","r");
    char c,n,s[100],*kw[]={"int","float","char","double","if","else","for","while","return","void"};
    int i,k;

    if(!f) { printf("File not found!"); return 1; }

    while((c=fgetc(f))!=EOF)
    {
        if(isalpha(c)||c=='_')
        {
            i=0;
            do { s[i++]=c; c=fgetc(f); } while(isalnum(c)||c=='_');
            s[i]=0; k=0;
            for(i=0;i<10;i++) if(!strcmp(s,kw[i])) k=1;
            printf("%s : %s\n",k?"KEYWORD":"IDENTIFIER",s);
            if(c!=EOF) ungetc(c,f);
        }
        else if(isdigit(c))
        {
            i=0;
            do { s[i++]=c; c=fgetc(f); } while(isdigit(c));
            s[i]=0;
            printf("CONSTANT : %s\n",s);
            if(c!=EOF) ungetc(c,f);
        }
        else if(c=='/')
        {
            n=fgetc(f);
            if(n=='/') while((c=fgetc(f))!=EOF&&c!='\n');
            else if(n=='*')
            {
                char p=0;
                while((c=fgetc(f))!=EOF)
                { if(p=='*'&&c=='/') break; p=c; }
            }
            else { if(n!=EOF) ungetc(n,f); printf("DIVISION : /\n"); }
        }
        else if(c=='"'||c=='\'')
        {
            char q=c;
            i=0; s[i++]=c;
            while((c=fgetc(f))!=EOF)
            {
                s[i++]=c;
                if(c==q) break;
            }
            s[i]=0;
            printf("%s : %s\n",q=='"'?"STRING":"CHARACTER",s);
        }
        else if(strchr("=!<>",c))
        {
            n=fgetc(f);
            if(n=='=') printf("RELATIONAL : %c%c\n",c,n);
            else
            {
                if(n!=EOF) ungetc(n,f);
                printf("%s : %c\n",c=='='?"ASSIGNMENT":"RELATIONAL",c);
            }
        }
        else if(strchr("+-*%",c))
        {
            n=fgetc(f);
            if(n==c||n=='=') printf("ARITHMETIC : %c%c\n",c,n);
            else
            {
                if(n!=EOF) ungetc(n,f);
                printf("ARITHMETIC : %c\n",c);
            }
        }
        else if(c=='&'||c=='|')
        {
            n=fgetc(f);
            if(n==c) printf("LOGICAL : %c%c\n",c,n);
            else
            {
                if(n!=EOF) ungetc(n,f);
                printf("INVALID OPERATOR : %c\n",c);
            }
        }
        else if(strchr("(){}[],;:",c))
            printf("SEPARATOR : %c\n",c);
        else if(!isspace(c))
            printf("INVALID : %c\n",c);
    }

    fclose(f);
    return 0;
}

int main()
{
    int a = 10;
    if(a >= 5)
        a = a + 1;
    return 0;
}
