
#include "main.h"

extern Sll *head;
/************************************************************************************************************************************************** 
**Description   : Function to modify the default action of the signal
 * PARAMETERS   : Integer
 * Return Value : Void
 ***********************************************************************************************************************************************/
void signal_handler(int signum)
{
       if (signum == SIGINT)
       {
	      printf(ANSI_COLOR_GREEN"\n%s"ANSI_COLOR_RESET, prompt);
	      fflush(stdout);
       }

       else if (signum == SIGTSTP)
       {
	      if (insert_at_last(&head) == FAILURE)
	      {
		     printf("Node Insertion failed!!\n");
	      }
       }

       else if (signum == SIGCHLD)
       {
	      // Clearing the child's resources
	      waitpid(-1, NULL, WNOHANG);
       }
}
