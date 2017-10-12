#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "pub.h"

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

        setdaemon(); //将程序设置为demon状态。
        printf("qqserverd begin\n");
        while(1)
            {
                sleep(1);
            }

        return 0;
    }
