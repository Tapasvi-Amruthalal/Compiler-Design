/**
 * Algorithm
 * 
 * 
 * 
 * 
 * 
 * STRUCTURES:
 *  NO DS as everything is vased on recursion with stack based function calls
 * 
 * FUNCTIONS
*/


#include <stdio.h>  
#include <string.h>  
  
#define SUCCESS 1  
#define FAILED 0  
  
int E(), Edash(), T(), Tdash(), F();  
  
const char *cursor;  
char string[64];  
  
int main()  
{   
    //1. input the string
    printf("Enter the string");  
    scanf("%s", string); 
    //2. Grammar definition 
    printf("Grammar is :\n");
    printf("E->TE'|$\n");
    printf("T->FT'\n");
    printf("T'->*FT'|$\n");
    printf("F->id|(E)\n");
    //sscanf("i+(i+i)*i", "%s", string);  
    cursor = string;  //3. Initialisin the cursor pointer to start of string
    printf("");  
    printf("Input      Action");  
    printf("\n--------------------------------\n");  
    //4. First symbol called inside a function and checked if cursor at end of string.
    if (E() && *cursor == '\0') {  
        printf("\n--------------------------------\n");  
        printf("String is successfully parsed\n");  
        return 0;  
    } else {  
        printf("\n--------------------------------\n");  
        printf("Error in parsing String\n");  
        return 1;  
    }  
}  
  
int E()  //E not-T
{  
    printf("%-16s E -> T E'\n", cursor);  //printing to show which production is descended
    if (T()) {  //NON-T 
        if (Edash())  // nested if because of the appended non-T
            return SUCCESS;  
        else  
            return FAILED;  
    } else  
        return FAILED;  
}  
  
int Edash()  
{  
    if (*cursor == '+') {  //checking cursor value for nont
        printf("%-16s E' -> + T E'\n", cursor);  //since it is the value production is used to reduce
        cursor++;  
        if (T()) {  
            if (Edash())  
                return SUCCESS;  
            else  
                return FAILED;  
        } else  
            return FAILED;  
    } else {  
        printf("%-16s E' -> $\n", cursor);  // since its a combined production rule with epsilon case
        return SUCCESS;  
    }  
}  
  
int T()  
{  
    printf("%-16s T -> F T'\n", cursor);  
    if (F()) {  
        if (Tdash())  
            return SUCCESS;  
        else  
            return FAILED;  
    } else  
        return FAILED;  
}  
  
int Tdash()  
{  
    if (*cursor == '*') {  
        printf("%-16s T' -> * F T'\n", cursor);  
        cursor++;  
        if (F()) {  
            if (Tdash())  
                return SUCCESS;  
            else  
                return FAILED;  
        } else  
            return FAILED;  
    } else {  
        printf("%-16s T' -> $\n", cursor);  
        return SUCCESS;  
    }  
}  
  
int F()  
{  
    if (*cursor == '(') {  
        printf("%-16s F -> ( E )\n", cursor);  
        cursor++;  
        if (E()) {  
            if (*cursor == ')') {  
                cursor++;  
                return SUCCESS;  
            } else  
                return FAILED;  
        } else  
            return FAILED;  
    } else if (*cursor == 'i') {  
        cursor++;  
        printf("%-16s F ->i\n", cursor);  
        return SUCCESS;  
    } else  
        return FAILED;  
}  