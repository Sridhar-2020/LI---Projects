#include "main.h"

extern char input_string[50];

/************************************************************************************************************************************************** 
**Description   : Function to continue the stopped processes
 * PARAMETERS   : Address of Head of SLL, Integer 
 * Return Value : Void
 ***********************************************************************************************************************************************/

void fg_bg(Sll *head, int flag)
{
       // Traverse to the last node
       while (head->link)
       {
	      head = head ->link;
       }

       // Foreground
       if (flag)
       {
	      printf("%s\n", head->cmd);
	      kill(head->pid, SIGCONT);
	      waitpid(head->pid, NULL, WUNTRACED);
       }

       // Background
       else
       {
	      printf("%s\t&\n", head->cmd);
	      kill(head->pid, SIGCONT);
       }

}
