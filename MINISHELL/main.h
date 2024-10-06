#ifndef MAIN_H
#define MAIN_H

/* User defined Datatype*/
typedef struct ListNode
{
       int pid;
       char cmd[100];
       struct ListNode *link;
}Sll;

/* Predefined Libraries*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
 
/* Macros*/
#define BUILTIN		1
#define EXTERNAL	2
#define NO_COMMAND  	3
#define SUCCESS  	4
#define FAILURE 	5

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


// Global varaibles used in all the files
extern char prompt[50];
extern int status;
extern pid_t pid;

/* Function prototypes*/

/* Function that is used to insert a new node at the end of the single linked list*/
int insert_at_last(Sll **head);

/* Function that is used to print the sll*/
void print_sll(Sll *head);

/* Function that continues the stopped processes*/
void fg_bg(Sll *head, int flag);

/* Function that is used to scan the input command from the user and validate*/
void scan_input(char *prompt, char input_string[]);

/* This function takes the input string and return the address of the first word*/
char *get_command(char *input_string);

/* Function to check whether the command is internal or external*/
int check_command_type(char *command);

/* Function that is used to execute the commands that include pipe*/
void npipe(char *input_string);

/* Function to execute the internal commands*/
void execute_internal_commands(char *input_string, char *command);

/* Function to execute the external commands*/
void execute_external_commands(char *input_string);

/* Function that is used to modify the default action of the signals*/
void signal_handler(int sig_num);

/* Function that is used to extract the external commands from a file*/
void extract_external_commands(char **external_commands);

#endif
