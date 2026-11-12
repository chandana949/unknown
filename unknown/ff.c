#include <stdio.h>
#include <string.h>
#include <ctype.h>
char p[20][20], first[26][20], follow[26][20];
int n;
void add(char *s, char c)
{
    if(!strchr(s, c))
    {
        int l = strlen(s);
        s[l] = c;
        s[l+1] = '\0';
    }
}
void FIRST(char c)
{
    if(!isupper(c))
    {
        add(first[c-'A'], c);
        return;
    }
    for(int i = 0; i < n; i++)
        if(p[i][0] == c)
        {
            char *r = strchr(p[i], '>') + 1;
            for(int j = 0; r[j]; j++)
            {
                if(r[j] == '#')
                {
                    add(first[c-'A'], '#');
                    break;
                }

                FIRST(r[j]);

                char *f = first[r[j]-'A'];

                for(int k = 0; f[k]; k++)
                    if(f[k] != '#')
                        add(first[c-'A'], f[k]);

                if(!strchr(f, '#'))
                    break;

                if(!r[j+1])
                    add(first[c-'A'], '#');
            }
        }
}
void FOLLOW(char c)
{
    if(c == p[0][0])
        add(follow[c-'A'], '$');

    for(int i = 0; i < n; i++)
    {
        char *r = strchr(p[i], '>') + 1;

        for(int j = 0; r[j]; j++)
            if(r[j] == c)
            {
                int k = j + 1;

                while(r[k])
                {
                    char x = r[k];

                    if(!isupper(x))
                    {
                        if(x != '#')
                            add(follow[c-'A'], x);
                        break;
                    }

                    char *f = first[x-'A'];

                    for(int t = 0; f[t]; t++)
                        if(f[t] != '#')
                            add(follow[c-'A'], f[t]);

                    if(!strchr(f, '#'))
                        break;

                    k++;
                }

                if(!r[k] && p[i][0] != c)
                {
                    FOLLOW(p[i][0]);

                    char *f = follow[p[i][0]-'A'];

                    for(int t = 0; f[t]; t++)
                        add(follow[c-'A'], f[t]);
                }
            }
    }
}

void printSet(char *s)
{
    printf("{");

    for(int i = 0; s[i]; i++)
    {
        if(i > 0)
            printf(",");

        printf("%c", s[i]);
    }

    printf("}");
}

int main()
{
    
    scanf("%d", &n);


    for(int i = 0; i < n; i++)
        scanf("%19s", p[i]);

    for(int i = 0; i < n; i++)
        FIRST(p[i][0]);

    for(int i = 0; i < n; i++)
        FOLLOW(p[i][0]);

    int printed[26] = {0};

    printf("\nFIRST and FOLLOW sets:\n");

    for(int i = 0; i < n; i++)
    {
        char c = p[i][0];

        if(!printed[c-'A'])
        {
            printf("\nFIRST(%c) = ", c);
            printSet(first[c-'A']);

            printf("\nFOLLOW(%c) = ", c);
            printSet(follow[c-'A']);

            printf("\n");
            printed[c-'A'] = 1;
        }
    }

    return 0;
}


4
S->AB
A->a
B->b
B->#