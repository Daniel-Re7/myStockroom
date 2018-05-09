#ifndef LOGIN_H
#define LOGIN_H
#include <QtSql>

class login
{
public:
    login();
    void closeConn();
    void openConn();
    QSqlDatabase getDB();

private:
    QSqlDatabase db;
};

#endif // LOGIN_H
