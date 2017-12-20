#include "tcpreceive.h"


tcpreceive::tcpreceive()
{
    m_tcpServer = new QTcpServer;
    bool lis_ret = m_tcpServer->listen(QHostAddress::Any,SERVERPORT );
    if(!lis_ret)
    {
       m_tcpServer->close();
       cout << "listen error. errno =" << errno << endl;
    }
    connect(m_tcpServer,SIGNAL(newConnection()),this,SLOT(newTcpSocket()) );

}

void tcpreceive::newTcpSocket()
{
    cout << "connect...." << endl;
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    connect(m_tcpSocket,SIGNAL(readyRead()),this,SLOT(Read()) );
    connect(m_tcpSocket,SIGNAL(disconnected()),this,SLOT(deleteLater()) );
}

void tcpreceive::Read()
{
    printf("read\n");

    int numRead = 0, numReadTotal = 0;
    char buffer[50];
    memset(buffer, 0, sizeof(buffer ) );
    forever {
        numRead  = m_tcpSocket->read(buffer, 5);
        for(int i = 0; i < numRead; i++)
        printf("i = %d,  buf = %x\n",i,buffer[i]);
        //cout << "read:" << buffer << endl;
        memset(buffer, 0, sizeof(buffer ) );
        numReadTotal += numRead;
        if (numRead == 0 && !m_tcpSocket->waitForReadyRead())
        {
            cout << "wait read" << endl;
            break;
        }
    }
}
