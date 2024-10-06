#include "main.h"

/* External commands*/
char *external[200];

/************************************************************************************************************************************************** 
 *Description  : Function to store the externals commands in a 2d array
 * PARAMETERS   : 2D array (Array of Strings)
 * Return Value : void
 ***********************************************************************************************************************************************/
void extract_external_commands(char *external[])
{
       // Open the file in the read mode
       int fd = open("ext_cmd.txt",O_RDONLY);

       // Error checking
       if(fd == -1)
       {
	      perror("OPEN");
	      return;
       }

       char ch, buf[100];
       int buf_idx = 0, external_idx = 0;

       while (read(fd, &ch, 1))
       {
	      //Read the content line by line
	      if (ch != '\n')
	      {
		     buf[buf_idx++] = ch;
	      }

	      else
	      {
		     external[external_idx] = calloc(buf_idx, sizeof(char));

		     // Memory validation
		     if (external[external_idx] == NULL)
		     {
			    perror("CALLOC");
			    return;
		     }

		     // Copy the content of the buffer in the external 2d array
		     strcpy(external[external_idx], buf);

		     // Clear the memory in the buffer
		     memset(buf, 0, sizeof(buf));

		     // Reset the buffer index
		     buf_idx = 0;

		     // Increment the external_idx
		     external_idx++;
	      }
       }
}
