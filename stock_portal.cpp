#include "stock_portal.h"
#include "ui_stock_portal.h"

QSqlDatabase db;
stock_portal::stock_portal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::stock_portal)
{
    ui->setupUi(this);

    //Setup database server connection
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("admin");
    db.setDatabaseName("stock");

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

stock_portal::~stock_portal()
{
    delete ui;
}

void stock_portal::on_add_stock_button_clicked()
{
    qDebug() << "Entering Add Stock App";
    add_stock = new add_stock_window(this);
    add_stock->exec();

}

void stock_portal::on_remove_stock_button_clicked()
{
    qDebug() << "Entering Remove Stock App";
    remove_stock = new remove_stock_window(this);
    remove_stock->exec();
}
