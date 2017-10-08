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

int mymysql::sql_open(const char *SQL , QStandardItemModel **p)
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

    int rowcount = 0 ;
    rowcount =  mysql_affected_rows(connection); //行数，记录数量。要放在fetch_filed后，

    int fieldcount = 0;
    fieldcount = mysql_field_count(connection);  //字段数量

    *p = new QStandardItemModel(rowcount , fieldcount);

    MYSQL_FIELD *field;



    int i =0;
    int j = 0;
    for(i = 0; i<fieldcount; i++)
    {
        field =  mysql_fetch_field(result);
        (*p)->setHeaderData(i,Qt::Horizontal,field->name);
    }

    MYSQL_ROW row  = NULL;
    for(i = 0; i<rowcount; i++)
    {
        row = mysql_fetch_row(result);
        for(j = 0; j < fieldcount; j++)
        {
            (*p)->setData((*p)->index(i,j,QModelIndex()),QString(row[j]));
        }
    }



}

const char *mymysql::getError()
{
    return buf;
}
