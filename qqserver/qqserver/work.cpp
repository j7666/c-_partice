#include "work.h"
#include "pub.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

work::work(int port)
    {
        memset(socket_client,0,sizeof(socket_client) );
        listen_st = socket_creat(port);
        if(listen_st == 0)
            exit(-1);

    }

work::~work()
    {
        if(listen_st)
            close(listen_st);
    }

void work::run()
    {
        struct epoll_event ev, events[CLIENTCOUNT];
        setnonblocking(listen_st ); //设置服务端Linstn的socket为非阻塞。
        int epfd = epoll_create(CLIENTCOUNT);
        ev.data.fd = listen_st; //指定放那个socket
        ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
        epoll_ctl(epfd, EPOLL_CTL_ADD, listen_st,&ev);
        printf("work::run begin\n");
        int st = 0;
        while(1)
            {
                //阻塞直到，epoll中的socket有指定的消息产生。
                printf("111111\n" );
                int nfds = epoll_wait(epfd,events,CLIENTCOUNT,-1 );
                printf("nfds = %d\n",nfds );
                if(nfds == -1)
                    {
                        printf("epoll_wait failed %s\n", strerror(errno));
                        break;
                    }

                for(int i=0; i< nfds; i++)
                    {
                        //printf("nfds = %d\n",nfds );
                        if(events[i].data.fd < 0 )
                            continue;
                        if(events[i].data.fd == listen_st)
                            {
                                st = socket_accept();
                                if(st >= 0 )
                                    {
                                        setnonblocking(st);
                                        ev.data.fd = st;
                                        ev.events = EPOLLIN |EPOLLERR | EPOLLHUP;
                                        epoll_ctl(epfd, EPOLL_CTL_ADD, st, &ev);
                                        continue;
                                    }
                            }

                        if(events[i].events & EPOLLIN)
                            {
                                st = events[i].data.fd; //得到有数据的socket
                                if(socket_receive(st) <= 0)
                                    {
                                        user_logout(st);
                                        events[i].data.fd = -1;
                                    }

                            }

                        if(events[i].events & EPOLLERR)
                            {
                                st = events[i].data.fd; //得到有数据的socket
                                user_logout(st);
                                events[i].data.fd = -1;
                            }


                        if(events[i].events & EPOLLHUP)
                            {
                                st = events[i].data.fd; //得到有数据的socket
                                user_logout(st);
                                events[i].data.fd = -1;
                            }


                    }

            }

        close(epfd);
    }

int work::setnonblocking(int st)
    {
        int opts = fcntl(st , F_GETFL);
        if(opts < 0 )
            {
                return 0;
            }

        opts = opts | O_NONBLOCK;

        if(fcntl(st , F_SETFL ,opts ) < 0 )
            {
                return 0;
            }
        return 1;
    }

int work::socket_accept()
    {
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        memset(&client_addr, 0 , sizeof(client_addr) );
        int client_st = accept(listen_st,(struct sockaddr *) &client_addr, &len );

        if(client_st < 0)
            printf("accept failed %s\n", strerror(errno));
        else
            printf("accept by %s\n", inet_ntoa(client_addr.sin_addr));
        return client_st;


    }

int work::socket_receive(int st)
    {
        return 0 ;
    }

void work::user_logout(int st)
    {

    }
