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

    private:
        int listen_st;
        int socket_client[CLIENTCOUNT];

    };

#endif // WORK_H
