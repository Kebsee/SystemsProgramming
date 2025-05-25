/**  smsh3.c  small-shell version 3
 **		adds redirection support to smsh2
 **		supports commands like: ls > file.txt, cat < input.txt
 **/

 #include	<stdio.h>
 #include	<stdlib.h>
 #include	<unistd.h>
 #include	<signal.h>
 #include	<string.h>
 #include	<sys/wait.h>
 #include	<fcntl.h>
 #include	"smsh.h"
 
 #define	DFL_PROMPT	"> "
 
 int execute_pipe(char **arglist);
 int execute_with_redirection(char **arglist);
 int find_pipe(char **arglist);
 int find_redirection(char **arglist, char *symbol);
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
             else if ( find_redirection(arglist, ">") != -1 || find_redirection(arglist, "<") != -1 )
                 result = execute_with_redirection(arglist);
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
 
 int find_redirection(char **arglist, char *symbol)
 /*
  * purpose: find location of redirection symbol in arglist
  * returns: index of redirection symbol, or -1 if not found
  */
 {
     int i = 0;
     while (arglist[i] != NULL) {
         if (strcmp(arglist[i], symbol) == 0)
             return i;
         i++;
     }
     return -1;
 }
 
 int execute_single(char **arglist)
 /*
  * purpose: execute a single command (no pipes or redirection)
  * returns: status of command
  */
 {
     return execute(arglist);
 }
 
 int execute_with_redirection(char **arglist)
 /*
  * purpose: execute command with input/output redirection
  * returns: status of command
  */
 {
     int out_redir = find_redirection(arglist, ">");
     int in_redir = find_redirection(arglist, "<");
     int pid;
     int status = 0;
     char *out_file = NULL;
     char *in_file = NULL;
     
     /* Get filenames and remove redirection from arglist */
     if (out_redir != -1) {
         out_file = arglist[out_redir + 1];
         arglist[out_redir] = NULL;
     }
     if (in_redir != -1) {
         in_file = arglist[in_redir + 1];
         arglist[in_redir] = NULL;
     }
     
     if ((pid = fork()) == -1) {
         perror("fork");
         return -1;
     }
     
     if (pid == 0) {
         /* Child process */
         signal(SIGINT, SIG_DFL);
         signal(SIGQUIT, SIG_DFL);
         
         /* Handle output redirection */
         if (out_file != NULL) {
             int fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
             if (fd == -1) {
                 perror("cannot open output file");
                 exit(1);
             }
             dup2(fd, STDOUT_FILENO);
             close(fd);
         }
         
         /* Handle input redirection */
         if (in_file != NULL) {
             int fd = open(in_file, O_RDONLY);
             if (fd == -1) {
                 perror("cannot open input file");
                 exit(1);
             }
             dup2(fd, STDIN_FILENO);
             close(fd);
         }
         
         execvp(arglist[0], arglist);
         perror("cannot execute command");
         exit(1);
     } else {
         /* Parent process */
         if (wait(&status) == -1)
             perror("wait");
     }
     
     return status;
 }
 
 int execute_pipe(char **arglist)
 /*
  * purpose: execute piped commands with possible redirection
  * returns: status of last command in pipe
  */
 {
     int pipe_pos = find_pipe(arglist);
     int pipefd[2];
     int pid1, pid2;
     int status = 0;
     
     if (pipe_pos == -1)
         return execute_with_redirection(arglist);
         
     /* Split the command at the pipe */
     arglist[pipe_pos] = NULL;
     char **cmd1 = arglist;
     char **cmd2 = &arglist[pipe_pos + 1];
     
     /* Check for redirection in second command */
     int out_redir = find_redirection(cmd2, ">");
     int in_redir = find_redirection(cmd1, "<");
     char *out_file = NULL;
     char *in_file = NULL;
     
     if (out_redir != -1) {
         out_file = cmd2[out_redir + 1];
         cmd2[out_redir] = NULL;
     }
     if (in_redir != -1) {
         in_file = cmd1[in_redir + 1];
         cmd1[in_redir] = NULL;
     }
     
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
         
         /* Handle input redirection for first command */
         if (in_file != NULL) {
             int fd = open(in_file, O_RDONLY);
             if (fd == -1) {
                 perror("cannot open input file");
                 exit(1);
             }
             dup2(fd, STDIN_FILENO);
             close(fd);
         }
         
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
         
         /* Handle output redirection for second command */
         if (out_file != NULL) {
             int fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
             if (fd == -1) {
                 perror("cannot open output file");
                 exit(1);
             }
             dup2(fd, STDOUT_FILENO);
             close(fd);
         }
         
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