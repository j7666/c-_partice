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

void mymysql::sql_disconnect()
{
    if(connection)
        mysql_close(connection);
    connection = NULL;
}

int mymysql::sql_exec(const char *SQL)
{
    if(0 != mysql_query(connection,SQL))
    {
        memset(buf,0,sizeof(buf));
        strcpy(buf,mysql_error(&mysql));
        return -1;
    }
    return 0;
}

int mymysql::sql_open(const char *SQL)
{
    if(0 != mysql_query(connection,SQL))
    {
        memset(buf,0,sizeof(buf));
        strcpy(buf,mysql_error(&mysql));
        return -1;
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if(result == NULL)
        return -1;
    MYSQL_FIELD *field;
    while(1)
    {
       field =  mysql_fetch_field(result);
       if(field == NULL)
        break;
       QMessageBox::information(0,"",field->name);
    }
}

const char *mymysql::getError()
{
    return buf;
}
