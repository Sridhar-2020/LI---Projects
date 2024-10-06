
#include "main.h"

/************************************************************************************************************************************************** 
**Description   : Function to execute the commands that include pipe
 * PARAMETERS   : String
 * Return Value : Void
 ***********************************************************************************************************************************************/
void npipe(char ip_str[])
{
       // Convert the input string to 2d array

       char *word = strtok(ip_str," ");

       int count = 0;
       char *argv[100];

       // Storing the first word in the 2D array
       argv[count++] = word;

       while (1)
       {
	      word = strtok(NULL, " ");

	      if (!word) break;

	      argv[count++] = word;
       }
       argv[count] = NULL;

       int i = 0, size = 0;
       while (argv[i])
       {
	      if (!strcmp(argv[i], "|"))
	      {
		     size++;
	      }

	      i++;
       }
       size++;  //To adjust the size of command array

       // Reset the index position
       i = 0;

       int cmd[size], idx = 1;
       cmd[0] = 0;              // Always the first index is the first command

       // Storing the commands position in a array
       while (argv[i])
       {
	      if (!strcmp(argv[i], "|"))
	      {
		     cmd[idx++] = i + 1;
		     argv[i] = NULL;
	      }
	      i++;
       }


       int fd[2];

       for (int i = 0; i < size; i++)
       {
	      if (pipe(fd) == -1)
	      {
		     perror("PIPE");
		     return;
	      }

	      // Creating a new process
	      pid_t pid = fork();

	      // Parent
	      if (pid > 0)
	      {
		     // Close the write end of the pipe
		     close(fd[1]);

		     // Replace the fd 0 with read end of the pipe
		     dup2(fd[0], 0);

		     // Close the read end of the pipe
		     close(fd[0]);

		     wait(NULL);
	      }

	      // Child
	      else if (pid == 0)
	      {
		     // If it is the last iteration dont execute
		     if (i != size - 1)
		     {
			    // Close the read end of the pipe
			    close(fd[0]);

			    // Replace the fd 1 with write end of the pipe
			    dup2(fd[1], 1);
		     }
		     // Execute the execvp command
		     execvp(argv[cmd[i]], argv + cmd[i]);
	      }

	      // Error
	      else
	      {
		     perror("FORK");
	      }
       }
}
