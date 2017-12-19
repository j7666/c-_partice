#include <QCoreApplication>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <QString>
#include <errno.h>

#define RDBMIRROR_CYCLE_DATA_PORT_send   7990
#define RDBMIRROR_CYCLE_DATA_PORT_receive   7991

#define RDBMAXREALTIMEDATALEN       32767//(1024*10)
#define strNetA "222.111.112.201"
#define strNetB "222.111.112.202"

using namespace std;

bool m_bExitThread = true;
int m_nRecvSocket = NULL;
int m_nSendSocketA = NULL;

bool receive_init();
void recieve_run();
bool send_init();
void send_run();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "====socket test begin====" << endl;
    if(!receive_init())
        cout << "====receive_init failed" << endl;
    if(!send_init())
        cout << "====send_init failed" << endl;
    if(QString(argv[1]) != "s")
    recieve_run();
    else
    send_run();

    return a.exec();
}

bool receive_init()
{
    if(m_nRecvSocket > 0)
    {
        ::shutdown(m_nRecvSocket, SHUT_RDWR);
        ::close(m_nRecvSocket);
    }

    m_nRecvSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
    if(m_nRecvSocket <= 0 )
    {
        cout << "创建receive socket出错"  << endl;
        return false;
    }
    else
        cout << "m_nRecvSocket id = " << m_nRecvSocket <<endl;

    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock_addr.sin_port = htons(RDBMIRROR_CYCLE_DATA_PORT_receive);
    if(::bind(m_nRecvSocket, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
    {
        ::shutdown(m_nRecvSocket, SHUT_RDWR);
        ::close(m_nRecvSocket);
        cout << "socket bind errno = " << errno << endl;
        return false;
    }

    int iBroadcast = 1;
    ::setsockopt(m_nRecvSocket, SOL_SOCKET, SO_BROADCAST, (char *)&iBroadcast, sizeof(int));
    m_bExitThread = false;
    return true;

}

void recieve_run()
{
    char *buf = NULL;
    while(m_bExitThread == false)
    {
        fd_set rset;
        struct timeval timedelay;
        timedelay.tv_sec = 0;
        timedelay.tv_usec = 50000;
        FD_ZERO(&rset);
        FD_SET(m_nRecvSocket, &rset);
        int maxfd = m_nRecvSocket;
        int ret = ::select(maxfd+1, &rset, NULL, NULL, &timedelay);
        if(ret <= 0)
        {
           //  cout << "select <=0" << endl;
            continue;
        }
        if(FD_ISSET(m_nRecvSocket, &rset))
        {
            cout << "has data..." << endl;
            int nLen;
            if(buf == NULL)
                buf = (char*)malloc(RDBMAXREALTIMEDATALEN);
            memset(buf, 0, RDBMAXREALTIMEDATALEN);
            nLen = ::recvfrom(m_nRecvSocket, buf, RDBMAXREALTIMEDATALEN, 0, NULL, NULL);
            if(nLen > RDBMAXREALTIMEDATALEN)
            {
                cout << "CMirrorDataRecvTask recv data is too long.len=" << nLen;
                continue;
            }
            cout << "data len = " << nLen <<"value = " << buf <<endl;
        }else cout << "FD_ISISET failed" << endl;
    }
    free(buf);
    buf = NULL;
}


bool send_init()
{
    if(m_nSendSocketA > 0)
    {
        ::shutdown(m_nSendSocketA, SHUT_RDWR);
        ::close(m_nSendSocketA);
    }

    m_nSendSocketA = ::socket(AF_INET, SOCK_DGRAM, 0);

    if(m_nSendSocketA <= 0)
        {
            cout << "创建send socket出错"  << endl;
            return false;
        }

    cout<< "sendsoket id = " <<m_nSendSocketA <<endl;
    return true;

}

void send_run()
{
    QString strSendIP = strNetB;

    int nSendPort = RDBMIRROR_CYCLE_DATA_PORT_send;
    struct sockaddr_in sendaddr;
    sendaddr.sin_family = AF_INET;
    sendaddr.sin_port = htons(nSendPort);
    sendaddr.sin_addr.s_addr = inet_addr(strSendIP.toStdString().data());
    while(1)
    {
        char *pData = "AABBCC----201 send";
        int ret = ::sendto(m_nSendSocketA, (const char*)pData, sizeof("AABBCC----201 send"), 0, (struct sockaddr *)&sendaddr, sizeof(sendaddr));
        cout << "send data to" << strSendIP.toStdString().data() << "   data:" << pData << endl;
        sleep(5);
    }
}
