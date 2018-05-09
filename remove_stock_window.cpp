#include "remove_stock_window.h"
#include "ui_remove_stock_window.h"
#include "stock_portal.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include "login.h"

remove_stock_window::remove_stock_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::remove_stock_window)
{
    ui->setupUi(this);
}

remove_stock_window::~remove_stock_window()
{
    delete ui;
}

void remove_stock_window::on_confirm_remove_button_clicked()
{
    login connection;
    connection.openConn();

    QString dpci = ui->remove_dpci_edit->text();
    QString location = ui->remove_loc_edit->text();
    QString dept = ui->remove_dept_input->currentText();
    QString removeAmount = ui->remove_amount_edit->text();

    QSqlQuery checkQ;
    checkQ.exec("SELECT * FROM stockroom WHERE Dept='" + dept + "' AND DPCI='" + dpci + "' AND Location ='" + location+ "'");
    checkQ.next();
    QString quanAmount;
    quanAmount.append(checkQ.value(2).toString() + " ");

    if(dept.isNull())
    {
       QMessageBox msg;
       msg.information(this,tr("Warning"), tr("Please select department"));
    }

    //Check if valid DPCI Code
    //Basic check for now...
    else if(!dpci.toInt() || dpci.isNull())
    {
       QMessageBox msg;
       msg.information(this,tr("Warning"), tr("Invalid DPCI"));
    }
    //Make sure quantity is not null or zero
    else if(removeAmount.toInt() <= 0 || removeAmount.isNull())
    {
       QMessageBox msg;
       msg.information(this,tr("Warning"), tr("Invalid amount to remove"));
    }

    //See if query returns a result, if not, no item in location
    else if(checkQ.size() == 0)
    {
        QMessageBox msg;
        msg.information(this,tr("Warning"), tr("No stock found"));
    }

    //See if trying to remove more stock than is available
    else if(quanAmount.toInt() < removeAmount.toInt())
    {
        QMessageBox msg;
        msg.information(this,"Warning",QString("Trying to take out more than is in stock. There is %1 in location").arg(quanAmount));
    }

    else
    {
        //If removal makes item count == 0 then delete from database
        if((quanAmount.toInt() - removeAmount.toInt()) == 0)
        {
            QSqlQuery removeQuery;
            removeQuery.exec("DELETE from stockroom WHERE Dept='" + dept + "' AND DPCI='" + dpci + "' AND Location ='" + location+ "'");

        }

        //Else update the new count for the item DPCI
        else
        {
            QSqlQuery removeQuery;
            removeQuery.exec("UPDATE stockroom SET Quantity=Quantity-" + removeAmount + " WHERE DPCI='" + dpci +"'");
        }

        //Check to see if item exists in replenishment database
        QSqlQuery replenish;
        replenish.exec("SELECT * FROM replenishment WHERE DPCI='" + dpci +"'");

        //If it does then update the count
        if(replenish.size() != 0)
        {
            QSqlQuery update_replenish;
            update_replenish.exec("UPDATE replenishment SET Quantity=Quantity+" + removeAmount + " WHERE DPCI='" + dpci +"'");
            connection.closeConn();
            this->close();

        }

        //Else the item is unique; so add to replenishment table
        else
        {
            QSqlQuery add_replenish;
            add_replenish.prepare("INSERT INTO replenishment(DPCI,Quantity) VALUES (:dpci,:quantity)");
            add_replenish.bindValue(":dpci", dpci);
            add_replenish.bindValue(":quantity",removeAmount);
            add_replenish.exec();
            connection.closeConn();
            this->close();
        }
    }

}


void remove_stock_window::on_remove_stock_back_button_clicked()
{
    this->close();
}
