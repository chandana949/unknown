#include <stdio.h>
#include <string.h>
int main()
{
    char s[100], v[100][20], op[100], temp[20], dest;
    int i, n=0, k=0, t=1, p;

    scanf("%s", s);
    dest = s[0];

    for(i=2; s[i]; i++)
        if(strchr("+-*/",s[i]))
            op[k++] = s[i];
        else {
            v[n][0] = s[i];
            v[n++][1] = '\0';
        }

    while(k) {
        for(p=0; p<k; p++)
            if(op[p]=='*' || op[p]=='/') break;
        if(p==k) p=0;

        sprintf(temp,"t%d",t++);
        printf("%s=%s%c%s\n",temp,v[p],op[p],v[p+1]);
        strcpy(v[p],temp);

        for(i=p; i<k-1; i++) op[i]=op[i+1];
        for(i=p+1; i<n-1; i++) strcpy(v[i],v[i+1]);

        n--; k--;
    }

    printf("%c=%s\n",dest,v[0]);
    return 0;
}