#ifndef STOCK_PORTAL_H
#define STOCK_PORTAL_H

#include <QMainWindow>
#include <QTSQL>
#include <QDebug>
#include "add_stock_window.h"

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

private:
    Ui::stock_portal *ui;
    add_stock_window *add_stock;
};

#endif // STOCK_PORTAL_H
