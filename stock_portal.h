#ifndef STOCK_PORTAL_H
#define STOCK_PORTAL_H

#include <QMainWindow>
#include <QTSQL>
#include <QDebug>
#include "add_stock_window.h"
#include "remove_stock_window.h"
#include "replenishment_window.h"

namespace Ui {
class stock_portal;
}

class stock_portal : public QMainWindow
{
    Q_OBJECT

public:
    explicit stock_portal(QWidget *parent = 0);
    ~stock_portal();

private slots:
    void on_add_stock_button_clicked();

    void on_remove_stock_button_clicked();

    void on_replenish_button_clicked();

private:
    Ui::stock_portal *ui;
    add_stock_window *add_stock;
    remove_stock_window *remove_stock;
    replenishment_window *replenish_stock;
};

#endif // STOCK_PORTAL_H
