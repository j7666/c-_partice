#include "pub.h"



void setdaemon()
    {
        pid_t pid,sid;
        pid = fork();

        if(pid < 0)
            {
                exit (EXIT_FAILURE);
            }
        if(pid > 0)
            {
                exit(EXIT_SUCCESS );
            }

        if( (sid = setsid()) < 0 )
            {
                printf("setsid failed %s\n", strerror(errno));
                exit (EXIT_SUCCESS);
            }

    }

int signal1(int signo, void (*func)(int))
    {
        struct sigaction act,oact;
        act.sa_handler = func;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        return sigaction(signo,&act,&oact);
    }



void catch_Signal(int Sign)
    {
        switch (Sign) {
            case SIGINT:
                break;
            case SIGPIPE:
                break;
            default:
                break;
            }
    }

int socket_creat(int port)
    {


    }
