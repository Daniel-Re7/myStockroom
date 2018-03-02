#include "remove_stock_window.h"
#include "ui_remove_stock_window.h"
#include "stock_portal.h"
#include <QSqlDatabase>
#include <QMessageBox>

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
    QString dpci = ui->remove_dpci_edit->text();
    QString location = ui->remove_loc_edit->text();
    QString dept = ui->remove_dept_input->currentText();
    QString amount = ui->remove_amount_edit->text();

    QSqlQuery checkQ;
    checkQ.exec("SELECT * FROM stockroom WHERE Dept='" + dept + "' AND DPCI='" + dpci + "' AND Location ='" + location+ "'");
    checkQ.next();
    QString quanAmount;
    quanAmount.append( checkQ.value(2).toString() + " ");

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
    else if(amount.toInt() <= 0 || amount.isNull())
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

    //See if trying to take out too much
    else if(quanAmount.toInt() < amount.toInt())
    {
        QMessageBox msg;
        msg.information(this,"Warning",QString("Trying to take out more than is in stock. There is %1 in location").arg(quanAmount));
    }
    else
    {
        if((quanAmount.toInt() - amount.toInt()) == 0)
        {
            QSqlQuery deleteQuery;
            deleteQuery.exec("DELETE from stockroom WHERE Dept='" + dept + "' AND DPCI='" + dpci + "' AND Location ='" + location+ "'");
            qDebug() << "Stock removed from Database";
            this->close();
        }
        else
        {
            int tempQuant = quanAmount.toInt();
            QSqlQuery deleteQuery;
            tempQuant -= amount.toInt();
            QString new_quantity;
            new_quantity = QString::number(tempQuant);
            deleteQuery.exec("DELETE from stockroom WHERE Dept='" + dept + "' AND DPCI='" + dpci + "' AND Location ='" + location+ "'");
            QSqlQuery query;
            query.prepare("INSERT INTO stockroom(Dept, DPCI, Quantity, Location) VALUES (:dept, :dpci, :quantity, :location)");
            query.bindValue(":dept", dept);
            query.bindValue(":dpci", dpci);
            query.bindValue(":quantity", new_quantity);
            query.bindValue(":location", location);
            query.exec();
            qDebug() << "Stock removed from Database";
            this->close();
        }
    }

}
