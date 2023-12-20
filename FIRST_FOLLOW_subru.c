
//ALGORITHM
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//1. General Data Structure and Functions:
int n, m = 0, p, i = 0, j = 0;
char a[10][10], f[10];
void follow(char c);
void first(char c);
void only_first(char c);
int main()
{

    int i, z;
    char c, ch;
    //2. Entering the number of Productions-->n
    printf("Enter the no of productions:\n");
    scanf("%d", &n);
    //3. Scanning the productions --> a[][]
    printf("Enter the productions:\n");
    for (i = 0; i < n; i++)
        scanf("%s%c", a[i], &ch);
    
    //4. DO WHILE LOOP --> till 
    do
    {
        m = 0;
        printf("Enter the elemets whose fisrt & follow is to be found:");
        scanf("%c", &c);
        only_first(c);
        printf("First(%c)={", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");
        strcpy(f, " ");
        m = 0;
        follow(c);
        printf("Follow(%c)={", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");
        printf("Continue(0/1)?");
        scanf("%d%c", &z, &ch);
    } while (z == 1);
    return (0);
}
void first(char c) //I. FIRST FUNCTION LOGIC
{
    int k;
    if (!isupper(c)) //a. if read character is not uppercase(NON terminal)
        f[m++] = c;// directly added to first set.
    for (k = 0; k < n; k++) // iterating through the productions starting with c (NON-T)
    {
        // printf("\nProduction: %s\n", a[k]);
        if (a[k][0] == c)//if found
        {
            if (a[k][2] == '$')//if it is an epsilon --> find follow of LHS
                follow(a[k][0]);
            else if (islower(a[k][2]))//if terminal
                f[m++] = a[k][2];
            else
                first(a[k][2]);//finding first of the NON-Terminal
        }
    }
}
void only_first(char c) //I. FIRST FUNCTION LOGIC
{
    int k;
    if (!isupper(c)) //a. if read character is not uppercase(NON terminal)
        f[m++] = c;// directly added to first set.
    for (k = 0; k < n; k++) // iterating through the productions starting with c (NON-T)
    {
        // printf("\nProduction: %s\n", a[k]);
        if (a[k][0] == c)//if found
        {
            if (a[k][2] == '$')//if it is an epsilon
                f[m++]='$';
            else if (islower(a[k][2]))//if terminal
                f[m++] = a[k][2];
            else
                first(a[k][2]);//finding first of the NON-Terminal
        }
    }
}
void follow(char c)
{
    if (a[0][0] == c)// if the read character is the start
        f[m++] = '$';
    for (i = 0; i < n; i++)
    {
        for (j = 2; j < strlen(a[i]); j++)//starting from the right symbol
        {
            if (a[i][j] == c)//if match
            {
                if (a[i][j + 1] != '\0')//if single character
                    first(a[i][j + 1]);
                if (a[i][j + 1] == '\0' && c != a[i][0])
                    follow(a[i][0]);
            }
        }
    }
}
/*
input:
S=AB
A=a|$
B=b|$

output:
Enter the no of productions:
3
Enter the productions:
S=AB
A=a|$
B=b|$
Enter the elemets whose fisrt & follow is to be found:A
First(A)={a}
Follow(A)={b}
Continue(0/1)?1
Enter the elemets whose fisrt & follow is to be found:S
First(S)={a}
Follow(S)={$}
Continue(0/1)?1
Enter the elemets whose fisrt & follow is to be found:B
First(B)={b}
Follow(B)={$}
Continue(0/1)?0
*/
