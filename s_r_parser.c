//PROGRAM NAME: SHIFT REDUCE PARSER
// AUTHOR NAME: Tapasvi Amruthalal
//     ROLL NO: 261
/**
 * ALGORITHM:
1. Initialising all the DS
2.initialising the stack string with null character. Necessary to make it a string... to use strcat()[NOTE]
3. User input for the number of production rules
4. User input for each production rule in the form 'left->right'
5. User input for the input string
6.If there are more characters in the input string than the stack, add the next character to the stack..SHIFT
7. Check for reductions by iterating through the production rules. REDUCTION
8. Check if the stack contains only the start symbol and if the entire input string has been processed ACCEPTED
9. Check if the entire input string has been processed but the stack doesn't match the start symbol ERROR
10. Repeat step tilll end of input string and it is accepted.
 * STRUCTURE:
 * 1. structure for production rule: character string for left and right--> object: rules[10]
 * 2. char Arrays
 *      a. input array
 *      b. stack array --> need to made into string using '\0'
 *      c. temp array --> to break rules into left and right
 *      d. ch character string --> string to store a character ending with '\0'
 * 3. char string pointers
 *      *token1
 *      *token2
 *      *substring--> to match for the stack contents in right side of productions usinf strstr()
 * 4. Iterators: i--> to move through stack
 *               j--> local
 *              stack_length--> used while replacing the RHS of production in stack with LHS
 *              substring_length--> used while replacing the RHS of production in stack with LHS
 *              stack_top--> to find the value where the stack is cut off only leaving everything except handle
 *              
 * 
 * 
 *  FUNCTIONS:
 * ONLY MAIN FUNCTION
 * 
 * 
 * KEY.FUNCTIONS.TO.REMEMBER:
 * strstr()
 * strtok
*/
#include <stdio.h>
#include <string.h>

struct ProductionRule
{
    char left[10];
    char right[10];
};

int main()
{
    //1. Initialising all the DS
    char input[20], stack[50], temp[50], ch[2], *token1, *token2, *substring;
    int i, j, stack_length, substring_length, stack_top, rule_count = 0;
    struct ProductionRule rules[10];//DS for productions

    stack[0] = '\0';//2.initialising the stack string with null character. Necessary to make it a string... to use strcat()[NOTE]

    // 3. User input for the number of production rules
    printf("\nEnter the number of production rules: ");
    scanf("%d", &rule_count);

    // 4. User input for each production rule in the form 'left->right'
    printf("\nEnter the production rules (in the form 'left->right'): \n");
    for (i = 0; i < rule_count; i++)//splitting the production 
                                    //rules into left and right token.
    {
        scanf("%s", temp);
        token1 = strtok(temp, "->");//strtok(string, "splitting character")
        token2 = strtok(NULL, "->");
        strcpy(rules[i].left, token1);
        strcpy(rules[i].right, token2);
    }

    //5. User input for the input string
    printf("\nEnter the input string: ");
    scanf("%s", input);

    i = 0;// intitialising i--> 
    // (I) The WHILE LOOP 
    while (1)
    {
        // 6.If there are more characters in the input string, 
        //add the next character to the stack
        if (i < strlen(input))// to ensure no more shift if all of input read
        {
            ch[0] = input[i];//taking the first character and using it as a string
            ch[1] = '\0';
            i++;// incrementing character count
            strcat(stack, ch);//concatenating with the stack
            printf("%s\t", stack);
            for (int k = i; k < strlen(input); k++)//to print the remaining input string.
            {
                printf("%c", input[k]);
            }
            printf("\tShift %s\n", ch); //Shift operation is the action.
        }
        
        // 7. to check for reductions by iterating through the production rules
        for (j = 0; j < rule_count; j++)
        {
            // Check if the right-hand side of the production 
            //rule matches a substring in the stack
            substring = strstr(stack, rules[j].right);
            if (substring != NULL)// if match found
            {
                // Replace the matched substring with the left-hand
                // side of the production rule
                stack_length = strlen(stack);//get pointer 
                substring_length = strlen(substring);
                stack_top = stack_length - substring_length;
                stack[stack_top] = '\0';
                strcat(stack, rules[j].left);
                printf("%s\t", stack);

                /**
                 * If a match is found:

                The code computes the position (stack_top) where the matched substring starts in the stack.
                It then truncates the stack at that position using '\0' (null terminator) effectively removing the matched substring.
                Finally, the left-hand side of the production rule (rules[j].left) is appended to the stack using strcat().
                */
                for (int k = i; k < strlen(input); k++)
                {
                    printf("%c", input[k]);
                }
                printf("\tReduce %s->%s\n", rules[j].left, rules[j].right);
                j = -1; // Restart the loop to ensure immediate 
                        //reduction of the newly derived production rule
            }
        }

        // 8. Check if the stack contains only the start symbol and 
        //if the entire input string has been processed
        if (strcmp(stack, rules[0].left) == 0 && i == strlen(input))
        {
            printf("\nAccepted");
            break;  
        }

        // 9. Check if the entire input string has been processed but
        // the stack doesn't match the start symbol
        if (i == strlen(input))
        {
            printf("\nNot Accepted");
            break;
        }
        //moving to nect iteration for nect character of reductions
    }

    return 0;
}


/*

OUTPUT

Enter the number of production rules: 4

Enter the production rules (in the form 'left->right'): 
E->E+E
E->E*E
E->(E)
E->i 

Enter the input string: i*i+i
i	*i+i	Shift i
E	*i+i	Reduce E->i
E*	i+i	Shift *
E*i	+i	Shift i
E*E	+i	Reduce E->i
E	+i	Reduce E->E*E
E+	i	Shift +
E+i		Shift i
E+E		Reduce E->i
E		Reduce E->E+E

Accepted




*/

