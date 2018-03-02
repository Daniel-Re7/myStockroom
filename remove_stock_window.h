#ifndef REMOVE_STOCK_WINDOW_H
#define REMOVE_STOCK_WINDOW_H

#include <QDialog>

namespace Ui {
class remove_stock_window;
}

class remove_stock_window : public QDialog
{
    Q_OBJECT

public:
    explicit remove_stock_window(QWidget *parent = 0);
    ~remove_stock_window();

private slots:
    void on_confirm_remove_button_clicked();

private:
    Ui::remove_stock_window *ui;
};

#endif // REMOVE_STOCK_WINDOW_H
