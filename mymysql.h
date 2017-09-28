#ifndef MYMYSQL_H
#define MYMYSQL_H

#include "mysql.h"
#include <windows.h>
class mymysql
{
public:
    mymysql();
    int sql_connect(const char *Hostname, const char *User, const char *Passwd, const char *DbName);
    void sql_disconnect();

    int sql_exec(const char *SQL);
    int sql_open(const char *SQL);
    const char *getError();
private:

    MYSQL *connection;
    MYSQL mysql;
    char buf[1024];
};

#endif // MYMYSQL_H
