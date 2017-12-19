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

void tcpreceive::start()
{
    while(1)
    {
        if(m_tcpServer->hasPendingConnections())
        {
            cout << "connect...." << endl;
            m_tcpSocket = m_tcpServer->nextPendingConnection();
            cout << "socket id =" <<m_tcpSocket << endl;

            int numRead = 0, numReadTotal = 0;
            char buffer[50];

            forever {
                numRead  = m_tcpSocket->read(buffer, 50);

                // do whatever with array

                numReadTotal += numRead;
                if (numRead == 0 && !m_tcpSocket->waitForReadyRead())
                    cout << "wait read" << endl;
            }
        }
        else
            cout << "err message: " << m_tcpServer->errorString().toStdString().data() << endl;
        continue;
    }

}

void tcpreceive::newTcpSocket()
{
    cout << "connect...." << endl;
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    cout << "socket id =" <<m_tcpSocket << endl;

    int numRead = 0, numReadTotal = 0;
    char buffer[50];

    forever {
        numRead  = m_tcpSocket->read(buffer, 50);
        printf("buf = %x\n",buffer);
        //cout << "read:" << buffer << endl;
        numReadTotal += numRead;
        if (numRead == 0 && !m_tcpSocket->waitForReadyRead())
            cout << "wait read" << endl;
    }

}
