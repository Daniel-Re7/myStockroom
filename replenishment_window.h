#ifndef REPLENISHMENT_WINDOW_H
#define REPLENISHMENT_WINDOW_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class replenishment_window;
}

class replenishment_window : public QDialog
{
    Q_OBJECT

public:
    explicit replenishment_window(QWidget *parent = 0);
    QSqlQueryModel replenish_model;
    ~replenishment_window();

private slots:
    void on_reload_button_clicked();

    void on_export_button_clicked();

    void replenish();


private:
    Ui::replenishment_window *ui;

};

#endif // REPLENISHMENT_WINDOW_H
