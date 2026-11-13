#include <stdio.h>
#include <string.h>
#include <ctype.h>

char lhs[20], rhs[20][20];
char first[26][20], follow[26][20];
int n;

void add(char *s, char c)
{
    if (!strchr(s, c))
    {
        int l = strlen(s);
        s[l] = c;
        s[l+1] = '\0';
    }
}

void FIRST(char c)
{
    if (!isupper(c))
    {
        add(first[c-'A'], c);
        return;
    }

    for (int i = 0; i < n; i++)
        if (lhs[i] == c)
        {
            if (rhs[i][0] == '#')
                add(first[c-'A'], '#');
            else
                for (int j = 0; rhs[i][j]; j++)
                {
                    char x = rhs[i][j];
                    FIRST(x);
                    for (int k = 0; first[x-'A'][k]; k++)
                        if (first[x-'A'][k] != '#')
                            add(first[c-'A'], first[x-'A'][k]);

                    if (!strchr(first[x-'A'], '#'))
                        break;

                    if (!rhs[i][j+1])
                        add(first[c-'A'], '#');
                }
        }
}

void FOLLOW(char c)
{
    if (c == lhs[0])
        add(follow[c-'A'], '$');

    for (int i = 0; i < n; i++)
        for (int j = 0; rhs[i][j]; j++)
            if (rhs[i][j] == c)
            {
                if (rhs[i][j+1])
                {
                    char x = rhs[i][j+1];
                    FIRST(x);

                    for (int k = 0; first[x-'A'][k]; k++)
                        if (first[x-'A'][k] != '#')
                            add(follow[c-'A'], first[x-'A'][k]);

                    if (strchr(first[x-'A'], '#'))
                        FOLLOW(lhs[i]);
                }
                else if (lhs[i] != c)
                    FOLLOW(lhs[i]);
            }
}

int main()
{
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (A=BC):\n");
    for (int i = 0; i < n; i++)
        scanf("%s", &lhs[i]), scanf("%*c%s", rhs[i]);
    for (int i = 0; i < n; i++)
        FIRST(lhs[i]);
    for (int i = 0; i < n; i++)
        FOLLOW(lhs[i]);
    for (int i = 0; i < n; i++)
        printf("FIRST(%c) = {%s}\n", lhs[i], first[lhs[i]-'A']);
    printf("\n");
    for (int i = 0; i < n; i++)
        printf("FOLLOW(%c) = {%s}\n", lhs[i], follow[lhs[i]-'A']);
    return 0;
}