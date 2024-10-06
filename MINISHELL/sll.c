
#include "main.h"

extern char input_string[50];

/*******************************************************************************************************************************************************************
 *  Description  : Function to insert the node at the end of the list
 * PARAMETERS   : Address of the head
 * Return Value : Integer
 ***********************************************************************************************************************************************/
int insert_at_last(Sll **head)
{
       // Create a Node
       Sll *new = malloc(sizeof(Sll));

       // Validation
       if (!new)
       {
	      perror("malloc");
	      return FAILURE;
       }
       new->pid = pid;
       strcpy(new->cmd, input_string);
       new->link = NULL;

       // First time
       if (*head == NULL)
       {
	      *head = new;
	      return SUCCESS;
       }

       Sll *temp = *head;
       while (temp->link)
       {
	      temp = temp -> link;
       }
       temp ->link = new;
       return SUCCESS;
}

/*******************************************************************************************************************************************************************
 *  Description  : Function to print the sll
 * PARAMETERS   : Head of the Sll
 * Return Value : Void
 ***********************************************************************************************************************************************/
void print_sll(Sll *head)
{
       int i = 1;
       while (head)
       {
	      printf("[%d]\t%d\t%s\n", i++, head->pid, head->cmd);
	      head = head -> link;
       }
       return;
}
