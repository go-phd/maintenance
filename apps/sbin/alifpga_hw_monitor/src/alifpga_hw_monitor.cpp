#include <gflags/gflags.h>
#include<iostream>
#include<string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>
#include "csd_maintenance.h"
#include "define.h"


using namespace std;
using namespace csd;

#define VERSION "1.0.0"

#if 0
void daemonize(const char *cmd)
{
    int                  i, fd0, fd1, fd2;
    pid_t                pid;
    struct rlimit        rl;
    struct sigaction     sa;
    
    /*
    * Clear file creation mask.
    */
    umask(0);

    /*
    * Get maximum number of file descriptors.
    */
    if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
        err_quit("%s: can't get file limit", cmd);
    
    /*
    * Become a session leader to lose controlling TTY.
    */
    if((pid = fork()) < 0)
        err_quit("%s: can't fork", cmd);
    else if (pid != 0)    /* parent */
        exit(0);
    setsid();

    /*
    * Ensure future opens won't allocate controlling TTYs.
    */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if(sigaction(SIGHUP, &sa, NULL) < 0)
        err_quit("%s: can't ignore SIGHUP");
    if((pid = fork()) < 0)
        err_quit("%s: can't fork", cmd);
    else if( pid != 0 )    /* parent */
        exit(0);

    /*
    * Change the current working directory to the root so 
    * we won't prevent file system from being unmounted.
    */
    if(chdir("/") < 0)
        err_quit("%s: can't change directory to /");
    
    /*
    * Close all open file descriptors.
    */
    if(rl.rlim_max = RLIM_INFINITY)
        rl.rlim_max = 1024;
    for(i = 0; i < rl.rlim_max; i++)
        close(i);

    /*
    * Attach file descriptors 0, 1, and 2 to /dev/null.
    */    
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    /*
    * Initialize the log file.
    */
    //openlog(cmd, LOG_CONS, LOG_DAEMON);
    if(fd0 != 0 || fd1 != 1 || fd2 != 2)
    {
        //syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
}
#endif


int main(int argc,char* argv[]) {
	gflags::SetVersionString(VERSION);//设置版本
	string usage_str = "Usage:";
	usage_str+=argv[0];
	gflags::SetUsageMessage(usage_str);
	gflags::ParseCommandLineFlags(&argc, &argv, true);

	printf("----------\n");
	if(daemon(0, 0) < 0)  
    {  
        perror("error daemon.../n");  
        exit(1);  
    }

	printf("-----========--\n");

	while (1) {
		sleep(1);
		printf("-----=+++++++++++=======--\n");
	}
	
	return 0;
}



