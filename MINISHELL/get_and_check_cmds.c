
#include "main.h"

/* Built in functions*/
char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
       "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
       "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", "fg", "bg", "jobs", "NULL"};

extern char *external[200];
/************************************************************************************************************************************************** 
 *  Description  : Function to get the command 
 * PARAMETERS   : String
 * Return Value : Address of the starting word of a command
 ***********************************************************************************************************************************************/
char *get_command(char *input_string)
{
       // Dynamically allocate the memory
       char *ptr = calloc(20, sizeof(char));

       // Memory validation
       if (!ptr) 
       {
	      perror("MALLOC");
	      return NULL;
       }

       for (int i = 0, j = 0; i < 20; i++)
       {
	      if (input_string[i] == ' ' || input_string[i] == '\0')
	      {
		     ptr[i] = '\0';
		     return ptr;
	      }
	      ptr[i] = input_string[i];
       }
}

/************************************************************************************************************************************************** 
**Description   : Function to check the command type 
 * PARAMETERS   : String
 * Return Value : Integer
 ***********************************************************************************************************************************************/
int check_command_type(char *command)
{
       int i = 0;
       // Check for internal command
       while (strcmp(builtins[i], "NULL"))
       {
	      if (!strcmp(builtins[i], command))
		     return BUILTIN;
	      i++;
       }

       // Reset the index
       i = 0;

       //Check for non builtin command
       while (external[i])
       {
	      if (!strcmp(external[i], command))
		     return EXTERNAL;
	      i++;
       }
       return NO_COMMAND;
}
