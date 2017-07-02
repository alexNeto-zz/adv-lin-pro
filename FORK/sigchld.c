#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

sig_atomic_t child_exit_status;

int spawn (char* program, char** arg_list){
  pid_t child_pid;
  /* Duplicate this process. */
  child_pid = fork ();
  if (child_pid != 0)
	 /* This is the parent process. */
	 return child_pid;
  else {
	 /* Now execute PROGRAM, searching for it in the path. */
	 execvp (program, arg_list);
	 /* The execvp function returns only if an error occurs. */
	 fprintf (stderr, "an error occurred in execvp\n");
	 abort ();
  }
}

void clean_up_child_process(int signal_number){
  /* Clean up the child process. */
  int status;
	 wait(&status);
  /* Store its exit status in a global variable. */
  child_exit_status = status;
}

int main(){
  /* Handle SIGCHLD by calling clean_up_child_process. */
		struct sigaction sigchld_action;
		memset(&sigchld_action, 0, sizeof(sigchld_action));
		sigchld_action.sa_handler = &clean_up_child_process;
		sigaction(SIGCHLD, &sigchld_action, NULL);

	/*  */
  int child_status;
  /* The argument list to pass to the “ls” command. */
  char* arg_list[] = {
  "ls",   /* argv[0], the name of the program. */
  "-l",
  "/",
  NULL   /* The argument list must end with a NULL. */
	};
  spawn("ls", arg_list);
  wait (&child_status);
  if (WIFEXITED (child_status))
	 printf ("the child process exited normally, with exit code %d\n",
	 WEXITSTATUS (child_status));
  else
	 printf ("the child process exited abnormally\n");

  return 0;
}
