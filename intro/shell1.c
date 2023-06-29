#include "apue.h"
#include <sys/wait.h>
/*
a simple program (Figure 1.7) that reads commands from standard input and executes the commands. 
This is a bare-bones implementation of a shell-like program.
The most fundamental limitation of this program is that we can’t pass arguments to the command we execute.
*/  


int
main(void)
{
	char	buf[MAXLINE];	/* from apue.h */
	pid_t	pid;
	int		status;

	printf("%% ");	/* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null cuz execlp needs */
		
		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid == 0) {		/* child */
			execlp(buf, buf, (char *)0); // replaces the child process with the new program file.
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}

		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");
	}
	exit(0);
}
