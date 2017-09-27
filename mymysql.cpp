#include "mymysql.h"
#include <QMessageBox>
#include "string.h"
mymysql::mymysql()
{
    mysql_init(&mysql);
    connection = NULL;
    memset(buf,0,sizeof(buf));
}

int mymysql::sql_connect(const char *Hostname, const char *User, const char *Passwd, const char *DbName)
{
    connection = mysql_real_connect(&mysql, Hostname, User, Passwd, DbName, 0, 0, 0);
    if(connection)
        return 0;
    else
    {
        //QMessageBox::information(0,"",mysql_error(&mysql));
        memset(buf,0,sizeof(buf));
        strcpy(buf,mysql_error(&mysql));
        return -1;
    }
}

const char *mymysql::getError()
{
    return buf;
}
