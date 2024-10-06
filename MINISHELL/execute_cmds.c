
#include "main.h"

int no_cmd_flag;
Sll *head = NULL;
int status;
/*******************************************************************************************************************************************************************
 ** Description  : Function to execute the external command 
 * PARAMETERS   : String
 * Return Value : void
 ***********************************************************************************************************************************************/
void execute_external_commands(char *input_string)
{
       // Convert the input string to argv
       char *argv[100], ptr[100]; 
       int count = 0, k = 0;
       for (int i = 0; i < (strlen(input_string) + 1); i++)
       {
	      if (input_string[i] == ' ' || input_string[i] == '\0')
	      {
		     ptr[count] = '\0';
		     count = 0;

		     // To avoid the buffer
		     argv[k] = malloc(strlen(ptr) + 1);

		     // Error Validtion
		     if (!argv[k])
		     {
			    perror("Malloc");
			    return;
		     }
		     // Coping the string to the appropiate index
		     strcpy(argv[k++], ptr);
	      }
	      else
	      {
		     ptr[count++] = input_string[i];
	      }
       }
       argv[k] = NULL;

       // Check for pipe
       if (strchr(input_string, '|'))
       {
	      // If pipe is present
	      npipe(input_string);
	      exit(0);
       }

       else
       {
	      // If pipe is not present
	      execvp(argv[0], argv);
       }
}

/************************************************************************************************************************************************** 
**Description   : Function to execute the internal command 
 * PARAMETERS   : String
 * Return Value : void
 ***********************************************************************************************************************************************/
void execute_internal_commands(char *input_string, char *cmd)
{
       int k = 0;
       char buf[100], path[100];
       if(!strcmp(input_string, "pwd"))
       {
	      getcwd(buf, sizeof(buf));
	      printf("%s\n", buf);
       }

       else if(!(strcmp(cmd, "cd")))
       {
	      int i = 0, slash_flag = 0;
	      while (input_string[i] != '\0')
	      {
		     if (!slash_flag)
		     {
			    if (input_string[i] == '/')
			    {
				   slash_flag = 1;
				   path[k++] = '/';
			    }
		     }
		     else
		     {
			    path[k++] = input_string[i];
		     }
		     i++;
	      }
	      path[k] = '\0';
	      printf("PATH : %s\n", path);

	      if(chdir(path) != 0) perror("chdir");
       }

       else if(!strcmp(cmd, "echo"))
       {
	      int dollar_flag = 0, i = 0, l = 0;
	      while(input_string[i])
	      {
		     if (!dollar_flag)
		     {
			    if(input_string[i] == '$')
			    {
				   dollar_flag = 1;
			    }
		     }

		     else
		     {
			    path[l++] = input_string[i];
		     }
		     i++;
	      }
	      path[l] = '\0';

	      if (!strcmp(path, "$"))
	      {
		     printf("%d\n", getpid());
	      }

	      else if (!strcmp(path, "?"))
	      {
		     // If there is an abnormal termination of the previous command
		     printf("%d\n", status);
	      }

	      else if (!strcmp(path, "SHELL"))
	      {
		     printf("%s\n", getenv("SHELL"));
	      }

	      else
	      {
		     printf("%s: command not found\n", path);
	      }
       }

       else if (!strcmp(cmd, "exit"))
       {
	      // Exit from the application
	      exit(0);
       }

       else if (!strcmp(cmd, "fg"))
       {
	      no_cmd_flag = 1;
	      fg_bg(head, 1);
       }

       else if (!strcmp(cmd, "bg"))
       {
	      no_cmd_flag = 1;
	      fg_bg(head, 0);
       }

       else if (!strcmp(cmd, "jobs"))
       {
	      no_cmd_flag = 1;
	      print_sll(head);
       }
}
