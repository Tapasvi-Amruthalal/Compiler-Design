/**
 * ALGORITHM:
 * 1. Decalre the necessary data strcuture and variables including the operatorIndex strcuture.
 * 2. Take the expression input from user.
 * 3. Call findOperator Function
 * 		[I]findOperator():
 * 			1. for loop till end of input string
* 			2. if came across +,-,*,/,% operator then:
* 					- store the operator in operator.op
* 					- store the operatorIndex in operator.pos
 * 4. Call Explore Function:
 * 		[II] Explore():
 * 			1. i=0 and while loop till operator index end is reached
 * 					left=fleft(operator.index)
 * 					right=fright(operator.index)
 * 					replace the operator.pos value with tempch after tempch--
 * 					print the 3AC
 * 					increment the 'i' variable iterating throgh the operators
 * 			2. find left and right of first operator fleft(1), fright(2)
 * 			3. printf("\t%s = %s", left, right
 * 5. End
 * 
 * [III]fleft(index value=x)
 * decrement x--;
 * delete left
 * while str[x] is not an operator, momve left
 * 			if it is not $
 * 			concatenate it to left
 * 			change str[x]to $
 * 			decrement x
 * 			
 * 
 * 
 * [IV]fright
 * DATA:STRUCTURES:
 * operatorIndex structure:: to store the operator index and operator itself
 * j--> global variable storing the total number of  operators in operatorIndex 
 * i--> global variable storing the current operator in the explore while loop
 * left[],right[] --> character array used as string
 * int tempch=90 -> auto character
 * 
 * 
 * FUNCTIONS:
 * findOperator()--> to find the oerator and storing in operatorIndex
 * Explore()--> exploring the right and left operands of the operator index
 * fright() --> finding the right operand
 * fleft() --> finding the left operand
 * 
 * KEY:FUNCTIONS:
 * strncat();-->
*/	
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//1. Decalre the global DS and function
//VARIABLES:
    //j--> to access the operatorIndex structure = 0
	//temoch--> to randomly access alphabets		
int i=1,j=0,tempch=90;
char str[20],left[10],right[10];

//struct array to store the operators and their position in the input expression
struct operatorIndex
{
	int pos;
	char op;
}operators[15];

//[II] FIND OPERATOR-->to find the operators and their corresponding positions
void findOperator(){
	for(i=0; str[i]!='\0'; i++){ //a. iterate through the string till EOS
		if(str[i]=='/' || str[i]=='+' || str[i]=='-' || str[i]=='*'){//if encountered operator
			operators[j].pos=i;//storing index in pos
			operators[j++].op=str[i];//storing the operator as charcter and incrementing the index
		}
	}
}

//[III] FLEFT--> function to find the left operand
void fleft(int x){
	x--;

	strcpy(left, "");
	while(str[x]!='/' && str[x]!='*' && str[x]!='+' && str[x]!='-' && str[x]!='\0' && str[x]!='='){
		if(str[x]!='$'){
																					//strcpy(temp, left);
																					//strcpy(left, "");
			strncat(left, &str[x], 1);// to append only one character from str[x] to the left string. 
																					//strcat(left, temp);
			str[x]='$';
		}
		// printf("%s\n", str); --> the state of string at each stage
		x--;
	}
}

//function to find the right operand
void fright(int x){
	x++;

	strcpy(right, "");
	while(str[x]!='/' && str[x]!='*' && str[x]!='+' && str[x]!='-' && str[x]!='\0' && str[x]!='='){
		if(str[x]!='$'){
			strncat(right, &str[x], 1);
			str[x]='$';
		}
		// printf("%s\n", str); --> the state of string at each stage
		x++;
	}
}

//[II] EXPLORE--> function to generate intermediate code
void explore(){
	i=0;
	while(i<j){// while loop till end of operatorIndex structure is reached
		fleft(operators[i].pos);//a. findin gthe left operand
		fright(operators[i].pos);//b. finding the right operand
		str[operators[i].pos] = tempch--;  //assigning a temp value to split the expression
		/*	Eg:		a+b*c -->	Z=b*c, Y=a+Z	*/
		// printf("%s\n", str); --> the state of string at each stage
		printf("\t%c = %s %c %s\n",str[operators[i].pos], left, operators[i].op, right);
		i++;
	}

	fleft(1);
	fright(1);
	//     After processing all operators, the fleft and fright functions are called with position 1 
	// (beginning of the expression) to find the final left and right operands.
    // The final three-address code is printed for the entire expression in the format: destination = finalLeftOperand.
	printf("\t%s = %s", left, right);

}
// [I] MAIN__Start
void main(){
	//1. input the expression
	printf("Enter any valid arithmetic expression : ");
	scanf("%s",str);

	//2. Output the intermediate code
	printf("\nThe intermediate code : \n");

	//3. Calling find operator()
	findOperator();
	//4. Exploring 
	explore();
}


/**
 Output format

Enter any valid arithmetic expression : a=x+y+z

The intermediate code :
a=$+y+z
a=$+$+z
a=$Z$+z
        Z = x + y
a=$Z$+z
a=$$$+z
a=$$$+z
a=$$$+$
a=$$$Y$
        Y = Z + z
$=$$$Y$
$=$$$Y$
$=$$$Y$
$=$$$Y$
$=$$$$$
$=$$$$$
        a = Y
*/