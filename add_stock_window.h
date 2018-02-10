#ifndef ADD_STOCK_WINDOW_H
#define ADD_STOCK_WINDOW_H

#include <QDialog>

namespace Ui {
class add_stock_window;
}

class add_stock_window : public QDialog
{
    Q_OBJECT

public:
    explicit add_stock_window(QWidget *parent = 0);
    ~add_stock_window();

private slots:
    void on_update_stock_button1_clicked();

private:
    Ui::add_stock_window *ui;
};

#endif // ADD_STOCK_WINDOW_H
