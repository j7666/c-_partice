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
