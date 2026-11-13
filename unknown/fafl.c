#include <stdio.h>
#include <string.h>
#include <ctype.h>

char l[20], r[20][20], f[26][20], g[26][20];
int n;

int add(char *s, char c)
{
    if (!strchr(s,c))
    {
        int k=strlen(s);
        s[k]=c; s[k+1]='\0';
        return 1;
    }
    return 0;
}

void FIRST(char c)
{
    if (!isupper(c)) { add(f[c-'A'],c); return; }

    for(int i=0;i<n;i++) if(l[i]==c)
    {
        int j;
        for(j=0;r[i][j];j++)
        {
            char x=r[i][j];
            if(x=='#') { add(f[c-'A'],'#'); break; }

            FIRST(x);
            for(int k=0;f[x-'A'][k];k++)
                if(f[x-'A'][k]!='#') add(f[c-'A'],f[x-'A'][k]);

            if(!strchr(f[x-'A'],'#')) break;
        }
        if(!r[i][j]) add(f[c-'A'],'#');
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf(" %c=%s",&l[i],r[i]);

    for(int i=0;i<n;i++) FIRST(l[i]);

    add(g[l[0]-'A'],'$');

    int ch;
    do {
        ch=0;
        for(int i=0;i<n;i++)
            for(int j=0;r[i][j];j++) if(isupper(r[i][j]))
            {
                char B=r[i][j];
                int k;
                for(k=j+1;r[i][k];k++)
                {
                    char x=r[i][k];
                    if(!isupper(x))
                    {
                        ch|=add(g[B-'A'],x);
                        break;
                    }
                    for(int t=0;f[x-'A'][t];t++)
                        if(f[x-'A'][t]!='#')
                            ch|=add(g[B-'A'],f[x-'A'][t]);

                    if(!strchr(f[x-'A'],'#')) break;
                }
                if(!r[i][k])
                    for(int t=0;g[l[i]-'A'][t];t++)
                        ch|=add(g[B-'A'],g[l[i]-'A'][t]);
            }
    } while(ch);

    int seen[26]={0};

    for(int i=0;i<n;i++)
        if(!seen[l[i]-'A'])
        {
            seen[l[i]-'A']=1;
            printf("FIRST(%c) = { %s }\n",l[i],f[l[i]-'A']);
        }

    printf("\n");
    memset(seen,0,sizeof(seen));

    for(int i=0;i<n;i++)
        if(!seen[l[i]-'A'])
        {
            seen[l[i]-'A']=1;
            printf("FOLLOW(%c) = { %s }\n",l[i],g[l[i]-'A']);
        }

    return 0;
}