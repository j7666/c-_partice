#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "pub.h"
#include "work.h"

using namespace std;

int main(int argc, char *argv[])
    {
        if(argc < 2 )
            {
                printf("usage:qqserverd port \n");
                return -1;
            }

        int iport = atoi(argv[1]);
        if(iport == 0)
            {
                printf("port %d is invalid\n" , iport);
                return -1;
            }

        //setdaemon(); //将程序设置为demon状态。

        work w(iport);
        printf("qqserverd begin\n");

        signal1(SIGINT,catch_Signal );
        signal1(SIGPIPE,catch_Signal );
        w.run();

        return 0;
    }
