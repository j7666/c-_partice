#ifndef MYMYSQL_H
#define MYMYSQL_H

#include "mysql.h"
#include <windows.h>
class mymysql
{
public:
    mymysql();
    int sql_connect(const char *Hostname, const char *User, const char *Passwd, const char *DbName);
    const char *getError();
private:

    MYSQL *connection;
    MYSQL mysql;
    char buf[1024];
};

#endif // MYMYSQL_H
