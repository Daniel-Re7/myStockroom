#include "add_stock_window.h"
#include "ui_add_stock_window.h"
#include "stock_portal.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include "login.h"

add_stock_window::add_stock_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_stock_window)
{
    ui->setupUi(this);
}

add_stock_window::~add_stock_window()
{
    delete ui;
}

void add_stock_window::on_update_stock_button1_clicked()
{
    login connection;
    connection.openConn();

    QString dept = ui->department_input->currentText();
    QString dpci = ui->dpci_input->text();
    QString quantity = ui->quantity_input->text();
    QString location = ui->location_input->text().toUpper();

    //Check if Department was selected
    if(dept.isNull())
    {
       QMessageBox msg;
       msg.information(this,tr("Warning"), tr("Please select department"));
    }
    //Check if valid DPCI Code
    else if(!dpci.toInt() || dpci.isNull())
    {
       QMessageBox msg;
       msg.information(this,tr("Warning"), tr("Invalid DPCI"));
    }
    //Make sure quantity is not null or zero
    else if(quantity.toInt() <= 0 || quantity.isNull())
    {
       QMessageBox msg;
       msg.information(this,tr("Warning"), tr("Invalid quantity"));
    }

    else
    {
       QSqlQuery checkExist;
       checkExist.exec("SELECT Quantity FROM stockroom WHERE Dept='" + dept + "' AND DPCI='" + dpci + "' AND Location ='" + location+ "'");

       //If item already exists in location and dept, update total count
       if(checkExist.size() != 0)
       {
           QSqlQuery updateQuery;
           updateQuery.exec("UPDATE stockroom SET Quantity=Quantity+" + quantity + " WHERE DPCI='" + dpci+"'" );
           connection.closeConn();
           this->close();

       }
       else
       {
            //Query item into the database
            QSqlQuery query;
            query.prepare("INSERT INTO stockroom(Dept, DPCI, Quantity, Location) VALUES (:dept, :dpci, :quantity, :location)");
            query.bindValue(":dept", dept);
            query.bindValue(":dpci", dpci);
            query.bindValue(":quantity", quantity);
            query.bindValue(":location", location);
            query.exec();
            connection.closeConn();
            this->close();
       }
    }
}


void add_stock_window::on_add_stock_back_button_clicked()
{
    this->close();
}
