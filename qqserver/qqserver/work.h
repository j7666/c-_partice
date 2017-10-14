#ifndef WORK_H
#define WORK_H

#define BODYBUF 1024
#define CLIENTCOUNT 256

struct msg_t
    {
        unsigned char head[4];
        char body[BODYBUF];
    };


class work
    {
    public:
        work(int port);
        ~work();
        void run();


    private:
        int setnonblocking(int st );
        int socket_accept();
        int socket_receive(int st);
        void user_logout(int st);
        int listen_st;
        int socket_client[CLIENTCOUNT];

    };

#endif // WORK_H
