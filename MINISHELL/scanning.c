#include "main.h"

// Global Declaration
pid_t pid;
extern int no_cmd_flag;

/* External commands*/
extern char *external[200];

/*******************************************************************************************************************************************************************
 *  Description  : Function to scan the input string and perform action accordinly
 * PARAMETERS   : Prompt(String), Command(String) 
 * Return Value : Void
 ***********************************************************************************************************************************************/
void scan_input(char *prompt, char *input_string)
{
       signal(SIGINT, signal_handler);
       signal(SIGTSTP, signal_handler);
       signal(SIGCHLD, signal_handler);
       extract_external_commands(external);
       // Super Loop
       while (1)
       {
	      // Print the prompt on to the screen
	      printf(ANSI_COLOR_GREEN"%s "ANSI_COLOR_RESET, prompt);

	      // Scanf the input from the user
	      scanf(" %[^\n]", input_string);

	      // Validating the PS1 variable

	      // If PS1 is present
	      if (strstr(input_string, "PS1") != NULL)
	      {
		     char *address = strchr(input_string, ' ');

		     if (address)
		     {
			    // If spaces are given print the error messasge else
			    printf("PS1 : command not found\n");
			    continue;
		     }
		     else
		     {
			    // Storing the address of the equals to into address variable
			    address = strchr(input_string, '=');
			    address++;
			    strcpy(prompt, address);
		     }
	      }

	      // Getting the first word of the command 
	      char *cmd = get_command(input_string);

	      // Checking for memory allocated or not
	      if(!cmd)
	      {
		     printf("Empty address\n");
		     return;
	      }

	      int type = check_command_type(cmd);

	      // If the type is a external command
	      if(type == EXTERNAL)
	      {
		     // Creating a new child process
		     pid = fork();

		     // Parent
		     if (pid > 0)
		     {
			    // Waiting for the child process even if it is stopped 
			    waitpid(pid, &status, WUNTRACED);
		     }

		     // Child
		     else if (pid == 0)
		     {
			    signal(SIGINT, SIG_DFL);
			    signal(SIGTSTP, SIG_DFL);
			    signal(SIGCHLD, SIG_DFL);

			    // Call the execute external command function
			    execute_external_commands(input_string);
		     }

		     // Error
		     else
		     {
			    perror("FORK");
			    return;
		     }
	      }

	      // If the type is a internal command
	      else if (type == BUILTIN)
	      {
		     // Call the execute internal command function
		     execute_internal_commands(input_string, cmd);
	      }

	      else if (!no_cmd_flag)
	      {
		     printf("%s: command not found\n", cmd);
	      }
       }
}
