#include "./client.hpp"

/**Points to know when handling signals -
 *
 * 1.
 * Prefer `sigaction` over `signal`
 * link -
 * https://stackoverflow.com/a/232711
 *
 * 2.
 * When you install a custom signal handler, it overrides the default handler.
 * So be extremely careful about what you are handling,
 * and do you need to perform the actions (eg - freeing allocated memory )
 * what the default handler would have performed.
 * There are ways to call default signal handler after our custom handler,
 * but most of them are not pleasant.
 * The general idea of to reset the handler and raise the exception again.
 * Only do this when you know what you are doing.
 * link -
 * https://stackoverflow.com/questions/6015498/executing-default-signal-handler
 *
 * 3.
 * printf and other printing statements must be avoiding inside the handlers.
 * A workaround is to use a global volatile flag and set it inside the handler,
 * then in the main function, check if flag is marked, then use print statements there.
 * links -
 * https://stackoverflow.com/a/16891799
 * https://stackoverflow.com/a/16891065
 * https://stackoverflow.com/a/21712525
 *
*/
 
// general functions
void InstallSignalHandlers();
void installSignalHandler(int signalType, void (*singalHandlerFunction)(int));

// signal handler functions
void segmentationFaultHandler(int sig);
void zombieProcessesHandler(int sig);

// @abort
extern pid_t parent_pid;
 
// @abort
void sigquit_handler (int sig) {
    // assert(sig == SIGQUIT);
    pid_t self = getpid();
	cout << "parent id is  " << parent_pid <<  " and MySELF is " << self << "\n";
    if (parent_pid != self) {_exit(0);}
	else{
		cout << "I AM THE PARENT.";
	}
}
 

/**Wrapper function : Install Signal Handlers
 *
 * @usage
 * Cleanly install required signal handlers
 *
*/
void InstallSignalHandlers() {
	/**Handling segmentation fault
	 *
	 * In most cases, you should avoid handling this.
	 * let the core get dumped, and try debugging from the dump.
	 * But in some cases, we need more control, for debugging etc
	 * this is useful in those cases.
	*/
	// installSignalHandler(SIGSEGV, segmentationFaultHandler);

	// reap off zombie processes
	installSignalHandler(SIGCHLD, zombieProcessesHandler);
	
	// @abort
	installSignalHandler(SIGQUIT, sigquit_handler);
}


/**install signal handler
 *
 * @usage
 * install a single signal handler cleanly
 *
 * Note that,
 * sigaction is used instead of signal because,
 * sigaction is portable, predictable and thread safe.
 *
*/
void installSignalHandler(int signalType, void (*singalHandlerFunction)(int)) {
	struct sigaction sa;
	sa.sa_handler = singalHandlerFunction;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(signalType, &sa, NULL) == -1) {
		printError();
		exit(1);
	}
}

/**Segmentation Fault Handler
 *
 * Whenever the SIGSEGV signal is raised,
 * it is redirected here.
 *
*/
void segmentationFaultHandler(int sig[[gnu::unused]]) {
	// @logging
	// logs("A Segmentation fault occured.");
	// fprintf(stderr, "Error: signal %d:\n", sig);

	// @logging : Print stack trace

	void* array[10];
	size_t size;

	// get void*'s for all entries on the stack
	size = backtrace(array, 10);

	// print out all the frames to stderr
	backtrace_symbols_fd(array, size, STDERR_FILENO);

	exit(1);
}


/**Reaper for zombie processes
 * When the parent doesn't collect the child's status, it becomes a zombie.
 *
 * @usage
 * The server main process (the one which always listens),
 * does not collect the status of the forked processes created
 * to handle the incoming clients.
 *
 * When the server runs indefinitely, a lot of clients come and go.
 * A lot of processes are created for these clients.
 * Therefore, a lot of zombies will be lying around if we don't clean them
 * 
 * @exact-use-case on client side
 * 1. when the named pipe ( a child process ) in executeShellCommand is done.
 * 2. the job of data connection connection manager process is done.
 * 
*/
void zombieProcessesHandler(int sig[[gnu::unused]]) {
	// @logging
	// logs("REAPING OFF ZOMBIE PROCESS");
	// fprintf(stderr, "Error: signal %d:\n", sig);

	/**
	 * The usual function of waitpid is to wait for child process to exit.
	 *
	 * However, WNOHANG in waitpid
	 * tells it to return immediately if no child processes have exited yet.
	 * It does not go into blocking state.
	 *
	 * waitpid() might overwrite errno, so we save and restore it
	*/
	int saved_errno = errno;
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
	errno = saved_errno;
}
