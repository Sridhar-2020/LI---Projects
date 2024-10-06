/*
Name 		: Sridhar
Date 		: 23/09/24	
Description 	: MINISHELL
Sample input 	:
Sample output 	:
 */

char prompt[50] = "sridhar@minishell$";
char input_string[50];
#include "main.h"

int main()
{
       // Clear the complete screen
       system("clear");

       // Call the scan_input function
       scan_input(prompt, input_string);
}

