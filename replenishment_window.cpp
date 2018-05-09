#include "replenishment_window.h"
#include "ui_replenishment_window.h"
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include "login.h"
#include <QDateTime>
#include <QFile>
#include <QDir>

replenishment_window::replenishment_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::replenishment_window)
{
    ui->setupUi(this);
    replenish();
}

replenishment_window::~replenishment_window()
{
    delete ui;
}

void replenishment_window::on_reload_button_clicked()
{
    replenish();
}

void replenishment_window::on_export_button_clicked()
{
    int rowCount = replenish_model.rowCount();
    int columnCount = replenish_model.columnCount();
    QString columnName = replenish_model.record(0).fieldName(0) + "," + replenish_model.record(0).fieldName(1)+"\n";
    QString data= columnName;

    //Traverse the QSqlQueryModel and write the data to string
    for(int row = 0; row < rowCount; row++)
    {
        for(int column = 0; column < columnCount; column++)
        {
            data+=replenish_model.data(replenish_model.index(row,column)).toString();
            data+= ",";
        }

        data+="\n";
    }

    //Specify the path to write the CSV file to
    QString path= QDir::homePath();
    path+= "/Desktop/Replenish_Reports/";

    if(!QDir(path).exists())
    {
        QDir().mkdir(path);
    }

    //Create the file and write to it
    QString date = QDate::currentDate().toString();
    date = date.replace(" ","-");
    QFile new_report(path + "Replenishment_" + date + ".csv");
    if(new_report.open(QIODevice::WriteOnly))
    {
        QTextStream write(&new_report);
        write << data;
        new_report.close();
    }

}

void replenishment_window::replenish()
{
    //Establish database connection
    login connection;
    connection.openConn();
    QSqlQuery* replenish_query = new QSqlQuery(connection.getDB());

    //Execuate query and populate the TableView
    replenish_query->prepare("SELECT * FROM replenishment");
    replenish_query->exec();
    replenish_model.setQuery(*replenish_query);
    ui->replenishmentView->setModel(&replenish_model);

    //Close database connection when done
    connection.closeConn();

    //Set timestamp of when the list was last updated
    QDateTime current_date;
    QString last_update = "Updated On: " + current_date.currentDateTime().toLocalTime().toString();
    ui->last_retrieved_label->setText(last_update);
}

