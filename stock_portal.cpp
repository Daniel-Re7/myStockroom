#include "stock_portal.h"
#include "ui_stock_portal.h"

QSqlDatabase db;
stock_portal::stock_portal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::stock_portal)
{
    ui->setupUi(this);
}

stock_portal::~stock_portal()
{
    delete ui;
}

void stock_portal::on_add_stock_button_clicked()
{
    add_stock = new add_stock_window(this);
    add_stock->exec();

}

void stock_portal::on_remove_stock_button_clicked()
{
    remove_stock = new remove_stock_window(this);
    remove_stock->exec();
}

void stock_portal::on_replenish_button_clicked()
{
    replenish_stock = new replenishment_window(this);
    replenish_stock->exec();

}
