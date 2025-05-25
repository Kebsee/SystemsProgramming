/**  smsh2.c  small-shell version 2
 **		adds piping support to smsh1
 **		supports commands like: ls | wc
 **/

 #include	<stdio.h>
 #include	<stdlib.h>
 #include	<unistd.h>
 #include	<signal.h>
 #include	<string.h>
 #include	<sys/wait.h>
 #include	"smsh.h"
 
 #define	DFL_PROMPT	"> "
 
 int execute_pipe(char **arglist);
 int find_pipe(char **arglist);
 int execute_single(char **arglist);
 
 int main()
 {
     char	*cmdline, *prompt, **arglist;
     int	result;
     void	setup();
 
     prompt = DFL_PROMPT ;
     setup();
 
     while ( (cmdline = next_cmd(prompt, stdin)) != NULL ){
         if ( (arglist = splitline(cmdline)) != NULL  ){
             if ( find_pipe(arglist) != -1 )
                 result = execute_pipe(arglist);
             else
                 result = execute_single(arglist);
             freelist(arglist);
         }
         free(cmdline);
     }
     return 0;
 }
 
 void setup()
 /*
  * purpose: initialize shell
  * returns: nothing. calls fatal() if trouble
  */
 {
     signal(SIGINT,  SIG_IGN);
     signal(SIGQUIT, SIG_IGN);
 }
 
 void fatal(char *s1, char *s2, int n)
 {
     fprintf(stderr,"Error: %s,%s\n", s1, s2);
     exit(n);
 }
 
 int find_pipe(char **arglist)
 /*
  * purpose: find location of pipe symbol in arglist
  * returns: index of pipe symbol, or -1 if not found
  */
 {
     int i = 0;
     while (arglist[i] != NULL) {
         if (strcmp(arglist[i], "|") == 0)
             return i;
         i++;
     }
     return -1;
 }
 
 int execute_single(char **arglist)
 /*
  * purpose: execute a single command (no pipes)
  * returns: status of command
  */
 {
     return execute(arglist);
 }
 
 int execute_pipe(char **arglist)
 /*
  * purpose: execute piped commands
  * returns: status of last command in pipe
  */
 {
     int pipe_pos = find_pipe(arglist);
     int pipefd[2];
     int pid1, pid2;
     int status = 0;
     
     if (pipe_pos == -1)
         return execute_single(arglist);
         
     /* Split the command at the pipe */
     arglist[pipe_pos] = NULL;
     char **cmd1 = arglist;
     char **cmd2 = &arglist[pipe_pos + 1];
     
     /* Create pipe */
     if (pipe(pipefd) == -1) {
         perror("pipe");
         return -1;
     }
     
     /* Fork first child for left side of pipe */
     if ((pid1 = fork()) == -1) {
         perror("fork");
         return -1;
     }
     
     if (pid1 == 0) {
         /* First child - left side of pipe */
         signal(SIGINT, SIG_DFL);
         signal(SIGQUIT, SIG_DFL);
         
         close(pipefd[0]);  /* Close read end */
         dup2(pipefd[1], STDOUT_FILENO);  /* Redirect stdout to pipe */
         close(pipefd[1]);  /* Close write end */
         
         execvp(cmd1[0], cmd1);
         perror("cannot execute command");
         exit(1);
     }
     
     /* Fork second child for right side of pipe */
     if ((pid2 = fork()) == -1) {
         perror("fork");
         return -1;
     }
     
     if (pid2 == 0) {
         /* Second child - right side of pipe */
         signal(SIGINT, SIG_DFL);
         signal(SIGQUIT, SIG_DFL);
         
         close(pipefd[1]);  /* Close write end */
         dup2(pipefd[0], STDIN_FILENO);  /* Redirect stdin from pipe */
         close(pipefd[0]);  /* Close read end */
         
         execvp(cmd2[0], cmd2);
         perror("cannot execute command");
         exit(1);
     }
     
     /* Parent process */
     close(pipefd[0]);
     close(pipefd[1]);
     
     /* Wait for both children */
     waitpid(pid1, NULL, 0);
     waitpid(pid2, &status, 0);
     
     return status;
 }