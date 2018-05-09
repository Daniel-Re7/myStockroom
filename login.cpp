#include "login.h"

login::login()
{
    //Setup database server connection
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("admin");
    db.setDatabaseName("stock");
}

void login::closeConn()
{
    db.close();
    qDebug() << "Connection Closed";
}

void login::openConn()
{
    if(db.open())
     {
         //Connection success
         qDebug() << "connected to " << db.hostName();
     }
     else
     {
         //Connection failure
         qDebug() << "Connection FAILED.";

     }
}

QSqlDatabase login::getDB()
{
    return login::db;
}
